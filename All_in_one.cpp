//RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT


#include <stdio.h>
#include <math.h>
#include <assert.h>


const double EPSILON = 1e-11;
enum ROOTS {INFINITE_ROOTS = -1, NO_ROOTS = 0, ONE_ROOT = 1, TWO_ROOTS = 2};
const int WEIRD_NUMBER = 26;


struct parameters  // parameters
{
    double a, b, c;
};

struct  answer // answer
{
    int nRoots;
    double x1, x2;
};

struct data_for_tests  // data for tests
{
    parameters params;
    answer ans;
};


int IsZero(const double num);
int IsEndOfInput(const int sym);
void Skip();
int MainInput();
void Base();
void InputSquare(parameters* const inDataP);
void OutputSquare(answer* const outDataP);
void Solve (parameters* const inDataP, answer* const outDataP);
int SolveLinear(const double b, const double c, double* const x1);
int SolveSquare(parameters* const inDataP, double* const x1, double* const x2);
void RunAllTests();
int Test(const int nTest, data_for_tests* const dataP);


int IsZero(const double num)
{
    if (fabs(num) < EPSILON)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int IsEndOfInput(const int sym)
{
    if (sym == EOF || sym == '\n' || sym == WEIRD_NUMBER)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void Skip()
{
    while (!IsEndOfInput(getchar()))
    {
        continue;
    }
}


int MainInput()
{
    printf("Enter 0 to run tests, 1 to solve, 2 to exit.\n");

    int ch1 = 0;

    while (1)
    {
        ch1 = getchar();

        if (IsEndOfInput(ch1))
        {
            printf("Input at least something! It'll be better if you enter 0, 1, or 2.\n");
            continue;
        }
        else
        {
            if (IsEndOfInput(getchar()))
            {
                if (ch1 == '0' || ch1 == '1' || ch1 == '2')
                {
                    return ch1;
                }
                else
                {
                    printf("Enter 0, 1 or 2!\n");
                }

            }
            else
            {
                Skip();

                printf("Enter ONE number! It'll be better if you enter 0, 1, or 2.\n");
            }
        }
    }
}


int main()
{
    int enter = 0;

    while (1)
    {
        enter = MainInput();

        switch (enter)
        {
            case '0':
                RunAllTests();
                break;

            case '1':
                Base();
                break;

            case '2':
                return 0;
                break;

            default:
                printf("something weird happened\n");
                break;
        }
    }
}


void Base()
{
    parameters inData = {NAN, NAN, NAN};

    printf("Enter the coefficients of the quadratic equation from a to c.\n");

    InputSquare(&inData);

    answer outData = {0, NAN, NAN};
    Solve(&inData, &outData);

    OutputSquare(&outData);
}


void InputSquare(parameters* const inDataP)
{
    assert(inDataP != 0);

    while (1)
    {
        int retVal = scanf("%lg %lg %lg", &(inDataP->a), &(inDataP->b), &(inDataP->c));

        if (retVal == 3)
        {
            if (IsEndOfInput(getchar()))
            {
                break;
            }
            else
            {
                Skip();

                printf("You entered them wrong. Try again!\n");
            }
        }
        else
        {
            if (retVal == -1)
            {
                printf( "Please, enter not only \"Ctrl+Z\".\n");
            }
            else
            {
                Skip();

                printf("You entered them wrong. Try again!\n");
            }
        }

    }



    /*while (scanf("%lg %lg %lg", &(inDataP->a), &(inDataP->b), &(inDataP->c)) != 3 || IsEndOfInput(getchar()))
    {
        while (!IsEndOfInput(getchar()))
        {
            continue;
        }

        printf("You entered them wrong. Try again!\n\n");
    }*/
}


void OutputSquare(answer* const outDataP)
{
    assert(outDataP != 0);

    if (IsZero(outDataP->x1))
    {
        outDataP->x1 = 0;
    }
    if (IsZero(outDataP->x2))
    {
        outDataP->x2 = 0;
    }

    switch (outDataP->nRoots)
    {
        case NO_ROOTS:
            printf("No roots\n\n");
            break;

        case ONE_ROOT:
            printf("First root %lg\n\n", outDataP->x1);
            break;

        case TWO_ROOTS:
            printf("First root %lg, second root %lg\n\n", outDataP->x1, outDataP->x2);
            break;

        case INFINITE_ROOTS:
            printf("Any number is a root\n\n");
            break;

        default:
            printf("Check nRoot value\n\n");
    }
}


void Solve (parameters* const inDataP, answer* const outDataP)
{
    assert(isfinite(inDataP->a) == 1);
    assert(isfinite(inDataP->b) == 1);
    assert(isfinite(inDataP->c) == 1);
    assert(inDataP != 0);
    assert(outDataP != 0);

    if (fabs(inDataP->a) < EPSILON)
    {
        outDataP->nRoots = SolveLinear(inDataP->b, inDataP->c, &(outDataP->x1));
    }
    else
    {
        outDataP->nRoots = SolveSquare(inDataP, &(outDataP->x1), &(outDataP->x2));
    }
}


int SolveLinear(const double b, const double c, double* const x1)
{
    assert(x1 != 0);

    if (IsZero(b))
    {
        if (IsZero(c))
        {
            return INFINITE_ROOTS;
        }
        else
        {
            return NO_ROOTS;
        }
    }
    else
    {
        *x1 = -c / b;
        return ONE_ROOT;
    }
}


int SolveSquare(parameters* inDataP, double* const x1, double* const x2)
{
    assert(inDataP != 0);
    assert(x1 != 0);
    assert(x1 != 0);
    assert(x1 != x2);

    double a = inDataP->a, b = inDataP->b, c = inDataP->c;

    double d = b*b - 4*a*c;

    if (IsZero(d))
    {
        *x1 = -b / (2*a);

        return ONE_ROOT;
    }
    else
    {
        if (d < 0)
        {
            return NO_ROOTS;
        }
        else
        {
            double sqrtD = sqrt(d);

            *x1 = (-b - sqrtD) / (2*a);
            *x2 = (-b + sqrtD) / (2*a);

            return TWO_ROOTS;
        }

    }
}


void RunAllTests()
{
    printf("\n");
                      /*{{ a,      b,     c}, {        nRoots,  x1,  x2}}*/
    data_for_tests data[] = {{{ 0,      0,     0}, {INFINITE_ROOTS, NAN, NAN}},
                             {{ 0,    2.5, -12.5}, {      ONE_ROOT,   5, NAN}},
                             {{ 2,      0,    -8}, {     TWO_ROOTS,  -2,   2}},
                             {{ 2,      0,     8}, {     TWO_ROOTS,  -2,   2}},      // deliberately incorrect data
                             {{ 1,      1,     0}, {     TWO_ROOTS,  -1,   0}},
                             {{ 0,      0,   -10}, {      NO_ROOTS, NAN, NAN}},
                             {{ 0, 15.246,     0}, {      ONE_ROOT,   0, NAN}},
                             {{-3,      0,     0}, {      ONE_ROOT,   0, NAN}},
                             {{ 1,     -2,    -3}, {     TWO_ROOTS,  -1,   3}}};

    int n = sizeof(data)/sizeof(data_for_tests);
    for (int i = 0; i < n; i++)
    {
        Test(i+1, &(data[i]));
    }
}


int Test(const int nTest, data_for_tests* const dataP)
{
    assert(dataP != 0);

    answer ans = {NO_ROOTS, NAN, NAN};
    Solve(&(dataP->params), &ans);

    if (ans.nRoots == (dataP->ans).nRoots &&
       (IsZero(ans.x1 - (dataP->ans).x1) || (isnan(ans.x1) && isnan((dataP->ans).x1))) &&
       (IsZero(ans.x2 - (dataP->ans).x2) || (isnan(ans.x2) && isnan((dataP->ans).x2))))
    {
        printf("Test %d. Success\n\n", nTest);
        return 0;
    }
    else
    {
        printf("Test %d. Data mismatch\n"
               "Number of roots: %d, expected %d\n"
               "First root: %lg, expected %lg\n"
               "Second root: %lg, expected %lg\n\n",
               nTest, ans.nRoots, (dataP->ans).nRoots, ans.x1, (dataP->ans).x1, ans.x2, (dataP->ans).x2);
        return 1;
    }

}

//RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT

#include <stdio.h>
#include <math.h>
#include <assert.h>


const double EPSILON = 0.000001;
const int INFINITE_ROOTS = -1;


struct input_data  // parameters
{
    double a, b, c;
};

struct  output_data // answer
{
    int nRootsExp;
    double x1Exp, x2Exp;
};


struct dft  // data for tests
{
    input_data params;
    output_data ans;
};


int Choice();
int Base();
void InputSquare(input_data* const inDataP);
void OutputSquare(const int nRoots, const double x1, const double x2);
int Solve (input_data* const inDataP, double* const x1, double* const x2);
int SolveLinear(const double b, const double c, double* const x1);
int SolveSquare(const double a, const double b, const double c, double* const x1, double* const x2);
void RunAllTests();
int Test(const int nTest, dft* const dataP);


int main()
{
    Choice();
}


int Choice()
{
    while (1)
    {
        printf("Enter 0 to run tests, 1 to solve, 2 to exit.\n");

        int enter = getchar();

        while (!((enter == '0' || enter == '1' || enter == '2') && getchar() == '\n'))
        {
            while (getchar() != '\n')
            {
                continue;
            }

            printf("Enter 0, 1 or 2!\n");

            enter = getchar();
        }

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


int Base()
{
    input_data inData = {NAN, NAN, NAN};
    double x1 = NAN, x2 = NAN;

    printf("Enter the coefficients of the quadratic equation from a to c.\n");

    InputSquare(&inData);

    int nRoots = 0;
    nRoots = Solve(&inData, &x1, &x2);

    OutputSquare(nRoots, x1, x2);

    return 0;
}


void InputSquare(input_data* const inDataP)
{
    while (scanf("%lg %lg %lg", &(inDataP->a), &(inDataP->b), &(inDataP->c)) != 3 || getchar() != '\n')
    {
        while (getchar() != '\n')
        {
            continue;
        }

        printf("You entered them wrong. Try again!\n\n");
    }
}


void OutputSquare(const int nRoots, const double x1, const double x2)
{
    switch (nRoots)
    {
        case 0:
            printf("No roots");
            break;

        case 1:
            printf("First root %lg", x1);
            break;

        case 2:
            printf("First root %lg, second root %lg", x1, x2);
            break;

        case INFINITE_ROOTS:
            printf("Any number is a root");
            break;

        default:
            printf("Check nRoot value");
    }
}


int Solve (input_data* const inDataP, double* const x1, double* const x2)
{
    assert(isfinite(inDataP->a) == 1);
    assert(isfinite(inDataP->b) == 1);
    assert(isfinite(inDataP->c) == 1);
    assert(x1 != x2);
    assert(x1 != 0 && x2 != 0 && inDataP != 0);

    if (fabs(inDataP->a) < EPSILON)
    {
        return SolveLinear(inDataP->b, inDataP->c, x1);
    }
    else
    {
        return SolveSquare(inDataP->a, inDataP->b, inDataP->c, x1, x2);
    }
}


int SolveLinear(const double b, const double c, double* const x1)
{
    if (fabs(b) < EPSILON)
    {
        if (fabs(c) < EPSILON)
        {
            return INFINITE_ROOTS;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (fabs(c) < EPSILON)
        {
            *x1 = 0;
            return 1;
        }
        else
        {
            *x1 = -c / b;
        }
        return 1;
    }
}


int SolveSquare(const double a, const double b, const double c, double* const x1, double* const x2)
{
    double d = b*b - 4*a*c;

    if (d < 0 && fabs(d) > EPSILON)
    {
        return 0;
    }
    else
    {
        if (fabs(d) < EPSILON)
        {

            *x1 = -b / (2*a);

            return 1;
        }
        else
        {

            *x1 = (-b - sqrt(d)) / (2*a);
            *x2 = (-b + sqrt(d)) / (2*a);

            return 2;
        }
    }
}


void RunAllTests()
{
    printf("\n");

    const int nTest = 9;
                    /*{{a, b, c}, {nRootsExp, x1Exp, x2Exp}}*/
    dft data[nTest]= {{{0, 0, 0}, {INFINITE_ROOTS, NAN, NAN}},
                      {{0, 2.5, -12.5}, {1, 5, NAN}},
                      {{2, 0, -8}, {2, -2, 2}},
                      {{2, 0, 8}, {2, -2, 2}},      // deliberately incorrect data
                      {{1, 1, 0}, {2, -1, 0}},
                      {{0, 0, -10}, {0, NAN, NAN}},
                      {{0, 15.246, 0}, {1, 0, NAN}},
                      {{-3, 0, 0}, {1, 0, NAN}},
                      {{1, -2, -3}, {2, -1, 3}}};

    int i;
    for (i = 0; i < nTest; i++)
    {
        Test(i+1, &(data[i]));

    }
}


int Test(const int nTest, dft* const dataP)
{
    double x1 = NAN, x2 = NAN;
    int nRoots = Solve(&(dataP->params), &x1, &x2);
    if (nRoots == (dataP->ans).nRootsExp &&
       (fabs(x1 - (dataP->ans).x1Exp) < EPSILON || (isnan(x1) && isnan((dataP->ans).x1Exp))) &&
       (fabs(x2 - (dataP->ans).x2Exp) < EPSILON || (isnan(x2) && isnan((dataP->ans).x2Exp))))
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
               nTest, nRoots, (dataP->ans).nRootsExp, x1, (dataP->ans).x1Exp, x2, (dataP->ans).x2Exp);
        return 1;
    }

}

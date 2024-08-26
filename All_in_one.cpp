//RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT


#include <stdio.h>
#include <math.h>
#include <assert.h>


const double EPSILON = 1e-6;
enum roots {INFINITE_ROOTS = -1, NO_ROOTS = 0, ONE_ROOT = 1, TWO_ROOTS = 2};


struct input_data  // parameters
{
    double a, b, c;
};

struct  output_data // answer
{
    int nRoots;
    double x1, x2;
};

struct dft  // data for tests
{
    input_data params;
    output_data ans;
};


int IsZero(const double num);
int IsEndOfInput(const int sym);
void Skip();
int ChoiceInput();
int Choice();
int Base();
void InputSquare(input_data* const inDataP);
void OutputSquare(output_data* const outDataP);
int Solve (input_data* const inDataP, double* const x1, double* const x2);
int SolveLinear(const double b, const double c, double* const x1);
int SolveSquare(const double a, const double b, const double c, double* const x1, double* const x2);
void RunAllTests();
int Test(const int nTest, dft* const dataP);


int main()
{
    Choice();

    return 0;
}


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
    if (sym == EOF || sym == '\n' || sym == 26)
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


int ChoiceInput()
{
    printf("Enter 0 to run tests, 1 to solve, 2 to exit.\n");

    int ch1;

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


int Choice()
{
    int enter;

    while (1)
    {
        enter = ChoiceInput();

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

    printf("Enter the coefficients of the quadratic equation from a to c.\n");

    InputSquare(&inData);

    output_data outData = {0, NAN, NAN};
    outData.nRoots = Solve(&inData, &outData.x1, &outData.x2);

    OutputSquare(&outData);

    return 0;
}


void InputSquare(input_data* const inDataP)
{
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


void OutputSquare(output_data* const outDataP)
{
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


int SolveSquare(const double a, const double b, const double c, double* const x1, double* const x2)
{
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
               /*{{a, b, c}, {nRoots, x1, x2}}*/
    dft data[]= {{{0, 0, 0}, {INFINITE_ROOTS, NAN, NAN}},
                 {{0, 2.5, -12.5}, {1, 5, NAN}},
                 {{2, 0, -8}, {2, -2, 2}},
                 {{2, 0, 8}, {2, -2, 2}},      // deliberately incorrect data
                 {{1, 1, 0}, {2, -1, 0}},
                 {{0, 0, -10}, {0, NAN, NAN}},
                 {{0, 15.246, 0}, {1, 0, NAN}},
                 {{-3, 0, 0}, {1, 0, NAN}},
                 {{1, -2, -3}, {2, -1, 3}}};

    int n = sizeof(data)/sizeof(dft);
    for (int i = 0; i < n; i++)
    {
        Test(i+1, &(data[i]));
    }
}


int Test(const int nTest, dft* const dataP)
{
    double x1 = NAN, x2 = NAN;
    int nRoots = Solve(&(dataP->params), &x1, &x2);
    if (nRoots == (dataP->ans).nRoots &&
       (IsZero(x1 - (dataP->ans).x1) || (isnan(x1) && isnan((dataP->ans).x1))) &&
       (IsZero(x2 - (dataP->ans).x2) || (isnan(x2) && isnan((dataP->ans).x2))))
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
               nTest, nRoots, (dataP->ans).nRoots, x1, (dataP->ans).x1, x2, (dataP->ans).x2);
        return 1;
    }

}

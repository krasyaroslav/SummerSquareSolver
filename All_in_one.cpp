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
void Repeat();
void InputSquare(double* const a, double* const b, double* const c);
void OutputSquare(const int nRoots, const double x1, const double x2);
int Solve (const double a, const double b, const double c, double* const x1, double* const x2);
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
    printf("Enter 0 to run tests, or something else to solve.\n");

    if (getchar() == '0' and getchar() == '\n')
    {
        RunAllTests();
        return 0;
    }
    else
    {
        while (getchar() != '\n')
        {
            continue;
        }

        Base();
        return 0;
    }
}


int Base()
{
    double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;


    printf("Enter the coefficients of the quadratic equation from a to c.\n");

    InputSquare(&a, &b, &c);

    int nRoots = 0;
    nRoots = Solve (a, b, c, &x1, &x2);

    OutputSquare(nRoots, x1,x2);

    printf("\nEnter 1 if you want to solve one more equation.\n");

    Repeat();

    return 0;
}


void Repeat()
{
    if (getchar() == '1' and getchar() == '\n')
    {
        printf("\n");
        Base();
    }
}


void InputSquare(double* const a, double* const b, double* const c)
{
    while (scanf("%lg %lg %lg", a, b, c) != 3 || getchar() != '\n')
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


int Solve (const double a, const double b, const double c, double* const x1, double* const x2)
{
    assert(isfinite(a) == 1);
    assert(isfinite(b) == 1);
    assert(isfinite(c) == 1);
    assert(x1 != x2);
    assert(x1 != 0 && x2 != 0);

    if (fabs(a) < EPSILON)
    {
        return SolveLinear(b, c, x1);
    }
    else
    {
        return SolveSquare(a, b, c, x1, x2);
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
    int nRoots = Solve((dataP->params).a, (dataP->params).b, (dataP->params).c, &x1, &x2);
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

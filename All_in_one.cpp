//RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT RT

#include <stdio.h>
#include <math.h>
#include <assert.h>

const double EPSILON = 0.000001;
const int INFINITE_ROOTS = -1;

int Choice();
int Base();
void InputSquare(double* const a, double* const b, double* const c);
void OutputSquare(const int nRoots, const double x1, const double x2);
int SolveSquare (const double a, const double b, const double c, double* const x1, double* const x2);
void RunAllTests();
int Test(int* const nTestP, const double a, const double b, const double c, const int nRootsExp, const double x1Exp, const double x2Exp);


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
    nRoots = SolveSquare (a, b, c, &x1, &x2);

    OutputSquare(nRoots, x1,x2);

    printf("\nEnter 1 if you want to solve one more equation.\n");

    if (getchar() == '1' and getchar() == '\n')
    {
        printf("\n");
        Base();
        return 0;
    }
    else
    {
        return 0;
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


int SolveSquare (const double a, const double b, const double c, double* const x1, double* const x2)
{
    assert(isfinite(a) == 1);
    assert(isfinite(b) == 1);
    assert(isfinite(c) == 1);
    assert(x1 != x2);
    assert(x1 != 0 && x2 != 0);

    if (fabs(a) < EPSILON)
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
    else
    {

        double d = b*b - 4*a*c;

        if (d < 0)
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
}


void RunAllTests()
{
    int nTest = 1;

    Test(&nTest, 0, 0, 0, INFINITE_ROOTS, NAN, NAN);
    Test(&nTest, 0, 2.5, -12.5, 1, 5, NAN);
    Test(&nTest, 2, 0, -8, 2, -2, +2);
    Test(&nTest, 2, 0, 8, 2, -2, +2);       // deliberately incorrect data
    Test(&nTest, 1, 1, 0, 2, -1, 0);
    Test(&nTest, 0, 0, -10, 0, NAN, NAN);
    Test(&nTest, 0, 15.246, 0, 1, 0, NAN);
    Test(&nTest, -3, 0, 0, 1, 0, NAN);
    Test(&nTest, 1, -2, -3, 2, -1, 3);
}


int Test(int* const nTestP, const double a, const double b, const double c, const int nRootsExp, const double x1Exp, const double x2Exp)
{
    double x1 = NAN, x2 = NAN;
    int nRoots = SolveSquare(a, b, c, &x1, &x2);
    if (nRoots == nRootsExp &&
       (fabs(x1 - x1Exp) < EPSILON || (isnan(x1) && isnan(x1Exp))) &&
       (fabs(x2 - x2Exp) < EPSILON || (isnan(x2) && isnan(x2Exp))))
    {
        printf("Test %d. Success\n\n", *nTestP);
        (*nTestP)++;
        return 0;
    }
    else
    {
        printf("Test %d. Data mismatch\n"
               "Number of roots: %d, expected %d\n"
               "First root: %lg, expected %lg\n"
               "Second root: %lg, expected %lg\n\n",
               *nTestP, nRoots, nRootsExp, x1, x1Exp, x2, x2Exp);
        (*nTestP)++;
        return 1;
    }

}

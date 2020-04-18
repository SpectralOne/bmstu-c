/*

  // Quadratic equation //

#include <stdio.h>
#include <math.h>
#define OK           0
#define INPUT_ERROR -1
#define CLASSIC     -2 // ax^2 + bx + c = 0
#define MISSING_A   -3 // bx = -c        : x = -c/b
#define MISSING_A_B -4 // c = 0 ---
#define MISSING_A_C -5 // bx = 0         : x = 0
#define MISSING_B   -6 // ax^2 = -c      : x = sqrt(-c/a)
#define MISSING_B_C -7 // ax^2 = 0       : x = 0
#define MISSING_ALL -8 // ? = 0
#define UNSOLVABLE  -9

int equation_type(int a, int b, int c)
{
    int equation_type = MISSING_ALL;

    if (a && b && c)
        equation_type = CLASSIC;
    if (!a && b && c)
        equation_type = MISSING_A;
    if (!a && !b && c)
        equation_type = MISSING_A_B;
    if (!a && b && !c)
        equation_type = MISSING_A_C;
    if (a && !b && c)
        equation_type = MISSING_B;
    if (a && !b && !c)
        equation_type = MISSING_B_C;

    return equation_type;
}

int root_finder(int a, int b, int c, int equation_type, double *root1, double *root2)
{
    int status = MISSING_ALL;

    if (equation_type == CLASSIC)
    {
        int D = (b * b) - (4 * a * c);
        if (D == 0)
        {
            status = OK;
            *root1 = -b/(2*a);
        }
        else if (D > 0)
        {
            status = OK;
            *root1 = (-b+sqrt(D))/(2*a);
            *root2 = (-b-sqrt(D))/(2*a);
        }
        else
            status = UNSOLVABLE;
    }
    if (equation_type == MISSING_A)
    {
        status = OK;
        *root1 = -c/b;
    }
    if (equation_type == MISSING_A_B)
        status = UNSOLVABLE;
    if (equation_type == MISSING_A_C)
    {
        status = OK;
        *root1 = 0;
    }
    if (equation_type == MISSING_B)
    {
        if ((c > 0 && a > 0) || (a < 0 && c > 0) || (a < 0 && c < 0))
            status = UNSOLVABLE;
        else
        {
            status = OK;
            *root1 = sqrt(-c/a);
            *root2 = -(sqrt(-c/a));
        }
    }
    if (equation_type == MISSING_B_C)
    {
        status = OK;
        *root1 = 0;
    }
    return status;
}

int main(void)
{
    int a, b, c, eq_type, status = OK;
    double root1, root2;

    printf("Enter coefficients: ");
    if (scanf("%d%d%d", &a, &b, &c) == 3)
    {
        eq_type = equation_type(a, b, c);
        status = root_finder(a, b, c, eq_type, &root1, &root2);
        if (status == OK)
        {
            if (root1 && root2)
                printf("Roots are %.4g and %.4g", root1, root2);
            else
                printf("Only one root has been found: %.4g", root1);
        }
        else
            printf("Cant solve!");
    }
    else
    {
        status = INPUT_ERROR;
        printf("Input error!");
    }
    return status;
}
*/



  // Bisection //

#include <stdio.h>
#include <math.h>
#define OK         0
#define INP_ERR   -1
#define RANGE_ERR -2
#define PRECISION  0.0000000000001

int f_equal(double num1, double num2)
{
    return (fabs(num1 - num2) < PRECISION);
}

size_t F(size_t x)
{
    return sin(x);
}

void bisection(int a, int b, int step, double eps)
{
    int a1, b1, n = 0;
    double root, xstart, xend;

    b1 = a;
    a1 = a;

    for (int i = 0; i < (b - a) / step; i++)
    {
        b1 += step;
        a1 = b1 - step;
        if (b1)
        {
            if (F(a1) * F(b1) <= 0)
            {
                xstart = a1;
                xend = b1;
                while (fabs(fabs(xstart) - fabs(xend)) > eps)
                {
                    root = (xend + xstart) / 2;
                    if (F(xstart) * F(root) <= 0)
                        xend = root;
                    else
                        xstart = root;
                }
                n++;
                printf("Root #%d = %f\n", n, root);
            }
        }
    }
}

int main(void)
{

    int a, b, step, status = OK;
    double eps;

    printf("I need start, end, step and eps: ");
    if (scanf("%d %d %d %lf", &a, &b, &step, &eps) == 4)
        bisection(a, b, step, eps);
    else
    {
        status = INP_ERR;
    }
    return status;
}


/*

  // Sum //


#include <stdio.h>
#include <math.h>
#define OK         0
#define INP_ERR   -1
#define RANGE_ERR -2
#define PRECISION  0.0000000000001

int f_equal(double num1, double num2)
{
    return (fabs(num1 - num2) < PRECISION);
}

double sum(double x, double eps)
{
    int i = 1;
    double s = x, t = x;

    while (fabs(t) > eps)
    {
        i += 2;
        t = -t * x * x / (i - 1) / i;
        s += t;
    }
    return s;
}

int main(void)
{
    int status = OK;
    double x, eps;

    printf("Enter x and eps: ");
    if (scanf("%lf%lf", &x, &eps) == 2)
    {
        if (eps < 0 || eps > 1 || f_equal(eps, 0))
        {
            status = RANGE_ERR;
            printf("Range error!");
        }
        else
            printf("Sum = %.13f", sum(x, eps));
    }
    else
    {
        status = INP_ERR;
        printf("I/O error!");
    }
    return status;
}
*/

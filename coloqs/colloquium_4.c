/*
 Богаченко Артём
 ИУ7-26Б (Ломовской И. В.)
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define MAX_STR_LEN   255
#define PRECISION     0.000000001
#define NUM_AFTER_DOT 6
#define NOT_VALID     0
typedef char string_t[MAX_STR_LEN + 1];

char* double_to_string_v1(double num, string_t str)
{
    long long int int_part, int_dig_count, digit, mlt, pos = 0;
    double float_part;

    if(num < 0.0)
    {
        str[pos++] = '-';
        num *= -1;
    }

    int_part = (long long int) num;
    float_part = num - (double) int_part;

    if (int_part)
        int_dig_count = (long long int) log10((double) int_part) + 1;
    else
        int_dig_count = 1;

    for (long long int len = int_dig_count; len > 0; len--)
    {
        mlt = pow(10, len - 1);
        digit = int_part / mlt;
        str[pos++] = digit + 48;
        int_part %= mlt;
    }
    str[pos++] = '.';

    for (long long int i = 0; i < NUM_AFTER_DOT; i++)
    {
        float_part *= 10.0;
        digit = float_part;
        str[pos++] = digit + 48;
        float_part -= digit;
    }
    str[pos]='\0';

    return str;
}

char* double_to_string_v2(double num, string_t str)
{
    long long int num_of_digits = log10(num), digit;
    double mlt;

    while (num > PRECISION)
    {
        mlt = pow(10.0f, num_of_digits);
        digit = num / mlt;
        num -= (digit * mlt);

        *(str++) = '0' + digit;
        if (num_of_digits == 0)
            *(str++) = '.';
        num_of_digits--;
    }
    *(str) = '\0';
    return str;
}

double string_to_double(string_t str)
{
    // "^\d{1}.\d+(E\+)\d+$"
    double num = 0.0;
    int num_sign = 1, exp_pow = 0, i = 0, flag = 0;
    int dot_count = 0, neg_sign_count = 0, e_neg_sign = 0, e_count = 0, pos_sign_count = 0, e_pos_sign = 0;

    for (i = 0; str[i] != '\0' && !flag; i++)
    {
        if (str[i] == '.')
            (!dot_count) ? (dot_count = 1) : (flag = 1);

        if (str[i] == '-' && i == 0)
            (!neg_sign_count) ? (neg_sign_count = 1) : (flag = 1);

        if (str[i] == '-' && i != 0)
            (!e_neg_sign) ? (e_neg_sign = 1) : (flag = 1);

        if ((str[i] == 'E' || str[i] == 'e') && i != 0)
            (!e_count) ? (e_count = 1) : (flag = 1);

        if (str[i] == '+' && i == 0)
            (!pos_sign_count) ? (pos_sign_count = 1) : (flag = 1);

        if (str[i] == '+' && i != 0)
            (!e_pos_sign) ? (e_pos_sign = 1) : (flag = 1);

        if (e_neg_sign && e_pos_sign)
            flag = 1;

        if ((e_neg_sign && e_count == 0) || (e_pos_sign && e_count == 0))
            flag = 1;
    }
    if (flag)
        return NOT_VALID;

    if (*str == '-')
    {
        num_sign = -1;
        str++;
    }

    if (*str == '+')
        str++;

    while (*str++ != '\0' && isdigit(*(str - 1)))
        num = num * 10.0 + (*(str - 1) - '0');

    if (*(str - 1) == '.')
        while (*(str++) != '\0' && isdigit(*(str - 1)))
        {
            num = num * 10.0 + (*(str - 1) - '0');
            exp_pow -= 1;
        }

    if (*(str - 1) == 'e' || *(str - 1) == 'E')
    {
        int e_sign = 1, count = 0;
        str++;

        if (*(str - 1) == '+')
            str++;

        else if (*(str - 1) == '-')
        {
            str++;
            e_sign = -1;
        }

        while (isdigit(*(str - 1)))
        {
            count = count * 10 + (*(str - 1) - '0');
            str++;
        }
        exp_pow += count * e_sign;
    }

    while (exp_pow > 0)
    {
        num *= 10.0;
        exp_pow--;
    }

    while (exp_pow < 0)
    {
        num *= 0.1;
        exp_pow++;
    }

    return num * num_sign;
}

int evaluate_expression(string_t str)
{
    int sum = 0, tmp_res = 0, sign = 1, digit;

    while (*str)
    {
        digit = *str++ - '0';

        if (digit >= 0 && digit <= 9)
            tmp_res = tmp_res * 10 + digit;
        else
        {
            sum += sign * tmp_res;
            sign = (*str == '-' ? -1 : 1);
            tmp_res = 0;
        }
    }
    sum += sign * tmp_res;

    return sum;
}

int main()
{
    string_t str = "0.123";
    printf("Input: %s\nResult: %lf", str, string_to_double(str));
    return 0;
}


/*

// Quadratic equation //

#include <stdio.h>
#include <math.h>
#define OK               0
#define INPUT_ERROR     -1
#define CLASSIC         -2 //  ax^2 + bx + c = 0
#define MISSING_A       -3 //  bx = -c        : x = -c/b
#define MISSING_A_B     -4 //  c = 0 ---
#define MISSING_A_C     -5 //  bx = 0         : x = 0
#define MISSING_B       -6 //  ax^2 = -c      : x = sqrt(-c/a)
#define MISSING_B_C     -7 //  ax^2 = 0       : x = 0
#define MISSING_ALL     -8 //  ? = 0
#define COMPLEX_CLASSIC -9
#define COMPLEX_MISSING -10
#define UNSOLVABLE      -11
#define PRECISION        0.0000000000001

int f_equal(double num1, double num2)
{
    return (fabs(num1 - num2) < PRECISION);
}

int equation_type(double a, double b, double c)
{
    int equation_type = MISSING_ALL;

    if (a && b && c)
        equation_type = CLASSIC;
    if (f_equal(a, 0) && b && c)
        equation_type = MISSING_A;
    if (f_equal(a, 0) && f_equal(b, 0) && c)
        equation_type = MISSING_A_B;
    if (f_equal(a, 0) && b && f_equal(c, 0))
        equation_type = MISSING_A_C;
    if (a && f_equal(b, 0) && c)
        equation_type = MISSING_B;
    if (a && f_equal(b, 0) && f_equal(c, 0))
        equation_type = MISSING_B_C;

    return equation_type;
}

int root_finder(double a, double b, double c, int equation_type, int* roots_count, double* root1, double* root2)
{
    int status = MISSING_ALL;

    if (equation_type == CLASSIC)
    {
        double D = (b * b) - (4 * a * c);
        if (f_equal(D, 0))
        {
            status = OK;
            *root1 = -b / (2 * a);
            *roots_count = 1;
        }
        else if (D > 0)
        {
            status = OK;
            *root1 = (-b + sqrt(D)) / (2 * a);
            *root2 = (-b - sqrt(D)) / (2 * a);
            *roots_count = 2;
        }
        else
        {
            status = COMPLEX_CLASSIC;
            *root1 = -b / (2 * a);
            *root2 = *root1;
        }
    }
    if (equation_type == MISSING_A)
    {
        status = OK;
        *root1 = -c / b;
        *roots_count = 1;
    }
    if (equation_type == MISSING_A_B)
        status = UNSOLVABLE;
    if (equation_type == MISSING_A_C)
    {
        status = OK;
        *root1 = 0;
        *roots_count = 1;
    }
    if (equation_type == MISSING_B)
    {
        if ((c > 0 && a > 0) || (a < 0 && c > 0) || (a < 0 && c < 0))
            status = COMPLEX_MISSING;
        else
        {
            status = OK;
            *root1 = sqrt(-c / a);
            *root2 = -(sqrt(-c / a));
            *roots_count = 2;
        }
    }
    if (equation_type == MISSING_B_C)
    {
        status = OK;
        *root1 = 0;
        *roots_count = 1;
    }
    return status;
}

int main(void)
{
    int eq_type, roots_count = 0, status = OK;
    double root1, root2, a, b, c;

    printf("Enter coefficients: ");
    if (scanf("%lf%lf%lf", &a, &b, &c) == 3)
    {
        eq_type = equation_type(a, b, c);
        status = root_finder(a, b, c, eq_type, &roots_count, &root1, &root2);
        if (status == OK)
        {
            if (roots_count == 2)
                printf("Roots are %.6f and %.6f", root1, root2);
            else
                printf("Only one root has been found: %.6f", root1);
        }
        else if (status == COMPLEX_CLASSIC)
        {
            double D = fabs((b * b) - (4 * a * c));
            printf("Complex solution:\n");
            printf("%.6f + i%.6f\n%.6f - i%.6f", root1, sqrt(D), root2, sqrt(D));
        }
        else if (status == COMPLEX_MISSING)
        {
            printf("Complex solution:\n");
            printf(" i%f\n-i%f", sqrt(fabs(-c / a)), sqrt(fabs(-c / a)));
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

/*

  // Bisection //

#include <stdio.h>
#include <math.h>
#define OK         0
#define INP_ERR   -1
#define RNG_ERR   -2
#define NO_ROOTS  -3
#define PRECISION  0.0000000000001

int f_equal(double num1, double num2)
{
    return (fabs(num1 - num2) < PRECISION);
}

double F(double x)
{
    return sin(x);
}

int bisection(int a, int b, int step, double eps)
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
            if (F(a1) * F(b1) < 0 || f_equal(F(a1) * F(b1), 0))
            {
                xstart = a1;
                xend = b1;
                while (fabs(fabs(xstart) - fabs(xend)) > eps)
                {
                    root = (xend + xstart) / 2;
                    if (F(xstart) * F(root) < 0 || f_equal(F(xstart) * F(root), 0))
                        xend = root;
                    else
                        xstart = root;
                }
                n++;
                printf("Root #%d = %f\n", n, root);
            }
        }
    }
    return n;
}

int main(void)
{

    int a, b, step, roots, status = OK;
    double eps;

    printf("Enter start, end, step and eps: ");
    if (scanf("%d %d %d %lf", &a, &b, &step, &eps) == 4)
    {
        if (eps < 0 || eps > 1 || f_equal(eps, 0) || step < 1)
        {
            status = RNG_ERR;
            printf("Range error!");
        }
        else
        {
            roots = bisection(a, b, step, eps);
            if (!roots)
            {
                status = NO_ROOTS;
                printf("No roots found!");
            }
        }
    }
    else
    {
        status = INP_ERR;
        printf("I/O error!");
    }
    return status;
}
*/

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

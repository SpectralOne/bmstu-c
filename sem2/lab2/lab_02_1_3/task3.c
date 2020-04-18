#include <stdio.h>
#include <math.h>
#define OK 0
#define INP_ERR 1
#define RANGE_ERR 2
#define TRUE 1
#define FALSE 0
#define PRECISION 0.0000001

/*
  Функция вычисляет сумму ряда
  Принимает на вход значение x и точность eps
  Тип данных: float
  Возвращает сумму ряда для x с точностью eps
*/

float sum(float x, float eps)
{
    float s = x, t = x;
    int n = 1;

    while (fabs(t) > eps)
    {
        n += 2;
        t = -t * x * x / (n - 1) / (n);
        s += t;
    }
    return s;
}

/*
 Функция сравнивает два числа между собой
 Если одно число равно другому - возвращает True
 Если числа отличны друг от друга - False
 Тип входящих данных: float
 Тип вовзращаемых данных: int
*/

int f_equal(float num1, float num2)
{
    if (fabs(num1 - num2) < PRECISION)
        return TRUE;
    else
        return FALSE;
}

int main(void)
{
    float eps, x, f, absol, otnos;
    int status = 0;

    printf("Enter x and eps: ");
    if (scanf("%f%f", &x, &eps) == 2)
    {
        if (eps < 0 || eps > 1 || f_equal(eps, 0))
        {
            status = RANGE_ERR;
            printf("Range error!");
        }
        else
        {
            status = OK;
            f = sin(x);

            if (f_equal(x, 0))
                otnos = 0;
            else
                otnos = fabs((f - sum(x, eps)) / f);

            absol = fabs(f - sum(x, eps));

            printf("f(x) s(x) Abs Otn : %.7f %.7f %.7f %.7f", f, sum(x, eps), absol, otnos);
        }
    }
    else
    {
        status = INP_ERR;
        printf("I/O error!");
    }

    return status;
}

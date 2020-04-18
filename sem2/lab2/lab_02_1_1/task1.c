#include <stdio.h>
#include <math.h>
#define OK 0
#define INP_ERR 1
#define RNG_ERR 2

/*
  Функция вычисляет результат деления одного числа на другое
  Принимает на вход делимое, делитель и адреса частного и остатка
  Тип данных: int
  Функция не возвращает никаких значений
*/

void process(int num, int div, int *r, int *q)
{
    int count = 0;

    while (num >= div)
    {
        num -= div;
        count++;
    }

    *q = count;
    *r = num;
}

int main(void)
{
    int a, d, r, q, status = 0;

    printf("Enter two integers: ");

    if (scanf("%d %d", &a, &d) == 2)
    {
        if (a <= 0 || d <= 0)
        {
            status = RNG_ERR;
            printf("Range error!");
        }
        else
        {
            status = OK;
            process(a, d, &r, &q);
            printf("Chastnoe Ostatok: %d %d", q, r);
        }
    }
    else
    {
        status = INP_ERR;
        printf("I/O error!");
    }

    return status;
}



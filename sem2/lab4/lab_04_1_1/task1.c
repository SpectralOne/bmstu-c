#include <stdio.h>
#define TRUE 1
#define OK 0
#define FALSE 0
#define NO_ODD -1
#define RNG_ERR -2
#define INP_ERR -3
#define BAD -4
#define N 10

/*
 Функция ввода массива
 Считывает элементы массива и их количество
 Принимает на вход указатель на массив и указатель на размер массива
 Тип данных: int
 Вернёт: OK если ввод прошёл успешно, в противном случае код ошибки
*/

int arr_input(int a[], int *size)
{
    printf("Enter number of elements: ");
    if (scanf("%d", size) != 1)
        return INP_ERR;
    if (*size <= 0 || *size > N)
        return RNG_ERR;
    printf("\nEnter sequence: ");
    for (int i = 0; i < *size; i++)
    {
        if (scanf("%d", &a[i]) != 1)
            return INP_ERR;
    }
    return OK;
}

/*
 * Функция находит произведение нечётных элементов массива
 * Принимает на вход указатель на массив, его размерность и
   указатель на переменную произведения нечётных элементов
 * Тип данных: int
 * В случае успешной работы вернёт TRUE, в противном FALSE
*/

int work(const int a[], const int len, int *production)
{
    int flag = 0;
    *production = 1;

    for (int i = 0; i < len; i++)
    {
        if ((a[i] % 2))
        {
            flag = 1;
            *production *= a[i];
        }
    }
    if (flag)
        return TRUE;
    else
        return FALSE;
}

int main(void)
{
    int a[N], size, status = OK, production;

    status = arr_input(a, &size);
    if (status == OK)
    {
        if (work(a, size, &production))
        {
            printf("\nProduct of odd numbers is %d", production);
        }
        else
        {
            printf("\nNo odd numbers detected!");
            status = NO_ODD;
        }
    }
    else if (status == RNG_ERR)
        printf("\nRange error!");
    else if (status == INP_ERR)
        printf("\nInput error!");

    return status;
}

#include <stdio.h>
#define OK 0
#define RNG_ERR -1
#define INP_ERR -2
#define N_MAX 10
#define M_MAX 10
typedef int matrix_t[N_MAX][M_MAX];
typedef int array_t[M_MAX];

/*
 Функция ввода двумерного массива
 Считывает размеры массива, а затем элементы
 Принимает на вход указатель на массив и указатель на размеры массива
 Тип данных: int
 Вернёт: OK если ввод прошёл успешно, в противном случае код ошибки
*/

int mtr_input(matrix_t a, int *n, int *m)
{
    int status = OK;
    printf("Input n, m: ");
    if (scanf("%d%d", n, m) == 2)
    {
        if (1 <= *n && *n <= N_MAX &&
            1 <= *m && *m <= M_MAX)
        {
            printf("Input elements:\n");
            for (int i = 0; status == OK && i < *n; i++)
                for (int j = 0; status == OK && j < *m; j++)
                    if (scanf("%d", &a[i][j]) != 1)
                        status = INP_ERR;
        }
        else
            status = RNG_ERR;
    }
    else
        status = INP_ERR;

    return status;
}

/*
 Функция вывода двумерного массива
 Принимает на вход указатель на массив и его размеры
 Тип данных: int
 Ничего не возвращает
*/

void mtr_print(matrix_t a, const int n, const int m)
{
    printf("Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

/*
 Функция находит максимальный элемент строки
 Принимает на вход указатель на строку массива и длину строки
 Тип данных: int
 Возвращает максмальный элемент
*/

int max_element(const array_t a, int m)
{
    int max = a[0];

    for (int i = 0; i < m; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

/*
 Функция меняет местами текущую и следующую строку массива
 Принимает на вход указатель на массив, номер строки (позицию) и длину строки
 Тип данных: int
 Ничего не возвращает
*/

void swap_rows(matrix_t a, int m, int i)
{
    int tmp;

    for (int k = 0; k < m; k++)
    {
        tmp = a[i][k];
        a[i][k] = a[i + 1][k];
        a[i + 1][k] = tmp;
    }
}

/*
 Функция сортировки элементов строк двумерного массива по убыванию наибольших элементов
 Тип сортировки: пузырьком
 Принимает на вход указатель на массив и его размеры
 Тип данных: int
 Ничего не возвращает
*/

void sort_mtr(matrix_t a, int n, int m)
{
    int max_element_1, max_element_2;

    for (int str_len = 0; str_len < n; str_len++)
        for (int i = 0; i < n - str_len - 1; i++)
        {
            max_element_1 = max_element(a[i], m);
            max_element_2 = max_element(a[i + 1], m);

            if (max_element_1 < max_element_2)
                swap_rows(a, m, i);
        }
}

int main(void)
{
    int status = OK, n, m;
    matrix_t a;

    status = mtr_input(a, &n, &m);
    if (status == OK)
    {
        sort_mtr(a, n, m);
        mtr_print(a, n, m);
    }
    else if (status == RNG_ERR)
        printf("Range error!");
    else if (status == INP_ERR)
        printf("Input error!");
    return status;
}

#include <stdio.h>
#define TRUE 1
#define OK 0
#define FALSE 0
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
 Функция вывода массива
 Принимает на вход указатель на массив и его размер
 Тип данных: int
 Ничего не возвращает
*/

void arr_print(const array_t b, const int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", b[i]);
    }
}

/*
 Функция проверки массива на симметричность
 Принимает на вход указатель на массив и его размер
 Тип данных: int
 Возвращает TRUE, если массив симметричен, FALSE в противном случае
*/

int sym_check(const array_t a, int m)
{
    int flag = TRUE;
    for (int i = 0; flag == TRUE && i < m / 2; i++)
    {
        if (a[i] != a[m - 1 - i])
            flag = FALSE;
    }
    return flag;
}

/*
 Функция формирует массив из 0 и 1 в соотвествии с симметричностью строки
 Принимает на вход: указатель на двумерный массив и его размеры, указатель на новый массив
 Тип данных: int
 Функция ничего не возвращает
*/

void form_array(matrix_t a, array_t b, int n, int m)
{
    for (int k = 0; k < n; k++)
    {
        if (sym_check(a[k], m))
            b[k] = 1;
        else
            b[k] = 0;
    }
}

int main(void)
{
    int n, m, status = OK;
    matrix_t a;
    array_t b;

    status = mtr_input(a, &n, &m);
    if (status == OK)
    {
        form_array(a, b, n, m);
        arr_print(b, n);
    }
    else if (status == RNG_ERR)
        printf("Range error!");
    else if (status == INP_ERR)
        printf("Input error!");

    return status;
}

#include <stdio.h>
#define OK 0
#define RNG_ERR -1
#define INP_ERR -2
#define N_MAX 10
#define M_MAX 10
#define ABS(n) (n < 0) ? -n : n
typedef int matrix_t[N_MAX][M_MAX];

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
        if (2 <= *n && *n <= N_MAX &&
            2 <= *m && *m <= M_MAX)
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
 Функция вычисляет сумму цифр числа
 Принимает на вход число
 Тип данных: int
 Возвращает сумму цифр числа
*/

int dig_sum(int number)
{
    int sum = number % 10;
    while (number > 0)
    {
        number /= 10;
        sum += number % 10;
    }
    return sum;
}

/*
 * Функция ищет минимальный элемент и
   записывает через указатель его строку и столбец
 * Принимает на вход указатель на массив и его размеры,
   указатель на столбец и строку
 * Тип данных: int
 * Ничего не возвращает
*/

void find_min(matrix_t a, int n, int m, int *min_element_row, int *min_element_col)
{
    int min = dig_sum(ABS(a[0][0]));
    *min_element_row = *min_element_col = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (dig_sum(ABS(a[i][j])) < min)
            {
                min = dig_sum(ABS(a[i][j]));
                *min_element_row = i;
                *min_element_col = j;
            }
        }
}

/*
 Функция удаляет из массива определённую строку и столбец
 Принимает на вход указатель на массив и его размеры, искомую строку и столбец
 Тип данных: int
 Ничего не возвращает
 Побочный эффект: уменьшает размеры матрицы на 1
*/

void form_mtr(matrix_t a, int *n, int *m, int min_element_row, int min_element_col)
{
    for (int i = min_element_row; i < *n; i++)
        for (int j = 0; j < *m; j++)
            a[i][j] = a[i + 1][j];

    for (int i = 0; i < *n; i++)
        for (int j = min_element_col; j < *m; j++)
            a[i][j] = a[i][j + 1];
    *n -= 1;
    *m -= 1;
}

int main(void)
{
    int n, m, min_element_row, min_element_col, status = OK;
    matrix_t a;

    status = mtr_input(a, &n, &m);
    if (status == OK)
    {
        find_min(a, n, m, &min_element_row, &min_element_col);
        form_mtr(a, &n, &m, min_element_row, min_element_col);
        mtr_print(a, n, m);
    }
    else if (status == RNG_ERR)
        printf("Range error!");
    else if (status == INP_ERR)
        printf("Input error!");

    return status;
}

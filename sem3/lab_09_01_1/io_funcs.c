#include <stdio.h>
#include <assert.h>
#include "io_funcs.h"
#include "custom_errors.h"

/*
 * Функция вывода матрицы на экран
 * Принимает указатель на структуру
 * Тип данных: matrix_s
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 --- Параметры ---
   [in]  *matrix : указатель первую матрицу
*/
void print_matrix(const matrix_s *matrix)
{
    assert(matrix);

    puts("Result:");
    for (size_t row = 0; row < matrix->cur_rows; row++)
    {
        for (size_t column = 0; column < matrix->cur_columns; column++)
            printf("%" PRId64 " ", matrix->data[row][column]);
        puts("");
    }
    puts("");
}

/*
 * Создания и заполения матрицы с потока ввода
 * Принимает на вход указатель на переменную, содержащую код ошибки
 * Тип данных: matrix_s, int
 * Функция возвращает:
   явно: указатель на область выделенной памяти либо NULL
   неявно: код ошибки
 --- Допущения ---
 * Указатель на переменную, содержащую код ошибки валиден
 --- Параметры ---
   [in]  *status : указатель на переменную, содержащая код ошибки
 [return] : указатель на область памяти либо NULL / код ошибки
*/
matrix_s *create_matrix(int *status)
{
    assert(status);
    
    int rows, columns;
    matrix_s *matrix = NULL;
    *status = OK;
    
    puts("Input n, m:");
    if (scanf("%d%d", &rows, &columns) == 2)
    {
        if (rows < 1 || columns < 1)
            *status = RNG_ERR;
        else
        {    
            matrix = allocate_matrix(rows, columns, status);
            if (*status == OK)
            {   
                puts("Input elements:");

                for (size_t row = 0; row < matrix->cur_rows && *status == OK; row++)
                    for (size_t column = 0; column < matrix->cur_columns && *status == OK; column++)
                        if (scanf("%" PRId64, &matrix->data[row][column]) != 1)
                            *status = READ_ERR;

                if (*status != OK)
                {
                    free_matrix(matrix);
                    matrix = NULL;
                }
            }
        }
    }
    else
        *status = READ_ERR;
    
    return matrix;
}

/*
 * Создания считывания степени с потока ввода
 * Принимает на вход указатель на переменную, куда буде считано значение
 * Тип данных: int
 * Функция возвращает код ошибки либо код успеха
 --- Допущения ---
 * Указатель на переменную валиден
 --- Параметры ---
   [in]  *power : указатель на переменную
 [return] : код ошибки
*/
int get_power(int *power)
{
    assert(power);
    int status = OK;
    
    printf("Input power for matrix: ");
    if (scanf("%d", power) == 1)
    {
        if (*power < 0)
            status = RNG_ERR;
    }
    else
        status = READ_ERR;
    
    return status;
}

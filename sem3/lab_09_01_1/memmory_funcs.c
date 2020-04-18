#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "memmory_funcs.h"

/*
 * Функция удаления одной строки
 * Принимает на вход указатель на структуру и индекс удаляемой строки
 * Тип данных: matrix_s, int
 * Функция возвращает код ошибки
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 * Индекс удаляемой строки не выходит за пределы матрицы
 --- Параметры ---
   [in]  *matrix : указатель матрицу
   [in]   row : индекс удаляемой строки
 [return] : код ошибки
*/
int remove_row(matrix_s *matrix, const int row)
{
    assert(matrix);
    assert(row >= 0 && row < matrix->cur_rows);

    int status = OK;

    // Освобождаем память из под удаляемой строки
    free(matrix->data[row]);

    for (size_t i = row; i < matrix->cur_rows - 1; i++)
        matrix->data[i] = matrix->data[i + 1];
    
    // for (size_t i = row; i < matrix->cur_rows - 1; i++)
        // memmove(matrix->data + i, matrix->data + 1 + i, sizeof(int) * (matrix->cur_rows - i - 1));
    
    // Уменьшаем текущее количество строк
    matrix->cur_rows -= 1;
  
    // Инициализируем временную переменную (контроль ошибок)
    int64_t **tmp;
    
    // Перераспределяем количество памяти (с учётом изменившегося количества строк)
    tmp = realloc(matrix->data, matrix->cur_rows * sizeof(*matrix->data));
    
    // Если удалось перераспределить память
    if (tmp)
    {
        // Меняем указатель на основное поле данных
        matrix->data = tmp;
        
        // Зануляем временную переменную
        tmp = NULL;
    }
    else
        status = MEM_ALLOC_ERR; // Если не удалось перевыделить память

    return status;
}

/*
 * Функция удаления одного столбца
 * Принимает на вход указатель на структуру и индекс удаляемого столбца
 * Тип данных: matrix_s, int
 * Функция возвращает код ошибки
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 * Индекс удаляемого столбца не выходит за пределы матрицы
 --- Параметры ---
   [in]  *matrix : указатель матрицу
   [in]   col : индекс удаляемого столбца
 [return] : код ошибки
*/
int remove_column(matrix_s *matrix, const int col)
{
    assert(matrix);
    assert(col >= 0 && col < matrix->cur_columns);

    int status = OK;

    // Пробегая по всем столбцам "перемещаем" элемент с переданной позиции в конец
    for (size_t i = 0; i < matrix->cur_rows  ; i++)
        memmove(matrix->data[i] + col, matrix->data[i] + col + 1, sizeof(*matrix->data[i]) * (matrix->cur_columns - col - 1));
    
    // Уменьшаем текущее количество столбцов
    matrix->cur_columns -= 1;

    // Проьегая по всем строкам, перевыделяем память с учётом изменившегося количества столбцов
    for (size_t row = 0; row < matrix->cur_rows && status == OK; row++)
    {
        // Инициализируем временную переменную (контроль ошибок)
        int64_t *tmp;
        
        // Перераспределяем количество памяти (с учётом изменившегося количества столбцов)
        tmp = realloc(matrix->data[row], matrix->cur_columns * sizeof(*matrix->data[row]));
        
        // Если удалось перераспределить память
        if (tmp)
        {
            // Меняем указатель на столбец
            matrix->data[row] = tmp;
            
            // Зануляем временную переменную
            tmp = NULL;
        }
        else
            status = MEM_ALLOC_ERR; // Если не удалось перевыделить память
    }
    return status;
}

/*
 * Функция добавления строк
 * Принимает на вход указатель на структуру
 * Тип данных: matrix_s, int
 * Функция возвращает код ошибки
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 * Новая размерность строк больше предыдущей размерности строк
 --- Параметры ---
   [in]  *matrix : указатель матрицу
 [return] : код ошибки
*/
int increase_matrix_rows(matrix_s *matrix)
{
    assert(matrix);
    assert(matrix->cur_rows > matrix->prev_rows);

    int status = OK;
    int64_t **tmp_data, *tmp_row;
    
    tmp_data = realloc(matrix->data, matrix->cur_rows * sizeof(*matrix->data));
    if (tmp_data)
    {
        matrix->data = tmp_data;
        for (size_t row = matrix->prev_rows; row < matrix->cur_rows && status == OK; row++)
        {
            tmp_row = malloc(matrix->cur_columns * sizeof(*matrix->data[row]));
            if (tmp_row)
                matrix->data[row] = tmp_row;
            else
                status = MEM_ALLOC_ERR;            
        }
    }
    else
        status = MEM_ALLOC_ERR; 
    return OK;
}

/*
 * Функция добавления столбцов
 * Принимает на вход указатель на структуру
 * Тип данных: matrix_s, int
 * Функция возвращает код ошибки
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 * Новая размерность столбцов больше предыдущей размерности строк
 --- Параметры ---
   [in]  *matrix : указатель матрицу
 [return] : код ошибки
*/
int increase_matrix_columns(matrix_s *matrix)
{
    assert(matrix);
    assert(matrix->cur_columns >= matrix->prev_columns);
    
    int status = OK;

    for (size_t row = 0; row < matrix->cur_rows; row++)
    {
        int64_t *tmp_col;
        tmp_col = realloc(matrix->data[row], matrix->cur_columns * sizeof(*matrix->data[row]));
        if (tmp_col)
            matrix->data[row] = tmp_col;
        else
           return MEM_ALLOC_ERR;
    }
    return status;
}

/*
 * Функция выделения памяти под структуру с матрицей
 * Принимает на вход количество строк, столбцов и указатель на переменную, содержащую код ошибки
 * Тип данных: matrix_s, int
 * Функция возвращает:
   явно: указатель на область выделенной памяти либо NULL
   неявно: код ошибки
 --- Допущения ---
 * Значения строк и столбцов больше нуля
 * Указатель на переменную, содержащую код ошибки валиден
 --- Параметры ---
   [in]  *matrix : указатель матрицу
 [return] : указатель на область памяти либо NULL / код ошибки
*/
matrix_s *allocate_matrix(const int rows, const int columns, int *status)
{
    assert(rows > 0 && columns > 0);
    assert(status);

    matrix_s *matrix = NULL;
    matrix = (matrix_s*) malloc(sizeof(matrix_s));
    if (matrix)
    {
        matrix->cur_rows = rows;
        matrix->prev_rows = rows;
        matrix->cur_columns = columns;
        matrix->prev_columns = columns;

        matrix->data = (int64_t**) malloc(matrix->cur_rows * sizeof(*matrix->data));
        
        if (matrix->data)
        {
            for (size_t row = 0; row < matrix->cur_rows && *status == OK; row++)
            {
                matrix->data[row] = (int64_t*) malloc(matrix->cur_columns * sizeof(*matrix->data[row]));
                if (!(matrix->data[row]))
                {
                    *status = MEM_ALLOC_ERR;
                    free_matrix(matrix);
                    matrix = NULL;
                }
            }
        }
        else
        {
            *status = MEM_ALLOC_ERR;
            if (matrix)
                free_matrix(matrix);
            
            matrix = NULL;
        }
    }
    else
        *status = MEM_ALLOC_ERR;

    return matrix;
}

/*
 * Функция освобождения памяти, выделенной под структуру с матрицей
 * Принимает на вход указатель на структуру
 * Тип данных: matrix_s
 * Функция ничего не возвращает
 --- Допущения ---
 * В функцию не может быть передан нулевой указатель
 --- Параметры ---
   [in]  *matrix : указатель матрицу
*/
void free_matrix(matrix_s *matrix)
{
    assert(matrix);

    for (size_t row = 0; row < matrix->cur_rows; row++)
        if (matrix->data[row])
            free(matrix->data[row]);
    
    if (matrix->data)
        free(matrix->data);
    
    if (matrix)
        free(matrix);
}

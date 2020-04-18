#include <stdlib.h>
#include <assert.h>
#include "utility_funcs.h"
#include "custom_defines.h"
#define typeof __typeof__
#define SWAP(x, y) do { typeof(x) __TMP__ = x; x = y; y = __TMP__; } while (0)

/*
 * Функция поиска индекса строки и столбца максимального элемента в обходе по строкам
 * Принимает указатель на структуру и на переменные, в которых будут храниться позиции
 * Тип данных: matrix_s, int
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 --- Параметры ---
   [in]  *matrix : указатель на структуру с матрицой
   [in]  *pos_row : указатель на переменную, в которой будет храниться позиция строки 
   [in]  *pos_column : указатель на переменную, в которой будет храниться позиция столбца
*/
void find_max_element_pos(const matrix_s *matrix, int *pos_row, int *pos_column)
{
    assert(matrix && pos_row && pos_column);

    int64_t max = matrix->data[0][0];
    *pos_row = *pos_column = 0;
    for (size_t row = 0; row < matrix->cur_rows; row++)
        for (size_t column = 0; column < matrix->cur_columns; column++)
            if (matrix->data[row][column] > max)
            {
                max = matrix->data[row][column];
                *pos_column = column;
                *pos_row = row;
            }
}

/*
 * Функция поиска значения минимального элемента
 * Принимает указатель на структуру
 * Тип данных: matrix_s, int64_t
 * Функция возвращает код ошибки
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 --- Параметры ---
   [in]  *matrix : указатель на структуру с матрицой
 [return]  min : значение минимального элемента
*/
int64_t find_min_element(const matrix_s *matrix)
{
    assert(matrix);

    int64_t min = matrix->data[0][0];
    
    for (size_t row = 0; row < matrix->prev_rows; row++)
        for (size_t column = 0; column < matrix->prev_columns; column++)
            if (matrix->data[row][column] < min)
                min = matrix->data[row][column];

    return min;
}

/*
 * Функция приведения размеров матрицы к размерам квадратной матрицы путём удаления строк или столбцов
 * Принимает указатель на структуру
 * Тип данных: matrix_s
 * Функция возвращает код ошибки
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 --- Параметры ---
   [in]  *matrix : указатель на структуру с матрицой
 [return] : код ошибки/успеха
*/
int round_matrix(matrix_s *matrix)
{
    assert(matrix);

    int status = OK;
    
    if (matrix->cur_rows != matrix->cur_columns)
    {    
        int diff = ABS(matrix->cur_rows - matrix->cur_columns);
        int pos_row, pos_column;

        for (size_t i = 0; i < diff && status == OK; i++)
        {
            find_max_element_pos(matrix, &pos_row, &pos_column);

            if (matrix->cur_rows < matrix->cur_columns)
                status = remove_column(matrix, pos_column);
            else
                status = remove_row(matrix, pos_row);
        }

        matrix->prev_columns = matrix->cur_columns;
        matrix->prev_rows = matrix->cur_rows;
    }
   
    return status;
}

/*
 * Функция поиска максимального элемента в строке
 * Принимает указатель на структуру, индекс строки поиска
 * Тип данных: matrix_s, int64_t
 * Функция возвращает значение максимально элемента
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 --- Параметры ---
   [in]  *matrix : указатель на структуру с матрицой
   [in]   row : индекс сторки поиска
 [return] : значение максимального элемента
*/
int64_t find_row_max(const int64_t *row, const int row_size)
{
    assert(row);

    int64_t max = row[0];
    for (size_t i = 0; i < row_size; i++)
        if (row[i] > max)
            max = row[i];

    return max;
}

/*
 * Функция поиска среднего арифметического столбца
 * Принимает указатель на структуру, индекс столбца
 * Тип данных: matrix_s, int
 * Функция возвращает среднее арифметическое, округлённое к низу
 --- Допущения ---
 * Индекс столбца не выходит за пределы матрицы
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 --- Параметры ---
   [in]  *matrix : указатель на структуру с матрицой
   [in]   col : индекс столбца
 [return] : среднее арифметическое, округлённое к низу
*/
int64_t find_col_avg(const matrix_s *matrix, const int col)
{
    assert(matrix);
    assert(col >= 0 && col < matrix->prev_columns);

    double avg = (double) find_col_sum(matrix, col) / matrix->prev_rows;
    int64_t result = find_min_element(matrix);

    while (result + 1 <= avg)
        result++;
    
    return result;
}

/*
 * Функция возвращает сумму элементов столбца матрицы
 * Принимает указатель на матрицу и индекс столбца
 * Тип данных: int64_t, size_t
 * Функция возвращает сумму элементов столбца
 --- Допущения ---
 * Индекс столбца не выходит за границы матрицы
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 --- Параметры ---
   [in]  *matrix : указатель на матрицу
   [in]   col : индекс столбца
 [return] : сумма элементов 
*/
int64_t find_col_sum(const matrix_s *matrix, const size_t col)
{
    assert(matrix);
    assert(col >= 0 && col <= matrix->prev_columns);

    int64_t sum = 0;
    for (size_t row = 0; row < matrix->prev_rows; row++)
        sum += matrix->data[row][col];
    
    return sum;
}

int allocate_row(int64_t **row, const int size)
{
    int64_t *tmp = NULL;
    tmp = malloc(size * sizeof(**row));
    if (!tmp)
        return 0;
    *row = tmp;

    return 1;    
}

int64_t *form_row(matrix_s *matrix, int *status)
{
    int64_t *new_row = NULL, col_avg;
            
    if (!allocate_row(&new_row, matrix->cur_rows))
    {
        *status = MEM_ALLOC_ERR;
        return NULL;
    }
            
    for (size_t col = 0; col < matrix->cur_columns; col++)
    {
        col_avg = find_col_avg(matrix, col);
        new_row[col] = col_avg;
    }
    
    return new_row;
}

int insert_row(matrix_s *matrix, int64_t *new_row)
{
    if (!new_row)
        return MEM_ALLOC_ERR;

    free(matrix->data[matrix->prev_rows]);
    matrix->data[matrix->prev_rows] = new_row;

    return OK;
}
/*
 * Функция уравнивания матрицы до размеров второй матрицы (размер вычислен заранее до вызова функции)
 * Принимает указатель на структуру, значение размера
 * Тип данных: matrix_s, int
 * Функция возвращает код ошибки
 --- Допущения ---
 * Количество, на которое будет увеличено число строк и столбцов больше нуля
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 --- Параметры ---
   [in]  *matrix : указатель на структуру с матрицой
   [in]   diff : количество, на которое следует расширить матрицу
 [return] : код ошибки
*/
int equalize(matrix_s *matrix, const int diff)
{
    assert(matrix);
    assert(diff > 0);

    int status = OK;
    int64_t row_max; //, col_avg;
    
    // Увеличиваем текущий размер строк
    matrix->cur_rows += diff;
    
    // Перевыделяем память с учётом нового количества строк
    status = increase_matrix_rows(matrix);
    if (status == OK)
    {   
        // Цикл, от 0 до количества строк, которое требуется добавить
        for (int current_iteration = 0; current_iteration < diff && status == OK; current_iteration++)
        {
            int64_t *new_row;
            
            new_row = form_row(matrix, &status);
            status = insert_row(matrix, new_row);

            // // Цикл от 0 до количества текущих столбцов
            // for (size_t col = 0; col < matrix->cur_columns; col++)
            // {
            //     // Высчитываем среднее арифметическое столбца
            //     col_avg = find_col_avg(matrix, col);

            //     // Вставляем высчитанное значение в конец текущего индекса столбца (col)
            //     matrix->data[matrix->prev_rows][col] = col_avg;
            //     // В качестве последней строки берём значение строк до перевыделения памяти
            // }
            // // Увеличиваем количество строк до перевыделения
            matrix->prev_rows += 1;
        }
    
        // Увеличиваем текущий размер столбцов
        matrix->cur_columns += diff;
        
        // Перевыделяем память с учётом нового количества столбцов
        status = increase_matrix_columns(matrix);
        if (status == OK)
        {
            // Цикл, от 0 до количества столбцов, которое требуется добавить
            for (int current_iteration = 0; current_iteration < diff; current_iteration++)
            {
                // Цикл от 0 до количества текущих строк 
                for (size_t row = 0; row < matrix->cur_rows; row++)
                {
                    // Находим значение максимального элемента в строке
                    row_max = find_row_max(matrix->data[row], matrix->prev_columns);
                    
                    // Вставляем найдененное значение элемента в конец столбца
                    matrix->data[row][matrix->prev_columns] = row_max;
                    // В качестве последнего столбца берём значение столбцов до перевыделения памяти
                }
                // Увеличиваем количество столбцов до перевыделения
                matrix->prev_columns += 1;
            }
        }
    }

    return status;
}
/*
 * Функция копирует содержимое одной матрицы в дугую
 * Принимает указатель на структуры
 * Тип данных: matrix_s
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 * Количество строк и столбцов переданных матриц совпадают
 --- Параметры ---
   [in]  *copy_from : указатель матрицу, содержимое которой будет скопировано
   [in]  *copy_to : указатель на матрицу, куда будет скопировано содержимое
*/
void copy_matrix_data(const matrix_s *copy_from, matrix_s *copy_to)
{
    assert(copy_from && copy_to);
    assert(copy_from->cur_rows == copy_to->cur_rows);
    assert(copy_from->cur_columns == copy_to->cur_columns);

    for (size_t row = 0; row < copy_from->cur_rows; row++)
        for (size_t column = 0; column < copy_from->cur_columns; column++)
            copy_to->data[row][column] = copy_from->data[row][column];
}

/*
 * Функция перемножения матриц
 * Принимает указатель на структуры
 * Тип данных: matrix_s, int
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 * Размерности исходный и результирующей матриц совпадают
 --- Параметры ---
   [in]  *matrix_a : указатель первую матрицу
   [in]  *matrix_b : указатель на вторую матрицу
   [in]  *result_matrix : указатель на матрицу, куда будет помещён результат
*/
void multiply_matrix(const matrix_s *matrix_a, const matrix_s *matrix_b, matrix_s *result_matrix)
{
    assert(matrix_a && matrix_b && result_matrix);
    assert(matrix_a->cur_rows == result_matrix->cur_rows);
    assert(matrix_b->cur_columns == result_matrix->cur_columns);

    for (size_t row = 0; row < matrix_a->cur_rows; row++)
    {
        for (size_t column = 0; column < matrix_b->cur_columns; column++)
        {
            result_matrix->data[row][column] = 0;
            for (size_t k = 0; k < matrix_b->cur_rows; k++)
                result_matrix->data[row][column] += matrix_a->data[row][k] * matrix_b->data[k][column];
        }
    }
}

/*
 * Функция возведения матрицы в степень
 * Результат помещается в исходную матрицу
 * Принимает указатель на структуру и степень
 * Тип данных: matrix_s, int
 * Функция возвращает код ошибки
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 * Значение степени положительное число
 --- Параметры ---
   [in]  *matrix : указатель матрицу
   [in]   pow : значение степени
 [return] : код ошибки
*/
int matrix_pow(matrix_s *matrix, const int power)
{
    assert(matrix);
    assert(power >= 0);

    int status = OK;
    
    if (power == 0)
        turn_matrix_to_unity(matrix);
    else
    {
        matrix_s *result = NULL, *tmp = NULL;

        result = allocate_matrix(matrix->cur_rows, matrix->cur_columns, &status);
        tmp = allocate_matrix(matrix->cur_rows, matrix->cur_columns, &status);
        if (tmp && result)       
        {
            copy_matrix_data(matrix, result);

            for (int i = 0; i < power - 1; i++)
            {               
                multiply_matrix(matrix, result, tmp);
                copy_matrix_data(tmp, result);
            }
            
            copy_matrix_data(result, matrix);
            
            free_matrix(tmp);
            free_matrix(result);
        }
    }
    
    return status;
}

/*
 * Функция превращает матрицу в единичную
 * Принимает указатель на структуру
 * Тип данных: matrix_s
 * Функция ничего не возвращает
 --- Допущения ---
 * Строки матрицы совпадают со столбцами
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 --- Параметры ---
   [in]  *matrix : указатель матрицу
*/
void turn_matrix_to_unity(matrix_s *matrix)
{
    assert(matrix);
    assert(matrix->cur_rows == matrix->cur_columns);

    for (size_t row = 0; row < matrix->cur_rows; row++)
        for (size_t column = 0; column < matrix->cur_columns; column++)
            if (row == column)
                matrix->data[row][column] = 1;
            else
                matrix->data[row][column] = 0;
}

/*
 * Функция превращает транспонирует матрицу
 * Принимает указатель на структуру
 * Тип данных: matrix_s
 * Функция ничего не возвращает
 --- Допущения ---
 * Строки матрицы совпадают со столбцами
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 --- Параметры ---
   [in]  *matrix : указатель матрицу
*/

void transpose(matrix_s *matrix)
{
    assert(matrix);
    assert(matrix->cur_rows == matrix->cur_columns);

    for (size_t row = 1; row < matrix->cur_rows; row++)
        for (size_t column = 0; column < row; column++)
            SWAP(matrix->data[row][column], matrix->data[column][row]);
}

/*
 * Функция перемножения матриц (вторая матрица транспонирована)
 * Принимает указатель на структуры
 * Тип данных: matrix_s, int
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 * Размерности исходный и результирующей матриц совпадают
 --- Параметры ---
   [in]  *matrix_a : указатель первую матрицу
   [in]  *matrix_b : указатель на вторую матрицу
   [in]  *result_matrix : указатель на матрицу, куда будет помещён результат
*/
void multiply_transpose_matrix(const matrix_s *matrix_a, const matrix_s *matrix_b, matrix_s *result_matrix)
{
    assert(matrix_a && matrix_b && result_matrix);
    assert(matrix_a->cur_rows == result_matrix->cur_rows);
    assert(matrix_b->cur_columns == result_matrix->cur_columns);

    for (size_t row = 0; row < matrix_a->cur_rows; row++)
    {
        for (size_t column = 0; column < matrix_b->cur_columns; column++)
        {
            result_matrix->data[row][column] = 0;
            for (size_t k = 0; k < matrix_b->cur_rows; k++)
                result_matrix->data[row][column] += matrix_a->data[row][k] * matrix_b->data[column][k];
        }
    }
}

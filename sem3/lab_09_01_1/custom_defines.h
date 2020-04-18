#ifndef __CUSTOM_DEFINES_H__
#define __CUSTOM_DEFINES_H__

#include <inttypes.h>
/* --- DEFINES --- */

// Код успешного завершения программы
#define OK 0

// Макрос, выполняющий функцию взятия модуля от числа. Может принимать в качестве аргумента выражение
#define ABS(x) ((x) < 0) ? -(x) : (x)

// Описание синонима структуры, содержащей матрицу
typedef struct matrix_s
{
    int cur_rows;      // Текущее количество строк
    int cur_columns;   // Текущее количество столбцов
    int prev_rows;     // Переменная, дублирующая количество строк (используется при расширении матрицы)
    int prev_columns;  // Переменная, дублирующая количество строк (используется при расширении матрицы)
    int64_t **data;    // Поле, содержащее матрицу
} matrix_s;

#endif
#include "io_funcs.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

/*
 * Функция вывода массива на экран
 * Принимает на вход указатели на начало массива и его конец
 * Ничего не возвращает
 --- Допущения ---
 * Массив существует
 * Массив имеет положительный размер
 --- Параметры ---
   [in]  *array : указатель на начало массива
   [in]  *end_array : указатель на конец массива
*/
void print_array(const double *array, const double *end_array)
{
    // массив существует и имеет положительный размер
    assert(array);
    assert(end_array);
    assert(array < end_array);

    printf("Array: ");
    for (const double *pcur = array; pcur < end_array; pcur++)
        printf("%lf ", *pcur);
   // printf("\n");
}

/*
 * Функция ввода массива
 * Считывает исключительно элементы массива
 * Принимает на вход указатели на начало массива и его конец
 * Тип данных: double
 * Вернёт: OK если ввод прошёл успешно, в противном случае код ошибки
 --- Допущения ---
 * Массив существует
 * Массив имеет положительный размер
 --- Параметры ---
   [in]  *array : указатель на начало массива
   [in]  *end_array : указатель на конец массива
 [return] : код ошибки/успеха
*/
int fill_array(double *array, double *end_array)
{
    // массив существует и имеет положительный размер
    assert(array);
    assert(end_array);
    assert(array < end_array);

    double *pcur = array;

    printf("Enter Array: ");
    while ((pcur < end_array) && (scanf("%lf", pcur) == 1))
        pcur++;

    if (pcur != end_array)
        return READ_ERR;
    return OK;
}

/*
 * Функция ввода размера массива
 --- Описание ---
 ** Считывает исключительно размер массива
 ** Размер массива не может быть меньше двух элементов (исходя из постановки задачи)
 --- -- -- -- ---
 * Принимает на вход указатель переменную
 * Тип данных: int
 * Вернёт: OK если ввод прошёл успешно, в противном случае код ошибки
 --- Допущения ---
 * Не требуются
 --- Параметры ---
   [in]  *size : указатель на размер массива
 [return] : код ошибки/успеха
*/
int get_array_size(int *size)
{
    int status = OK;

    printf("Enter size of array: ");
    if (scanf("%d", size) == 1)
    {
        if (*size <= AMOUNT_TO_DELETE)
            status = RNG_ERR_ARR_SIZE;
    }
    else
        status = READ_ERR;

    return status;
}

/*
 * Функция ввода позиции
 --- Описание ---
 ** Считывает позицию и сравнивает её с размером массива
 ** Номер позиции не может превышать количества элементов массива
 --- -- -- -- ---
 * Принимает на вход указатель на переменную и указаель на размер массива
 * Тип данных: int
 * Вернёт: OK если ввод и сравнение прошло успешно, в противном случае код ошибки
 --- Допущения ---
 * Не требуются
 --- Параметры ---
   [in]  *pos : указатель на позицию
   [in]  *size : указатель на размер массива
 [return] : код ошибки/успеха
*/
int get_pos(int *pos, const int size)
{
    int status = OK;

    printf("Enter pos: ");
    if (scanf("%d", pos) == 1)
    {
        if (*pos < 0 || (*pos + 1) > size)
            status = RNG_ERR_POS;
    }
    else
        status = READ_ERR;

    return status;
}

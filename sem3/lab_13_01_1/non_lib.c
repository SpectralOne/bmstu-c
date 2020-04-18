#include <stdio.h>

#include "non_lib.h"

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


/*
 * Функция-обработчик кодов ошибок
 * Принимает на вход код ошибки, распечатывает справку по данному коду
 * Тип данных: int
 * Функция ничего не возвращает
 --- Допущения ---
 * Не требуются
 --- Параметры ---
   [in]   status : код ошбки
*/
void err_handler(const int status)
{
    switch (status)
    {
        case MEM_ALLOC_ERR:
            printf("Memmory allocation/reallocation error!");
            break;
        case READ_ERR:
            printf("I/O Error!");
            break;
        case RNG_ERR_ARR_SIZE:
            printf("Range Error!\n'size' must be greater than 'zero'!\n");
            break;
        case RNG_ERR_POS:
            printf("Range Error!\n'pos' can't be greater than 'size'!\n");
            break;
        case ERR_LIBRARY:
            printf("Library/func load error!\n");
            break;
        case ERR_LOAD:
            printf("Error loading funcs\n");
            break;
    }
}
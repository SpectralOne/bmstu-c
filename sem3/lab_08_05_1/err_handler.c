#include "err_handler.h"
#include <stdio.h>

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
    }
}

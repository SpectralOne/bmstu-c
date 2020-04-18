#include <stdio.h>
#include "err_handler.h"

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
        case RNG_ERR:
            printf("Range Error!\n");
            break;
    }
}

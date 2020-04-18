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
        case 0:
            break;
        case MEM_ALLOC_ERR:
            puts("Memmory allocation/reallocation error!");
            break;
        case READ_ERR:
            puts("I/O Error!");
            break;
        case INV_SEX:
            puts("Invalid sex!");
            break;
        case INV_DATE:
            puts("Invalid date!");
            break;
        case OVERFLOW_ERR:
            puts("String overflow!");
            break;
        case EMPTY_STR:
            puts("Empty string!");
            break;
        case INVALID_SORT_KEY:
            puts("Invalid sort key!");
            break;
        case EMPTY_ARRAY:
            puts("Empty array");
            break;
        case NOT_ENOUGH_FIELDS:
            puts("Not all fields of struct were readed!");
            break;
        case ERR_FILE:
            puts("Open file error!");
            break;
        case INV_STRING:
            puts("Invalid character found!");
            break;
        default:
            printf("Unknown error code: %d\n", status);
            break;
    }
}

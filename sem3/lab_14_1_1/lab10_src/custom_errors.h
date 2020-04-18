#ifndef __CUSTOM_ERRORS_H__
#define __CUSTOM_ERRORS_H__

/* --- ERROR CODES --- */

// Ошибка выделения/перевыделения памяти
#define MEM_ALLOC_ERR -1

// Ошибка чтения потока ввода
#define READ_ERR -2

// Ошибка ввода пола
#define INV_SEX -3

// Ошибка ввода даты
#define INV_DATE -4

// Ошибка переполнения строки
#define OVERFLOW_ERR -5

// Ошибка пустой строки
#define EMPTY_STR -6

// Ошибка пустого массива записей
#define EMPTY_ARRAY -7

// Ошибка ввода имени
#define INV_STRING -8

// Ошибка ввода оценок
#define INV_GRADES -9

// Если вводимая структура уже существует
#define DUPLICATE -10

#endif

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

// Ошибка ключа сортировки (неизвестный ключ)
#define INVALID_SORT_KEY -7

// Ошибка пустого массива записей
#define EMPTY_ARRAY -8

// Ошибка чтения структуры (не все поля прочитаны)
#define NOT_ENOUGH_FIELDS -9

// Ошибка открытия файла
#define ERR_FILE -10

// Код ошибки при недопустимых символах в строке
#define INV_STRING -11

#endif

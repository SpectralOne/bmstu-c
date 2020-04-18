#ifndef __CUSTOM_ERRORS_DEFINES_H__
#define __CUSTOM_ERRORS_DEFINES_H__

/* --- DEFINES --- */

// Точность сравнения двух чисел типа double
#define PRECISION 0.0000000000001

// Количество эелементов для удаления/добавления в массив
#define AMOUNT_TO_DELETE 2
#define AMOUNT_TO_ADD 3

// Обозначения "логического" типа: правда/ложь
#define TRUE 1
#define FALSE 0

// Код успешного завершения программы
#define OK 0

/* --- ERROR CODES --- */

// Ошибка выделения/перевыделения памяти
#define MEM_ALLOC_ERR -1

// Ошибка чтения потока ввода
#define READ_ERR -2

// Ошибка диапазона размерности массива
#define RNG_ERR_ARR_SIZE -3

// Ошибка диапазона позиции
#define RNG_ERR_POS -4

#endif

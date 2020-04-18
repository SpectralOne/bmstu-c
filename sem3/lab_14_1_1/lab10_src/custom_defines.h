#ifndef __CUSTOM_DEFINES_H__
#define __CUSTOM_DEFINES_H__

/* --- DEFINES --- */

// Код успешного завершения программы
#define OK 0

// Код мужского пола
#define MALE 1
// Код женского пола
#define FEMALE 2

// Логический. Нужно ли сортировать
#define DONT_SORT 0
#define SORT 1

// Начальный размер массива структур
#define START_SIZE 2

// Код, сигнализирующий правильность введённой даты
#define VALID 42

#define GRADE_ADDED 12

// Максимальные длины строк
#define MAX_STR_LEN 256
#define MAX_SEX_LEN 6
#define MAX_DATE_LEN 10
#define GRADES_BUF_LEN 6
#define LINE_BUF_LEN 80

// Синоним к типам char
typedef char string_t[MAX_STR_LEN + 1];
typedef char sex_str_t[MAX_SEX_LEN + 1];
typedef char date_str_t[MAX_DATE_LEN + 1];

// Формат, описывающий параметры удаления: пол и максимально допустимый возвраст
#define DELETE_SEX "female"
#define ACCEPTABLE_AGE 17
#define DELETE_FORMAT DELETE_SEX, ACCEPTABLE_AGE

// Формат даты
#define DATE_FORMAT "%Y.%m.%d"

// Символ пробела
#define SPACE_CHAR ' '

// Текущая дата
#define CURRENT_YEAR 2019
#define CURRENT_MONTH 11
#define CURRENT_DAY 1

// Описание синонима структуры оценок
typedef struct
{
    int count;          // Количество
    int *grades_array; // Оценки
} grades_s;

// Описание синонима структуры
typedef struct
{
    char *surname;       // Имя
    char *sex;          // Пол
    char *birth_day;   // Дата рождения
    grades_s *grades; // Структура с оценками
} person_s;

#endif
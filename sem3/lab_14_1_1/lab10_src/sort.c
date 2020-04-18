#include <string.h> // strcmp
#include <assert.h>
#include "sort.h"

// #define SWAP(x, y) do { __typeof__(x) __TMP__ = x; x = y; y = __TMP__; } while (0)

/*
 * Функция обменивает две переменные между собой
 * Принимает на вход указатели на указатели на переменную
 * Тип данных: person_s
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели окажутся валидными и не будут содержать неинициилизированную память
 --- Параметры ---
   [in] **x : указатель на указатель на первую переменную
   [in] **y : указатель на указатель на вторую переменную
*/
void swap(person_s **x, person_s **y)
{ 
    person_s *temp = *x; 
    *x = *y; 
    *y = temp; 
} 

/*
 * Функция-компаратор поля "ФАМИЛИЯ"
 * Принимает на вход два неопределённых указателя на элементы
 * Тип данных: int, person_s
 * Функция возвращает SORT, если первый элемент больше второго, DONT_SORT иначе
 --- Допущения ---
 * Передающиеся указатели окажутся валидными и не будут содержать неинициилизированную память
 --- Параметры ---
   [in]  *item1 : указатель на первый элемент
   [in]  *item2 : указатель на второй элемент
 [return] : признак
*/
int compare_surname(const person_s *item1, const person_s *item2)
{
    assert(item1 && item2);

    if (strcmp(item1->surname, item2->surname) > 0)
        return SORT;
    
    return DONT_SORT;
}

/*
 * Функция-компаратор поля "ПОЛ"
 * Принимает на вход два неопределённых указателя на элементы
 * Тип данных: int, person_s
 * Функция возвращает SORT, если первый элемент больше второго, DONT_SORT иначе
 --- Допущения ---
 * Передающиеся указатели окажутся валидными и не будут содержать неинициилизированную память
 --- Параметры ---
   [in]  *item1 : указатель на первый элемент
   [in]  *item2 : указатель на второй элемент
 [return] : признак
*/
int compare_sex(const person_s *item1, const person_s *item2)
{
    assert(item1 && item2);

    sex_str_t p1_sex, p2_sex;
    
    string_to_lower(p1_sex, item1->sex);
    string_to_lower(p2_sex, item2->sex);
    
    if (strcmp(p1_sex, p2_sex) > 0)
        return SORT;
    
    return DONT_SORT;
}

/*
 * Функция-компаратор поля "ДАТА"
 * Принимает на вход два неопределённых указателя на элементы
 * Тип данных: int, person_s
 * Функция возвращает SORT, если первый элемент больше второго, DONT_SORT иначе
 --- Допущения ---
 * Передающиеся указатели окажутся валидными и не будут содержать неинициилизированную память
 --- Параметры ---
   [in]  *item1 : указатель на первый элемент
   [in]  *item2 : указатель на второй элемент
 [return] : признак
*/
int compare_birth_date(const person_s *item1, const person_s *item2)
{
    assert(item1 && item2);

    if (strcmp(item1->birth_day, item2->birth_day) > 0)
        return SORT;
    
    return DONT_SORT;
}

/*
 * Функция-компаратор поля "ОЦЕНКИ"
 * Принимает на вход два неопределённых указателя на элементы
 * Тип данных: int, person_s
 * Функция возвращает SORT, если первый элемент больше второго, DONT_SORT иначе
 --- Допущения ---
 * Передающиеся указатели окажутся валидными и не будут содержать неинициилизированную память
 --- Параметры ---
   [in]  *item1 : указатель на первый элемент
   [in]  *item2 : указатель на второй элемент
 [return] : признак
*/
int compare_grade_average(const person_s *item1, const person_s *item2)
{
    assert(item1 && item2);

    float average1 = grades_average(item1->grades);
    float average2 = grades_average(item2->grades);

    if (average1 > average2)
        return SORT;
    
    return DONT_SORT;
}

/*
 * Функция сортировки массива структур
 * Алгоритм: обратный пузырёк
 * Принимает указатель на массив структур, размер массива и указатель на функцию-компаратор
 * Тип данных: int, person_s
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели окажутся валидными и не будут содержать неинициилизированную память
 * Размер есть натуральное число
 --- Параметры ---
   [in] **array : указатель на массив структур
   [in]   array_size : размер
   [in]  *compare : указатель на функцию-компаратор
 [return] : признак
*/
void sort_arr(person_s **array, const int array_size, int (*compare)(const person_s *, const person_s *))
{   
    assert(array_size > 0);
    assert(array && compare);

    for (int i = 0; i < array_size; i++)
    {
        int skip = 1;
        for (int j = array_size - 1; j > i; j--)
        {
            if (compare(array[j - 1], array[j]) == SORT)
            {
                swap(&array[j], &array[j - 1]);
                skip = 0;
            }
        }
        if (skip)
            break;
    }
}

/*
 * Функция частичной сортировки массива структур. С переданной позиции. Ровно один проход.
 * Алгоритм: обратный пузырёк
 * Принимает указатель на массив структур, размер массива и указатель на функцию-компаратор
 * Тип данных: int, person_s
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели окажутся валидными и не будут содержать неинициилизированную память
 * Размер есть натуральное число
 --- Параметры ---
   [in] **array : указатель на массив структур
   [in]   array_size : размер
   [in]  *compare : указатель на функцию-компаратор
   [in]   cur_pos : позиция для сортировки
*/
void partial_sort(person_s **array, const int array_size, int (*compare)(const person_s *, const person_s *), const int pos)
{   
    for (int i = pos; i < pos + 1; i++)
    {
        int skip = 1;
        for (int j = array_size - 1; j > i; j--)
        {
            if (compare(array[j - 1], array[j]) == SORT)
            {
                swap(&array[j], &array[j - 1]);
                skip = 0;
            }
        }
        if (skip)
            break;
    }
}
#include <stdlib.h>
#include <assert.h>
#include "memmory_funcs.h"

/*
 * Функция выделения/перевыделения памяти под массив структур
 * Принимает на вход указатель на массив структур (в случае выделения NULL), 
   указатель на переменную с кодом ошибки и размер массива структур
 * Тип данных: person_s, int
 * Функция возвращает:
   явно: указатель на область выделенной памяти либо NULL
   неявно: код ошибки
 --- Допущения ---
 * Размер есть натуральное число
 * Указатель на переменную, содержащую код ошибки валиден
 --- Параметры ---
   [in] **array : указатель на массив структур
   [in]  *status : указатель на переменную с кодом ошибки
   [in]   array_size : размер массива структур
 [return] : указатель на область памяти либо NULL / код ошибки
*/
person_s **reallocate_struct_array(person_s **array, int *status, const int array_size)
{
    assert(array_size > 0);
    assert(status);

    person_s **tmp = NULL;

    tmp = (person_s**) realloc(array, array_size * sizeof(person_s*));
    if (tmp)
    {
        *status = OK;
        return tmp;
    }

    *status = MEM_ALLOC_ERR;
    return NULL;
}

/*
 * Функция выделения памяти под структуру
 * Принимает на вход указатель на переменную с кодом ошибки
 * Тип данных: person_s, grades_s, int
 * Функция возвращает:
   явно: указатель на область выделенной памяти либо NULL
   неявно: код ошибки
 --- Допущения ---
 * Указатель на переменную, содержащую код ошибки валиден
 --- Параметры ---
   [in]  *status : указатель на переменную с кодом ошибки
 [return] : указатель на область памяти либо NULL / код ошибки
*/
person_s *allocate_struct(int *status)
{
    assert(status);

    person_s *kid = NULL;

    kid = (person_s*) malloc(sizeof(person_s));
    if (kid)
    {
        kid->grades = (grades_s*) malloc(sizeof(grades_s));
        if (kid->grades)
        {
            *status = OK;
            return kid;
        }
    }

    *status = MEM_ALLOC_ERR;
    
    return NULL;
}

/*
 * Функция выделения/перевыделения памяти под массив оценок
 * Принимает на вход указатель на массив оценок (в случае выделения NULL), 
   количество оценок (размер) и указатель на переменную с кодом ошибки
 * Тип данных: int
 * Функция возвращает:
   явно: указатель на область выделенной памяти либо NULL
   неявно: код ошибки
 --- Допущения ---
 * Размер есть натуральное число
 --- Параметры ---
   [in]  *array : указатель на массив структур
   [in]   grades_count : количество оценок (размер)
   [in]  *status : указатель на переменную с кодом ошибки
 [return] : указатель на область памяти либо NULL / код ошибки
*/
int *reallocate_grades(int *array, const int grades_count, int *status)
{
    assert(grades_count > 0);

    int *tmp_grades = NULL;
    
    tmp_grades = realloc(array, grades_count * sizeof(int));
    if (tmp_grades)
    {
        *status = OK;
        return tmp_grades;
    }

    *status = MEM_ALLOC_ERR;

    return NULL;
}

/*
 * Функция выделения памяти под строку
 * Принимает на вход количество символов (размер строки) и указатель на переменную с кодом ошибки
 * Тип данных: char, int
 * Функция возвращает:
   явно: указатель на область выделенной памяти либо NULL
   неявно: код ошибки
 --- Допущения ---
 * Количество символов есть натуральное число
 * Указатель на переменную, содержащую код ошибки валиден
 --- Параметры ---
   [in]   char_count : количество символов (размер)
   [in]  *status : указатель на переменную с кодом ошибки
 [return] : указатель на область памяти либо NULL / код ошибки
*/
char *allocate_string(const int char_count, int *status)
{
    assert(char_count > 0);
    assert(status);

    char *tmp = NULL;
    
    tmp = malloc((char_count + 1) * sizeof(char));
    if (tmp)
    {
        *status = OK;
        tmp[0] = 0;

        return tmp;
    }

    *status = MEM_ALLOC_ERR;

    return NULL;
}

/*
 * Функция освобождения памяти, выделенной под структуру
 * Принимает на вход указатель на структуру
 * Тип данных: person_s
 * Функция ничего не возвращает
 --- Допущения ---
 * В функцию не может быть передан нулевой указатель
 --- Параметры ---
   [in]  *kid : указатель на структуру
*/
void free_struct(person_s *kid)
{
    assert(kid);

    if (kid->surname)
        free(kid->surname);
    if (kid->sex)
        free(kid->sex);
    if (kid->birth_day)
        free(kid->birth_day);
    if (kid->grades->grades_array)
        free(kid->grades->grades_array);

    free(kid->grades);
    free(kid);
}

/*
 * Функция освобождения памяти, выделенной под массив структур
 * Принимает на вход указатель на массив структур и его размер
 * Тип данных: person_s, int
 * Функция ничего не возвращает
 --- Параметры ---
   [in] **array : указатель на массив структур
   [in]   array_size : размер массива
*/
void free_struct_array(person_s **array, const int array_size)
{
    if (array)
    {
        for (int i = 0; i < array_size; i++)
        {
            if (array[i])
                free_struct(array[i]);
        }
        free(array);
    }
}
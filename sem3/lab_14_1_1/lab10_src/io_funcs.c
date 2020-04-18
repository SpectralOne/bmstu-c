#include <assert.h>
#include <string.h>
#include <stdlib.h> // free
#include "io_funcs.h"

/*
 * Функция чтения строки из потока ввода.
 * Принимает на вход указатель на строку, куда будет считан ввод
 * Тип данных: int, string_t
 * Функция возвращает код ошибки / успеха
 --- Допущения ---
 * Передающиеся указатели валидны
 * Tип строки определён как string_t длиной 255 + 1
 --- Параметры ---
   [in]   string : указатель на строку
 [return] : код ошибки / успеха
*/
int read_string(string_t string, FILE *f)
{
    assert(string);

    int status = OK;

    if (fgets(string, sizeof(string_t), f) == NULL)
        status = READ_ERR;
    else if (string[strlen(string) - 1] != '\n')
        status = OVERFLOW_ERR;
    else
    {
        string[strlen(string) - 1] = '\0';
        if (strlen(string) == 0)
            status = EMPTY_STR;
    }
    return status;
}

/*
 * Функция считывания оценок из строки в структуру
 * Принимает на вход указатель структуру, куда следует считать оценки и указатель на строку с оценками
 * Тип данных: grades_s, char
 * Функция возвращает код ошибки / успеха
 --- Допущения ---
 * Передающиеся указатели валидны
 * Передающаяся структура содержит поля для хранения оценок
 --- Параметры ---
   [in]  *grades  : указатель на структуру
   [in]  *grades_string : указатель на строку оценок
 [return] : код ошибки / успеха
*/
int read_grades(grades_s *grades, char *grades_string)
{
    assert(grades && grades_string);

    int i = 0, status = OK;
    char *token = strtok(grades_string, " ");
    grades->count = atoi(token);

    grades->grades_array = reallocate_grades(NULL, grades->count, &status);

    if (status == OK)
        while (token != NULL) 
        {
            token = strtok(NULL, " ");
            if (token)
            {
                grades->grades_array[i] = atoi(token);
                i++;
            }
        }   

    return status;
}

/*
 * Функция заполнения полей структуры
 * Принимает на вход указатель структуру и данные для полей
 * Тип данных: grades_s, char
 * Функция возвращает код ошибки / успеха
 --- Допущения ---
 * Передающиеся указатели валидны
 * Передающаяся структура содержит поля для данных
 --- Параметры ---
   [in]  *kid  : указатель на структуру
   [in]  *surname : указатель на строку фамилии
   [in]  *sex : указатель на строку пола
   [in]  *date: указатель на строку даты
   [in]  *grades: указатель на строку оценок
 [return] : код ошибки / успеха
*/
int fill_record(person_s *kid, char *surname, char *sex, char *date, char *grades)
{
    assert(kid && surname && sex && date && grades);

    int status = OK;

    kid->surname = NULL;
    kid->sex = NULL;
    kid->birth_day = NULL;
    kid->grades->grades_array = NULL;

    kid->surname = allocate_string(strlen(surname), &status);
    if (kid->surname)
    {
        strcpy(kid->surname, surname);
        kid->sex = allocate_string(strlen(sex), &status);
        if (kid->sex)
        {
            strcpy(kid->sex, sex);
            kid->birth_day = allocate_string(strlen(date), &status);
            if (kid->birth_day)
            {
                strcpy(kid->birth_day, date);
                status = read_grades(kid->grades, grades);
            }
        }
    }

    return status;
}

/*
 * Функция сравнения двух структур
 * Принимает на вход указатели на структуры
 * Тип данных: person_s
 * Функция возвращает 1, если структуры равны, 0 - иначе
 --- Допущения ---
 * Передающиеся указатели валидны
 * Передающаяся структура содержит поля для данных
 --- Параметры ---
   [in]  *person1  : указатель на структуру
   [in]  *person2  : указатель на структуру
 [return] : признак равенства
*/
int is_equal(person_s *person1, person_s *person2)
{
    assert(person1 && person2);

    if (strcmp(person1->surname, person2->surname) == 0)
        if (strcmp(person1->sex, person2->sex) == 0)
            if (strcmp(person1->birth_day, person2->birth_day) == 0)
                if (person1->grades->count == person2->grades->count)
                    for (int i = 0; i < person1->grades->count; i++)
                        if (person1->grades->grades_array[i] != person2->grades->grades_array[i])
                            return 0;
    return 1;
}

/*
 * Функция поиска структуры в массива
 * Принимает на вход указатель на массив, его размер и указатель на структуру
 * Тип данных: person_s, int
 * Функция возвращает 1, если структура найдена, 0 - иначе
 --- Допущения ---
 * Передающиеся указатели валидны
 * Передающаяся структура содержит поля для данных
 --- Параметры ---
   [in] **arr  : указатель на массив
   [in]   size : размер массива
   [in]  *person : указатель на структуру
 [return] : признак найдено/не найдено
*/
int find_in_arr(person_s **arr, int size, person_s *person)
{
    assert(arr && person);
    assert(size);

    for (int i = 0; i < size; i++)
        if (is_equal(arr[i], person))
            return 1;
    return 0;
}
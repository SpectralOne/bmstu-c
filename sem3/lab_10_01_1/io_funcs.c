#include <assert.h>
#include <string.h>
#include <stdlib.h> // free
#include "io_funcs.h"

/*
 * Функция печати массива оценок в файл
 * Принимает на вход количество оценок, указатель на массив оценок и файловую переменную
 * Тип данных: grades_s, FILE
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели валидны
 * Количество оценок есть натуральное число
 * Передающаяся файловая переменная валидная
 --- Параметры ---
   [in]  *grades : указатель на структуру с оценками
   [in]  *f : файловая переменная
*/
void print_marks(grades_s *grades, FILE *f)
{
    assert(grades && f);
    assert(grades->count > 0);

    fprintf(f, "%d ", grades->count);
    for (int i = 0; i < grades->count; i++)
        fprintf(f, "%d ", grades->grades_array[i]);
}

/*
 * Функция печати структуры в файл
 * Принимает на вход указатель на структуру и файловую переменную
 * Тип данных: person_s, FILE
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели валидны
 * Передающаяся файловая переменная валидная
 --- Параметры ---
   [in]  *kid : указатель на структуру
   [in]  *f : файловая переменная
*/
void print_struct(const person_s *kid, FILE *f)
{
    assert(kid && f);

    fprintf(f, "%s\n", kid->surname);
    fprintf(f, "%s\n", kid->sex);
    fprintf(f, "%s\n", kid->birth_day);
    print_marks(kid->grades, f);
    fprintf(f, "\n");
}

/*
 * Функция печати массива структур в файл
 * Принимает на вход указатель на массив структур, его размер и файловую переменную
 * Тип данных: person_s, int, FILE
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели валидны
 * Размер массива есть натуральное число
 * Передающаяся файловая переменная валидная
 --- Параметры ---
   [in] **array : указатель на массив структур
   [in]   array_size : размер массива
   [in]  *f : файловая переменная
*/
void print_struct_array(person_s **array, const int array_size, FILE *f)
{
    assert(array && f);
    assert(array_size > 0);

    for (int i = 0; i < array_size; i++)
        print_struct(array[i], f);
}

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
int read_string(string_t string)
{
    assert(string);

    int status = OK;

    if (fgets(string, sizeof(string_t), IN_FILE) == NULL)
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
 * Функция оценок с потока ввода
 * Принимает на вход указатель структуру, куда следует считать оценки
 * Тип данных: grades_s
 * Функция возвращает код ошибки / успеха
 --- Допущения ---
 * Передающиеся указатели валидны
 * Передающаяся структура содержит поля для хранения оценок
 --- Параметры ---
   [in]  *grades  : указатель на структуру
 [return] : код ошибки / успеха
*/
int read_grades(grades_s *grades)
{
    assert(grades);

    int status = READ_ERR;
    
    if (fscanf(IN_FILE, "%d", &grades->count) == 1 && grades->count > 0)
    {
        grades->grades_array = reallocate_grades(NULL, grades->count, &status);
        if (grades->grades_array && status == OK)
        {
            for (size_t count = 0; count < grades->count && status == OK; count++)
                if (fscanf(IN_FILE, "%d", &grades->grades_array[count]) != 1 || grades->grades_array[count] <= 0 || grades->grades_array[count] > 10)
                    status = READ_ERR;
        }
    }

    return status;
}

/*
 * Функция чтения одной структуры с потока ввода
 * Принимает на вход указатель на структуру, куда будет считан ввод
 * Тип данных: int, person_s
 * Функция возвращает код ошибки / успеха
 --- Допущения ---
 * Передающиеся указатели валидны
 --- Параметры ---
   [in]  *kid : указатель на структуру
 [return] : код ошибки / успеха
*/
int read_kid_info(person_s *kid)
{
    assert(kid);

    char tmp[4];
    string_t buf;
    int status = READ_ERR;

    kid->surname = NULL;
    kid->sex = NULL;
    kid->birth_day = NULL;
    kid->grades->grades_array = NULL;
    
    status = read_string(buf);
    if (status == OK && strcmp(buf, STOP_SURNAME) == 0)
        return END_OF_INPUT;

    if (status == OK)
    {
        status = check_string(buf);
        if (status == OK)
        {
            kid->surname = allocate_string(strlen(buf), &status);
            if (kid->surname)
            {
                strcpy(kid->surname, buf);
                
                status = read_string(buf);
                if (status == OK)
                {
                    status = check_sex_string(buf);
                    if (status == MALE || status == FEMALE)
                    {
                        kid->sex = allocate_string(strlen(buf), &status);
                        if (kid->sex)
                        {
                            strcpy(kid->sex, buf);

                            status = read_string(buf);
                            if (status == OK)
                            {
                                status = check_date_string(buf, DATE_FORMAT);
                                if (status == VALID)
                                {
                                    kid->birth_day = allocate_string(strlen(buf), &status);
                                    if (kid->birth_day)
                                    {
                                        strcpy(kid->birth_day, buf);

                                        status = read_grades(kid->grades);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (status == OK)
        fgets(tmp, sizeof(tmp), stdin);

    return status;
}

/*
 * Функция чтения массива структур с потока ввода. 
 ** Память может увеличиваться по мере заполнения. По окончанию ввода массив сжимается.
 * Принимает на вход указатель на массив структур, его размер и переменную, содержащую код ошибки
 * Тип данных: int, person_s
 * Функция возвращает указатель на область памяти / NULL
 --- Допущения ---
 * Передающиеся указатели валидны
 --- Параметры ---
   [in]  *size : указатель на размер
   [in]  *status : переменная с кодом ошибки
 [return] : код ошибки / успеха
*/
person_s **get_struct_array(int *array_size, int *status) 
{    
    assert(array_size && status);

    *status = EMPTY_ARRAY;
    person_s *temp_struct = NULL;
    person_s **struct_array = NULL;

    // Starting size
    *array_size = START_SIZE;

    struct_array = reallocate_struct_array(NULL, status, *array_size);
    if (struct_array && *status == OK)
    {
        int current_array_size = 0;
        // Reading stream
        do
        {
            temp_struct = allocate_struct(status); 
            if (temp_struct && *status == OK)
            {
                *status = read_kid_info(temp_struct);
                if (temp_struct && *status == OK)
                {
                    // In case when we need addictional memmory for storing structures
                    if (current_array_size == *array_size)
                    {
                        // Allocate size x2
                        *array_size *= 2;

                        person_s **tmp = reallocate_struct_array(struct_array, status, *array_size);
                        if (tmp && *status == OK)
                            struct_array = tmp;
                    }   
           
                    struct_array[current_array_size++] = temp_struct;
                }
            }
        } 
        while (*status == OK);

        // Free allocated resources
        if (temp_struct)
            free_struct(temp_struct);
        
        // Replacing 'END_OF_INPUT' with OK
        if (*status == END_OF_INPUT)
            *status = OK;

        // Processing size
        if (!current_array_size)
        {
            free(struct_array); // Free allocated array
            struct_array = NULL;
            *status = EMPTY_ARRAY;
        }
        else
            *array_size = current_array_size;

        // Array compression
        if (current_array_size && *status == OK)
            *status = compress_array(&struct_array, current_array_size, *array_size);

        return struct_array;
    }

    return NULL;    
}

/*
 * Функция сжатия массива
 * Принимает на вход указатель на указатель массив структур и размер, до которого нужно сжать
 * Тип данных: int, person_s
 * Функция возвращает код ошибки / успеха
 --- Допущения ---
 * Передающиеся указатели валидны
 * Размер есть натуральное число
 --- Параметры ---
   [in] ***array : указатель на указатель на массив
   [in]    size : размер, до которого нужно сжать
 [return] : код ошибки / успеха
*/
int compress_array(person_s ***array, const int curr_size, const int prev_size)
{
    assert(array && *array);
    assert(curr_size > 0 && prev_size > 0);

    if (curr_size == prev_size)
        return OK;

    int status = MEM_ALLOC_ERR;

    person_s **tmp = reallocate_struct_array(*array, &status, curr_size);
    if (status == OK)
        *array = tmp;

    return status;
}

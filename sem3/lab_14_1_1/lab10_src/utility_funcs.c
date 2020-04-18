#include <string.h>     // strlen, strcmp, strtok
#include <ctype.h>     // tolower
#define __USE_XOPEN   // for time.h
#include <time.h>    // mktime, strptime, strftime
#include <stdlib.h> // atoi
#include <assert.h>
#include "utility_funcs.h"

/*
 * Функция удаляет структуру с переданной позиции
 * Принимает указатель на массив структур, его размер и позицию
 * Тип данных: person_s, int
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями person_s валидны и не содержат неинициализированную память
 * Размер есть число натуральное
 * Значение позиции не может выйти за границы массива
 --- Параметры ---
   [in] **array : указатель на массив структур
   [in]   array_size : размер массива структур
   [in]   pos : позиция удаляемой структуры
*/
void delete_struct_by_pos(person_s **array, const int array_size, const int pos)
{
    assert(array_size > 0);
    assert(pos >= 0 && pos < array_size);
    assert(array);

    free_struct(array[pos]);

    for (int i = pos; i < array_size - 1; i++)
        array[i] = array[i + 1];
}

/*
 * Функция выделяет из строки с датой год, месяц и день
 * Принимает: указатель на строку с датойб а также указатели где будут хранится год, месяц, день
 * Тип данных: date_str_t, int
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели валидны
 * Дата соответствует формату DATE_FORMAT и является валидной
 --- Параметры ---
   [in]   date : строка с датой
   [in]  *b_year : указатель на переменную, где будет хранится год
   [in]  *b_month : указатель на переменную, где будет хранится месяц
   [in]  *b_day : указатель на переменную, где будет хранится день
*/
void split_date(const date_str_t date, int *b_year, int *b_month, int *b_day)
{
    char *cur;
    date_str_t tmp_date;
    
    strcpy(tmp_date, date);
    cur = strtok(tmp_date, ".");
    if (cur)
    {
        *b_year = atoi(cur);
        cur = strtok(NULL, ".");
        if (cur)
        {
            *b_month = atoi(cur);
            cur = strtok(NULL, ".");
            if (cur)
                *b_day = atoi(cur);
        }
    }
}

/*
 * Функция вычисляет возраст (на момент CURRENT_YEAR, CURRENT_MONTH, CURRENT_DAY) по дате рождения
 * Принимает: указатель на строку с датой
 * Тип данных: date_str_t
 * Функция возвращает возвраст
 --- Допущения ---
 * Передающиеся указатели валидны
 * Дата соответствует формату DATE_FORMAT и является валидной
 --- Параметры ---
   [in]   date : строка с датой
 [return] : возраст
*/
int calculate_person_age(const date_str_t date)
{
    assert(check_date_string(date, DATE_FORMAT) == VALID);
    
    int current_year = CURRENT_YEAR, current_month = CURRENT_MONTH, current_day = CURRENT_DAY;
    
    int b_year, b_month, b_day;

    split_date(date, &b_year, &b_month, &b_day);

    if (b_day > current_day) 
        current_month -= 1;
  
    if (b_month > current_month) 
        current_year -= 1; 

    return current_year - b_year;
}

/*
 * Функция удаляет всех девушек старше 17 лет из массива структур
 * Принимает: указатель на указатель на массив структур, указатель его размер,
 *            призак-пол и признак-возраст удаления
 * Тип данных: person_s, int
 * Функция возвращает код ошибки
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями person_s валидны и не содержат неинициализированную память
 * Размер есть число натуральное
 --- Параметры ---
   [in] **array : указатель на массив структур
   [in]  *array_size : указатель на размер массива структур
   [in]   sex : призак-пол
   [in]   acceptable_age : признак-возраст
 [return] : код ошибки
*/
int normalize_array(person_s ***array, int *array_size, const sex_str_t delete_sex, const int acceptable_age)
{
    assert(*array_size > 0);
    assert(array && array_size);

    int status = OK;
    person_s **tmp;
    for (int i = 0; i < *array_size && status == OK; i++)
    {
        sex_str_t sex_tmp;
        string_to_lower(sex_tmp, (*array)[i]->sex);
        if ((strcmp(sex_tmp, delete_sex) == 0) && (calculate_person_age((*array)[i]->birth_day) > acceptable_age))
        {
            if (!(*array_size - 1))
                status = EMPTY_ARRAY; 

            if (status == OK)
            {
                delete_struct_by_pos(*array, *array_size, i);
                *array_size -= 1;
            }
            i--;
        }
    }
    if (status == OK)
    {
        tmp = reallocate_struct_array(*array, &status, *array_size);
        if (tmp && status == OK)
            *array = tmp;
    }

    return status;
}

/*
 * Функция добавляет оценку 3 ко всем школьникам
 * Принимает указатель на указатель на массив структур и его размер
 * Тип данных: person_s, int
 * Функция возвращает код ошибки
 --- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями person_s валидны и не содержат неинициализированную память
 * Размер есть число натуральное
 --- Параметры ---
   [in] **array : указатель на массив структур
   [in]   array_size : размер массива структур
 [return] : код ошибки
*/
int add_three_all(person_s **array, const int array_size)
{
    assert(array_size > 0);
    assert(array);

    int status = GRADE_ADDED;

    for (int i = 0; i < array_size; i++)
    {
        int *tmp;
        array[i]->grades->count += 1;
        tmp = reallocate_grades(array[i]->grades->grades_array, array[i]->grades->count, &status);
        if (tmp)
        {
            array[i]->grades->grades_array = tmp;
            array[i]->grades->grades_array[array[i]->grades->count - 1] = 3;
        }
    }
    return status;
}

/*
 * Функция находит среднее арифметическое оценок 
 * Принимает указатель на структуру
 * Тип данных: person_s, float
 * Функция возвращает среднее арифметическое
 --- Допущения ---
 * Передающиеся указатели валидны
 --- Параметры ---
   [in]  *kid : указатель на структуру
 [return] : среднее арифметическое оценок 
*/
float grades_average(const grades_s *grades)
{
    assert(grades);

    float sum = 0;

    for (int i = 0; i < grades->count; i++)
        sum += grades->grades_array[i];

    return sum / grades->count;
}

/*
 * Функция переводит строку в нижний регистр (результат помещается в переданную строку)
 * Принимает указатель на строку, куда будет записан результат и указатель на исходную строку
 * Тип данных: char
 * Функция ничего не возвращает
 --- Допущения ---
 * Передающиеся указатели валидны
 * Передающиеся строки валидны и имеют одинаковый размер
 --- Параметры ---
   [in]  *destination_str : указатель на строку, куда будет записан результат
   [in]  *source_str : указатель на исходную строку
*/
void string_to_lower(char *destination_str, const char *source_str)
{
    assert(destination_str && source_str);

    size_t string_len = strlen(source_str);
    size_t i = 0;
    
    for (; i < string_len; i++)
        destination_str[i] = tolower(source_str[i]);

    destination_str[i] = '\0';
}

/*
 * Функция проверки строки "ПОЛ" на валидность
 * Принимает указатель на строку
 * Тип данных: char, int
 * Функция возвращает:
   -3 : невалидный пол
    2 : если пол женский
    1 : если пол мужской
 --- Допущения ---
 * Передающиеся указатели валидны
 * Передающаяся строка валидна
 --- Параметры ---
   [in]  *string : указатель на строку
 [return] : числовое значение, соответствующее ситуации
*/
int check_sex_string(const string_t string)
{
    assert(string);

    int sex = INV_SEX;

    if (strlen(string) < 7 && strlen(string) > 3)
    {
        sex_str_t tmp_sex;
        string_to_lower(tmp_sex, string);

        if (strcmp(tmp_sex, "male") == 0)
            sex = MALE;
        else if (strcmp(tmp_sex, "female") == 0)
            sex = FEMALE;
    }

    return sex;
}

/*
 * Функция проверки строки "ДАТА" на валидность
 * Принимает указатель на строку
 * Тип данных: char, int
 * Функция возвращает VALID, если дата валидна, код ошибки иначе
 --- Допущения ---
 * Передающиеся указатели валидны
 * Передающаяся строка валидна
 --- Параметры ---
   [in]  *string : указатель на строку
 [return] : числовое значение, соответствующее ситуации
*/
int check_date_string(const string_t string, const char *format)
{
    assert(string);

    int date_status = INV_DATE;

    if (strlen(string) == 10)
    {
        // const char min_school_age[] = "2013.11.01";
        const char good_old_times[] = "1990.11.01";
        date_str_t converted_string, mktime_string;
        struct tm date = { 0 };
        
        strptime(string, format, &date);
        strftime(converted_string, sizeof(converted_string), format, &date);
        
        mktime(&date);
        strftime(mktime_string, sizeof(mktime_string), format, &date);

        // Valid date
        if (strcmp(mktime_string, converted_string) == 0)
            date_status = VALID;
        
        // Not too young
        // if (strcmp(mktime_string, min_school_age) > 0)
            // date_status = INV_DATE;
        
        // Not too old
        if (strcmp(mktime_string, good_old_times) < 0)
            date_status = INV_DATE;
    }

    return date_status;
}

/*
 * Функция проверки строки на валидность
 * Принимает указатель на строку
 * Тип данных: int, string_t
 * Функция возвращает OK, если строка валидна, код ошибки иначе
 --- Допущения ---
 * Передающиеся указатели валидны
 * Tип строки определён как string_t длиной 255 + 1
 --- Параметры ---
   [in]  *string : указатель на строку
 [return] : числовое значение, соответствующее ситуации
*/
int check_string(const string_t string)
{
    assert(string);
    
    const char *cur = string;
    if (!isupper(*cur))
        return INV_STRING;

    cur++;
    for (; cur && *cur != '\0'; cur++)
        if (isalpha(*cur) && !isupper(*cur))
            continue;
        else 
            return INV_STRING;

    return OK;
}

/*
 * Функция проверки строки содержание только чисел и пробелов
 * Принимает указатель на строку
 * Тип данных: char
 * Функция возвращает OK, если строка валидна, код ошибки иначе
 --- Допущения ---
 * Передающиеся указатели валидны
 --- Параметры ---
   [in]  *string : указатель на строку
 [return] : числовое значение, соответствующее ситуации
*/
int digits_space_only(char *string)
{
    while (*string) 
    {
        if (isdigit(*string++) == 0)
            if (*(string - 1) != SPACE_CHAR) 
                return 0;
    }

    return 1;
}

/*
 * Функция проверки строки оценок на валидность
 * Принимает указатель на строку
 * Тип данных: char
 * Функция возвращает OK, если строка валидна, код ошибки иначе
 --- Допущения ---
 * Передающиеся указатели валидны
 --- Параметры ---
   [in]  *string : указатель на строку
 [return] : числовое значение, соответствующее ситуации
*/
int check_grades(char *grades)
{   
    if (!grades)
        return INV_GRADES;

    if (digits_space_only(grades))
    {
        int count, buf, real = 0;

        char *token = strtok(grades, " ");
        if (token)
        {
            count = atoi(token);
            if (count < 1)
                return INV_GRADES;
        }

        while (token != NULL) 
        {
            token = strtok(NULL, " ");
            if (token)
            {
                buf = atoi(token);
                if (buf < 1)
                    return INV_GRADES;
                real++;
            }
        }            
        if (count)
            if (count == real)
                return OK;
    }
    return INV_GRADES;
}
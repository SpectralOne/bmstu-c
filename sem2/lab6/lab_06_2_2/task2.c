#include <stdio.h>
#include <string.h>
#define OK 0
#define EMPTY_STR -1
#define STR_OVERFLOW -2
#define INP_ERR -3
#define MAX_WORD_LEN_ERR -4
#define MAX_STR_LEN 256
#define MAX_WORD_LEN 16
typedef char word_arr_t[MAX_STR_LEN / 2][MAX_WORD_LEN + 1];
typedef char string_t[MAX_STR_LEN + 1];

/*
 Функция определяет является ли символ разделителем
 Принимает на вход символ
 Тип данных: char
 Возвращает 1 если символ - разделитель, иначе 0
*/
int is_delimiter(char ch)
{
    char delimiter_list[] = ",;:-.!? ";
    char *p = strchr(delimiter_list, ch);
    if (p)
        return 1;
    return 0;
}

/*
 Функция удаляет повторяющиеся слова из массива
 Принимает на вход указатель на массив и его размер
 Тип данных: char
 Функция ничего не возвращает
*/
void remove_duplicates(word_arr_t word_arr, int *size)
{
    int i = 0, j = 0, k = 0, len = *size;
    // Цикл от первого элемента до последнего (гаранирован проход по всем элементам)
    for (i = 0; i < len; i++)
    {
        // Цикл от второго элемента до конца
        for (j = i + 1; j < len;)
        {
            // Если найдено повторяющееся слово
            if (strcmp(word_arr[i], word_arr[j]) == 0)
            {
                // Перекопировать по очереди все слова на одну позицию влево
                for (k = j; k < len - 1; k++)
                    strcpy(word_arr[k], word_arr[k + 1]);
                len -= 1; // Уменьшить общее количество элементов
            }
            else
                j++;
        }
    }
    *size = len;
}

/*
 Функция ищет точное вхождение слова в строку
 Получает на вход указатель на строку и слово
 Тип данных: char
 Вернёт 1 если найдено полное соответсвие, в противном случае 0
 Допущения: слова должны быть разделены одним пробелом
*/
int word_checker(const string_t str, const char *word)
{
    const char *p = NULL;
    int len = strlen(word);

    if (len > 0)
    {
        for (p = str; (p = strstr(p, word)) != NULL; p++)
        {
            if (p == str || is_delimiter(p[-1]))
            {
                if (is_delimiter(p[len]))
                    return 1;
                p += len;
            }
        }
    }
    return 0;
}

/*
 Функция определяет начальную и конечную позицию первого слова в строке
 Получает на вход указатель на строку, начальную позицию и конечную позицию
 Тип данных: char, int
 Вернёт 1 в случае успешного определения или 0 в случае, если достигнуть конец строки
*/
int get_word_pos(const string_t str, int *start_pos, int *end_pos)
{
    while (!str[*start_pos] || is_delimiter(str[*start_pos]))
    {
        if (str[*start_pos] == '\0')
            return 0;
        *start_pos += 1;
    }
    *end_pos = *start_pos;
    while (str[*end_pos] && !is_delimiter(str[*end_pos]))
    {
        if (str[*end_pos] == '\0')
            return 0;
        *end_pos += 1;
    }
    return 1;
}

/*
 Функция получает из строки двумерный массив слов
 Получает на вход указатель на начало строки и массив
 Тип данных: char
 Вернёт ОК если всё успешно, в противном случае вернёт код ошибки
*/

int get_word_arr(string_t str, word_arr_t word_arr, int *size)
{
    int start_pos = 0, end_pos = 0, flag = 1, status = OK;
    *size = 0;

    while (get_word_pos(str, &start_pos, &end_pos) && flag)
    {
        if ((end_pos - start_pos) < MAX_WORD_LEN)
        {
            strncpy(word_arr[*size], str + start_pos, end_pos - start_pos);
            word_arr[*size][end_pos - start_pos] = '\0';
            *size += 1;
            start_pos = end_pos;
        }
        else
        {
            flag = 0;
            status = MAX_WORD_LEN_ERR;
        }
    }
    if (!*size)
        status = EMPTY_STR;

    return status;
}

/*
 Функция ввода строки
 Получает на вход указатель на строку
 Тип данных: char
 Возвращает ОК в случае успеха, иначе код ошибки
*/
int input_string(string_t string)
{
    int status = OK;

    if (fgets(string, sizeof(string_t), stdin) == NULL)
        status = INP_ERR;
    else if (string[strlen(string) - 1] != '\n')
        status = STR_OVERFLOW;
    else
    {
        string[strlen(string) - 1] = '\0';
        if (strlen(string) == 0)
            status = EMPTY_STR;
    }
    return status;
}

int main(void)
{
    int size, status = OK;
    string_t str1, str2;
    word_arr_t word_arr;

    printf("Input first string: ");
    status = input_string(str1);
    if (status == OK)
    {
        status = get_word_arr(str1, word_arr, &size);
        if (status == OK)
        {
            printf("Input second string: ");
            status = input_string(str2);
            if (status == OK)
            {
                remove_duplicates(word_arr, &size);
                printf("Result:\n");
                for (int i = 0; i < size; i++)
                {
                    if (word_checker(str2, word_arr[i]))
                        printf("%s yes\n", word_arr[i]);
                    else
                        printf("%s no\n", word_arr[i]);
                }
            }
        }
    }
    return status;
}

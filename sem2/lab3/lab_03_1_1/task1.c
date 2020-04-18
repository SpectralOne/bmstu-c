#include <stdio.h>
#define OK 0
#define NO_RESULT -1
#define INP_ERR -2

/*
 Функция ищет два максимальных числа последовательности
 Считывает числа из файла
 Принимает на вход файл и указатель на числа
 Тип данных: int
 Вернёт: OK если операция прошла успешно, в противном случае код ошибки
*/
int process(FILE* f, int *result1, int *result2)
{
    int number, tmp, status = INP_ERR;

    if (fscanf(f, "%d%d", result1, result2) == 2)
    {
        status = OK;
        if (*result1 < *result2)
        {
            tmp = *result1;
            *result1 = *result2;
            *result2 = tmp;
        }
        while (fscanf(f, "%d", &number) == 1)
        {
            if (number > *result2)
            {
                *result2 = number;
                if (*result1 < *result2)
                {
                    tmp = *result1;
                    *result1 = *result2;
                    *result2 = tmp;
                }
            }
        }
    }
    return status;
}

int main(void)
{
    FILE* f = stdin;
    int result1, result2, status = OK;

    printf("Input numbers per one: ");
    if (!process(f, &result1, &result2))
        printf("\nTwo maximum numbers from sequence is %d and %d", result1, result2);
    else
    {
        status = NO_RESULT;
        printf("Input error!");
    }
    return status;
}

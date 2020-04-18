#include <stdio.h>
#define OK 0
#define NO_FILE_NAME -1
#define FILE_DSNT_EXIST -2
#define ERR_INP -3

/*
 Функция находит среднее арифметическое максимального и минимального элементов
 Считывает из файла числа
 Принимает на вход файл и указатель на среднее арифметическое
 Тип данных: float
 Вернёт: OK если операция успешно, в противном случае код ошибки
*/

float min_max(FILE *f, float *min, float *max)
{
    int status = ERR_INP;
    float number;

    if (fscanf(f, "%f%f", min, max) == 2)
    {
        while (fscanf(f, "%f", &number) == 1)
        {
            if (number > *max)
                *max = number;
            if (number < *min)
                *min = number;
        }
        status = OK;
    }
    return status;
}

/*
 Функция подсчитывает количество чисел в файле больше среднего
 Считывает числа из файла
 Принимает на вход файл и среднее арифметическое
 Тип данных: int
 Возвращает количество чисел больше среднего
*/

int res(FILE *f, float avg)
{
    float number;
    int count = 0;

    while (fscanf(f, "%f", &number) == 1)
    {
        if (number > avg)
            count++;
    }
    return count;
}

int main(int argc, char **argv)
{
    FILE *f;
    int status = OK;
    float avg, min, max;

    if (argc != 2)
    {
        printf("No file name!");
        status = NO_FILE_NAME;
    }
    else
    {

        f = fopen(argv[1], "r");

        if (f == NULL)
        {
            printf("File doesn't exist!");
            status = FILE_DSNT_EXIST;
        }
        else
        {
            status = min_max(f, &min, &max);
            if (status == OK)
            {
                rewind(f);
                avg = (min + max) / 2;

                printf("Ammount of numbers higher than avg of min and max: %d", res(f, avg));
            }
            else
                printf("Input error!");
        }
        fclose(f);
    }
    return status;
}

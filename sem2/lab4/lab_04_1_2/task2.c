#include <stdio.h>
#define OK 0
#define NOT_PRIME -1
#define NO_PRIME -2
#define RNG_ERR -3
#define INP_ERR -4
#define N 10

/*
 Функция ввода массива
 Считывает элементы массива и их количество
 Принимает на вход указатель на массив и указатель на размер массива
 Тип данных: int
 Вернёт: OK если ввод прошёл успешно, в противном случае код ошибки
*/

int arr_input(int a[], int *size)
{
    printf("Enter number of elements: ");
    if (scanf("%d", size) != 1)
        return INP_ERR;
    if (*size <= 0 || *size > N)
        return RNG_ERR;
    printf("\nEnter sequence: ");
    for (int i = 0; i < *size; i++)
    {
        if (scanf("%d", &a[i]) != 1)
            return INP_ERR;
    }
    return OK;
}

/*
 Функция вывода массива
 Принимает на вход указатель на массив и его размер
 Тип данных: int
 Ничего не возвращает
*/

void arr_output(const int a[], const int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
}

/*
 Функция проверяет если входящее число является простым
 Принимает на вход число
 Тип данных: int
 В случае успешной работы вернёт OK, в противном NOT_PRIME
*/

int is_prime(int number)
{
    if (number < 2)
        return NOT_PRIME;
    else
        for (int i = 2; i < number; i++)
        {
            if (number % i == 0)
                return NOT_PRIME;
        }
    return OK;
}

/*
 Функция создаёт новый массив из простых чисел старого массива
 Принимает на вход указатель на старый и новый массив и
 размерность старого массива
 Тип данных: int
 Функция ничего не возвращает
*/

void prime_array(const int old_a[], const int size, int *new_a, int *prime_count)
{
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (!(is_prime(old_a[i])))
        {
            new_a[j] = old_a[i];
            j++;
        }
    }
    *prime_count = j;
}

int main(void)
{
    int a[N], new_a[N], prime_count, size, status = OK;

    status = arr_input(a, &size);
    if (status == OK)
    {
        printf("\nPrime array: ");
        prime_array(a, size, new_a, &prime_count);

        if (!prime_count)
        {
            printf("\nNo prime numbers detected!");
            status = NO_PRIME;
        }
        else
            arr_output(new_a, prime_count);
    }
    else if (status == RNG_ERR)
        printf("\nRange error!");
    else if (status == INP_ERR)
        printf("\nInput error!");

    return status;
}

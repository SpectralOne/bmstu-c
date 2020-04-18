#include <stdio.h>
#define OK 0
#define RNG_ERR -1
#define INP_ERR -2
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
    printf("\nNew array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
}

/*
 Функция поиска минимального элемента (для сортировки выборкой)
 Принимает на вход указатель на массив и его размер и текущую
 Тип данных: int
 Возвращает позицию (индекс) минимального элемента
*/

int find_min(int array[], int len)
{
    int min_index = 0;
    for (int j = 1; j < len; j++)
        if (array[j] < array[min_index])
            min_index = j;
    return min_index;
}

/*
 Функция сортирует массив по возврастанию
 Принимает на вход указатель на массив и его размерность
 Тип сортировки: вставками / выборкой
 Тип данных: int
 Функция ничего не возвращает
*/
/*
void insertion_sort(int a[], const int len)
{
    int tmp, j;

    for (int i = 1; i < len; i++)
    {
        tmp = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > tmp)
        {
            a[j + 1] = a[j];
            j -= 1;
        }
        a[j + 1] = tmp;
    }
}
*/

void selection_sort(int a[], const int len)
{
    int tmp, min_index;
    for (int i = 0; i < len - 1; i++)
    {
        min_index = i + find_min(&a[i], len - i);

        tmp = a[i];
        a[i] = a[min_index];
        a[min_index] = tmp;
    }
}


int main(void)
{
    int a[N], size, status = OK;

    status = arr_input(a, &size);
    if (status == OK)
    {
        //insertion_sort(a, size);
        selection_sort(a, size);
        arr_output(a, size);
    }
    else if (status == RNG_ERR)
        printf("\nRange error!");
    else if (status == INP_ERR)
        printf("\nInput error!");

    return status;
}

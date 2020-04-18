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
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
}

/*
 Функция находит по индексу очередное число Фибоначчи
 Принимает на вход индекс
 Тип данных: int
 Возвращает число Фибоначчи
*/

int fib_number(int index)
{
    int fib1 = 0, fib2 = 1, tmp;

    if (index != 1)
    {
        for (int i = 1; i < index; i++)
        {
            tmp = fib1;
            fib1 += fib2;
            fib2 = tmp;
        }
    }
    return fib1;
}

/*
 * Функция сдвигает на одну позицию вправо все эелементы массива до
   указанной позиции и вставляет на неё указанный элемент
 * Принимает на вход элемент, указатель на массив, размер массива, позицию
 * Тип данных: int
 * Функция ничего не возвращает
 * Побочный эффект: изменение исходного (переданного) массива
*/

void insert_element(int element, int a[], int size, int position)
{
    for (int i = size; i > position; i--)
        a[i] = a[i - 1];
    a[position] = element;
}

/*
 * Функция вставляет после каждого эелемента,
   кратного 3 очередное число Фибоначчи
 * Принимает на вход указатель на массив, его размер и
   количество чисел, кратных трём
 * Тип данных: int
 * Функция ничего не возвращает
 * Побочный эффект: изменение исходного (переданного) массива
*/

void form_array(int a[], int old_size, int aliquot_count)
{
    int fib_ind = 1, tmp_size = old_size;

    for (int i = 0; i < old_size + aliquot_count; i++)
    {
        if ((a[i] % 3 == 0) && (a[i] != 0))
        {
            tmp_size += 1;
            insert_element(fib_number(fib_ind), a, tmp_size, i + 1);
            fib_ind += 1;
            i++;
        }
    }
}

/*
 Функция подсчитывает количество элементов массива, кратных трём
 Принимает на вход указатель на массив, его размер и указатель на количество кратных
 Тип данных: int
 Функция ничего не возвращает
*/

void counter(const int a[], const int size, int *aliquot_count)
{
    *aliquot_count = 0;
    for (int i = 0; i < size; i++)
    {
        if ((a[i] % 3 == 0) && (a[i] != 0))
        {
            *aliquot_count += 1;
        }
    }
}

int main(void)
{
    int a[N*2], size, status = OK, aliquot_count;

    status = arr_input(a, &size);
    if (status == OK)
    {
        counter(a, size, &aliquot_count);
        form_array(a, size, aliquot_count);
        printf("\nSequence: ");
        arr_output(a, size + aliquot_count);
    }
    else if (status == RNG_ERR)
        printf("\nRange error!");
    else if (status == INP_ERR)
        printf("\nInput error!");

    return status;
}

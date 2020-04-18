#include <stdio.h>

#include "utility.h"

int find_digit_sum(int number)
{
    int sum = 0;
    
    // !!!
    unsigned tmp =  (number < 0) ? -number : number;

    /*
    do
    {
        sum += number % 10;
        number /= 10;
    } while(number);
    */
    
    // !!!
    do
    {
        sum += tmp % 10;
        tmp /= 10;
    } while(tmp);
    
    return sum;
}

int count_digits(int **matrix, const int row, const int column)
{
    int cnt = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
           if (find_digit_sum(matrix[i][j]) > 10)
               cnt++;
    return cnt;
}

int *get_num_array(int **matrix, const int row, const int column, int *arr_size)
{
    int cnt = count_digits(matrix, row, column);
    if (!cnt)
        return NULL;

    int *array = allocate_array(cnt);
    if (!array)
        return NULL;
    int idx = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
           if (find_digit_sum(matrix[i][j]) > 10)
               array[idx] = matrix[i][j], idx++;
    return *arr_size = cnt, array;
}

void sort(int *array, const int size)
{
    for (int i = 0; i < size; i++)
        for (int j = size - 1; j > i; j--)
            // Это не Ваша ошибка, это я забыл написать в условии
            if (find_digit_sum(array[j]) < find_digit_sum(array[j - 1]))
               SWAP(array[j], array[j - 1]);
}

void replace(int **matrix, const int row, const int column, int *array, const int arr_size)
{
    int idx = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
           if (find_digit_sum(matrix[i][j]) > 10)
                matrix[i][j] = array[idx], idx++;
}

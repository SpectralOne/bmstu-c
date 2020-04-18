#include "array.h"

void print_array(const array a, const int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
}

int read_array(FILE* f, array a, int *n)
{

    int iterator = 0, status;

    while(fscanf(f, "%d", &a[iterator]) == 1 && iterator < MAX_ELEM)
        iterator++;
    (!iterator) ? (status = READ_ERR) : (status = OK);

    *n = iterator;
    return status;
}

int find_min(const array a, const int size, const int pos)
{
    int min = pos;
    for (int j = pos + 1; j < size; j++)
    {
        if (a[j] < a[min])
            min = j;
    }
    return min;
}

void sort_array(array a, const int n)
{
    int min, temp;
    for (int i = 0; i < n - 1; i++)
    {
        min = find_min(a, n, i);

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

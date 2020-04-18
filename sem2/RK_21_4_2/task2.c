#include<stdio.h>
#define TRUE 1
#define OK 0
#define INP_ERR -1
#define RNG_ERR -2
#define N 10
#define M 10

int arr_input(int a[], int *size)
{
    int status = OK;
    if (scanf("%d", size) == 1)
    {
        if (*size > 0 && *size < N)
        {
            for (int i = 0; i < *size; i++)
            {
                if (scanf("%d", &a[i]) != 1)
                    status = INP_ERR;
            }
        }
        else
            status = RNG_ERR;
    }
    else
        status = INP_ERR;
    return status;
}

void combine_arr(const int x[], int n, const int y[], int m, int z[])
{
    
    int i = 0, j = 0, k = 0;
    for (; i < n && j < m; k++)

        if (x[i] < y[j])  // записать меньшее число из двух массивов в z
        {
            z[k] = x[i];
            i++;
        }
        else
        {
            z[k] = y[j];
            j++;
        }
    if (i < n)
        for (; i < n; i++, k++)  // остаток x в конец z
            z[k] = x[i];
    else
        for (; j < m; j++, k++)  // остаток y в конец z
            z[k] = y[j];
}

void arr_output(const int a[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);
}

int main(void)
{
    int x[N], n, y[M], m, z[N+M], status = OK;
    status = arr_input(x, &n);
    if (status == OK)
    {
        status = arr_input(y, &m);
        if (status == OK)
        {
            combine_arr(x, n, y, m, z);
            arr_output(z, n+m);
        }
        else if (status == INP_ERR)
            printf("Input error!");
        else if (status == RNG_ERR)
            printf("Range error!");
    }
    else if (status == INP_ERR)
        printf("Input error!");
    else if (status == RNG_ERR)
        printf("Range error!");
    return status;
}

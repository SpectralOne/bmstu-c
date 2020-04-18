#include <stdio.h>
#define OK 0
#define RNG_ERR -1
#define INP_ERR -2
#define N_MAX 10
typedef int matrix_t[N_MAX][N_MAX];

int mtr_input(matrix_t a, int *n)
{
    int status = OK;
    printf("Input size of square matrix: ");
    if (scanf("%d", n) == 1)
    {
        if (2 <= *n && *n <= N_MAX)
        {
            printf("Input elements:\n");
            for (int i = 0; status == OK && i < *n; i++)
                for (int j = 0; status == OK && j < *n; j++)
                    if (scanf("%d", &a[i][j]) != 1)
                        status = INP_ERR;
        }
        else
            status = RNG_ERR;
    }
    else
        status = INP_ERR;

    return status;
}

int get_min_element(matrix_t a, int n)
{
    int min;
    min = a[1][n-1];
    for (int i = 2; i < n; i++)
        for (int j = n - i; j < n; j++)
            if (a[i][j] < min)
                min = a[i][j];
    return min;
}

int main(void)
{
    int n, status, min;
    matrix_t a;

    status = mtr_input(a, &n);

    if (status == OK)
    {
        min = get_min_element(a, n);
        printf("\nMin. element = %d", min);
    }
    else if (status == RNG_ERR)
        printf("Range error!");
    else if (status == INP_ERR)
        printf("Input error!");

    return status;
}
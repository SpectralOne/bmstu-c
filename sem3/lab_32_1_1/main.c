#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "io.h"
#include "mem.h"


int find_min(int **matrix, const int row, const int col, int *min)
{
    int flag = 0;

    if (row == 1)
        return -1;

    for (int i = 1; i < row; i++)
        for (int j = 0; j < col - 1; j++)
            if (j < i)
                if (matrix[i][j] % 2 /*== 1*/)
				{
                    *min = matrix[i][j];
                    flag = 1;
                }
				
    if (!flag)
        return -1;
    
    for (int i = 1; i < row; i++)
        for (int j = 0; j < col - 1; j++)
            if (j < i)
                if (matrix[i][j] % 2 /*== 1*/ && matrix[i][j] < *min)
                    *min = matrix[i][j];
    return 0;
}

int main(int argc, char **argv)
{
    // !!!
    int rc = 0;
    
    if (argc != 2)
        return -1;

    FILE *f = fopen(argv[1], "r");
    if (!f)
        return -1;

    int row, column, **matrix, status = 0;

    matrix = create_matrix(f, &row, &column, &status);
    if (!matrix)
        return -1;

    int min;
    if (find_min(matrix, row, column, &min) == 0)
        printf("%d\n", min);
    // !!!
    else
        rc = -1;

    free_matrix(matrix, row);    

    // !!!
    return rc;
}

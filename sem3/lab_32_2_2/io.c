#include <stdio.h>
#include <assert.h>
#include "io.h"

void print_matrix(int **matrix, const int row, const int column)
{
    assert(matrix);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
            printf("%d ", matrix[i][j]);
        puts("");
    }
}

int **create_matrix(FILE *f, int *row, int *column, int *status)
{
    int **tmp;

    if (fscanf(f, "%d %d", row, column) == 2 && *row > 0 && *column > 0 /**row > 1 && *column > 1 && *row == *column*/)
    {
        tmp = allocate_matrix(*row, *column, status);
        if (tmp)
        {
            for (int i = 0; i < *row; i++)
                for (int j = 0; j < *column; j++)
                    if (fscanf(f, "%d", &(tmp[i][j])) != 1)
                    {
                        free_matrix(tmp, *row);
                        *status = -1;
                        return NULL;
                    }
            return tmp;
        }
    }
    *status = -1;
    return NULL;
}

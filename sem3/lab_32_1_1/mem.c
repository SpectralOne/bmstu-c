#include <stdlib.h>
#include <assert.h>

#include "mem.h"

void free_matrix(int **matrix, int row)
{
    assert(matrix);

    for (int i = 0; i < row; i++)
    {
        if (matrix[i])
            free(matrix[i]);
    }

    free(matrix);
}


int **allocate_matrix(const int row, const int column, int *status)
{
    int **tmp;
    *status = 0;
    tmp = (int**) malloc(row * sizeof(int*));
    if (tmp)
    {
        for (int i = 0; i < row; i++)
        {
            tmp[i] = (int*) malloc(column * sizeof(int));
            if (!tmp[i])
            {
                *status = -1;
                free_matrix(tmp, row);
                return NULL;
            }
        }
        return tmp;
    }
    *status = -1;
    return NULL;
}

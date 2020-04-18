#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "io.h"
#include "mem.h"
#include "utility.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        return -1;

    FILE *f = fopen(argv[1], "r");
    if (!f)
        return -1;

    int row, column, **matrix, status = 0;

    matrix = create_matrix(f, &row, &column, &status);
    if (!matrix)
        return -1;

    int arr_size = 0;
    int *array = get_num_array(matrix, row, column, &arr_size);
    if (!array)
        return free_matrix(matrix, row), -1;

    sort(array, arr_size);
    replace(matrix, row, column, array, arr_size);

    print_matrix(matrix, row, column);

    free_matrix(matrix, row);
    free(array);
    return 0;
}

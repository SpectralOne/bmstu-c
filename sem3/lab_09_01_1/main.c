#include <stdio.h>
#include "io_funcs.h"
#include "custom_defines.h"
#include "custom_errors.h"
#include "memmory_funcs.h"
#include "utility_funcs.h"
#include "err_handler.h"

int main(void)
{
    setbuf(stdout, NULL);

    matrix_s *matrix1 = NULL, *matrix2 = NULL, *result_matrix = NULL;

    int status = OK, power;
    matrix1 = create_matrix(&status);
    if (matrix1 && status == OK)
    {
        matrix2 = create_matrix(&status);
        if (matrix2 && status == OK)
        {
            status = round_matrix(matrix1);
            if (status == OK)
            {
                status = round_matrix(matrix2);
                if (status == OK)
                {
                    if (matrix1->cur_rows != matrix2->cur_rows)
                    {
                        if (matrix1->cur_rows < matrix2->cur_rows)
                            status = equalize(matrix1, ABS(matrix1->cur_rows - matrix2->cur_rows));
                        else
                            status = equalize(matrix2, ABS(matrix1->cur_rows - matrix2->cur_rows));
                    }
                    if (status == OK)
                    {
                        status = get_power(&power);
                        if (status == OK)
                        {
                            status = matrix_pow(matrix1, power);
                            if (status == OK)
                            {
                                status = get_power(&power);
                                if (status == OK)
                                {
                                    status = matrix_pow(matrix2, power);
                                    if (status == OK)
                                    {
                                        result_matrix = allocate_matrix(matrix1->cur_rows, matrix2->cur_columns, &status);
                                        if (result_matrix)
                                        {
                                            transpose(matrix2);
                                            
                                            multiply_transpose_matrix(matrix1, matrix2, result_matrix);
                                            print_matrix(result_matrix);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    err_handler(status);

    if (matrix1)
        free_matrix(matrix1);
    if (matrix2)
        free_matrix(matrix2);
    if (result_matrix)
        free_matrix(result_matrix);

    return status;
}

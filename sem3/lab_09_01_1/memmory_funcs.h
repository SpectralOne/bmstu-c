#ifndef __MEMMORY_FUNCS_H__
#define __MEMMORY_FUNCS_H__

#include "custom_errors.h"
#include "custom_defines.h"

int remove_row(matrix_s *matrix, const int row);
int remove_column(matrix_s *matrix, const int col);
int increase_matrix_rows(matrix_s *matrix);
int increase_matrix_columns(matrix_s *matrix);
matrix_s *allocate_matrix(const int rows, const int columns, int *status);
void free_matrix(matrix_s *matrix);

#endif
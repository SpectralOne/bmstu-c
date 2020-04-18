#ifndef __UTILITY_FUNCS_H__
#define __UTILITY_FUNCS_H__

#include "custom_errors.h"
#include "custom_defines.h"
#include "memmory_funcs.h"

void find_max_element_pos(const matrix_s *matrix, int *pos_row, int *pos_column);
int64_t find_min_element(const matrix_s *matrix);
int round_matrix(matrix_s *matrix);
int64_t find_row_max(const int64_t *row, const int row_size);
int64_t find_col_avg(const matrix_s *matrix, const int col);
int equalize(matrix_s *matrix, const int diff);
void copy_matrix_data(const matrix_s *original_matrix, matrix_s *tmp);
void multiply_matrix(const matrix_s *matrix_a, const matrix_s *matrix_b, matrix_s *result_matrix);
int matrix_pow(matrix_s *matrix, const int power);
void turn_matrix_to_unity(matrix_s *matrix);
int64_t find_col_sum(const matrix_s *matrix, const size_t col);
void multiply_transpose_matrix(const matrix_s *matrix_a, const matrix_s *matrix_b, matrix_s *result_matrix);
void transpose(matrix_s *matrix);

#endif //__MATRIX__H__

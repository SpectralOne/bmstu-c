#ifndef __IO_FUNCS_H__
#define __IO_FUNCS_H__

#include "custom_defines.h"
#include "memmory_funcs.h"

void print_matrix(const matrix_s *matrix);
matrix_s *create_matrix(int *status);
int get_power(int *power);

#endif
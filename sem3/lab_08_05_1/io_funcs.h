#ifndef __IO_FUNCS_H__
#define __IO_FUNCS_H__

#include "custom_errors.h"
#include "custom_defines.h"

void print_array(const double *array, const double *end_array);
int fill_array(double *array, double *end_array);
int get_array_size(int *size);
int get_pos(int *pos, const int size);

#endif

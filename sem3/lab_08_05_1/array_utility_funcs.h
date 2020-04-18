#ifndef __ARRAY_UTILITY_FUNCS_H__
#define __ARRAY_UTILITY_FUNCS_H__

#include "custom_errors.h"
#include "custom_defines.h"

double find_min(const double *array, const double *end_array);
double find_max(const double *array, const double *end_array);
void move_to_end(double *const array, double *const end_array);
void find_element(double *array, double *end_array, double **pos, const double mu1);
int normalize_array(double **array, double **end_array, const double mu1);
int delete_element(double **array, double **end_array, double *pos);
int reallocate_array(double **array, double **end_array, int new_size);
int f_equal(double num1, double num2);
void insert_to_pos(double *array, double *end_array, const int pos, const double item);

#endif

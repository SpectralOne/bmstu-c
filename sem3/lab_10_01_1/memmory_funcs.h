#ifndef __MEMMORY_FUNCS_H__
#define __MEMMORY_FUNCS_H__

#include "custom_errors.h"
#include "custom_defines.h"

person_s **reallocate_struct_array(person_s **array, int *status, const int array_size);
person_s *allocate_struct(int *status);
int *reallocate_grades(int *array, const int grades_count, int *status);
char *allocate_string(const int char_count, int *status);
void free_struct(person_s *kid);
void free_struct_array(person_s **array, const int array_size);

#endif
#ifndef __IO_FUNCS_H__
#define __IO_FUNCS_H__

#include <stdio.h> // FILE definition

#include "utility_funcs.h"
#include "custom_defines.h"
#include "custom_errors.h"
#include "memmory_funcs.h"

void print_marks(grades_s *grades, FILE *f);
void print_struct(const person_s *kid, FILE *f);
void print_struct_array(person_s **arr, const int count, FILE *f);
int read_string(string_t string);
int read_grades(grades_s *grades);
int read_kid_info(person_s *kid);
person_s **get_struct_array(int *size, int *status);
int compress_array(person_s ***array, const int curr_size, const int prev_size);

#endif
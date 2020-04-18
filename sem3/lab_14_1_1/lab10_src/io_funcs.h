#ifndef __IO_FUNCS_H__
#define __IO_FUNCS_H__

#include <stdio.h> // FILE definition

#include "utility_funcs.h"
#include "custom_defines.h"
#include "custom_errors.h"
#include "memmory_funcs.h"

int read_string(string_t string, FILE *f);
int read_grades(grades_s *grades, char *grades_string);
int fill_record(person_s *kid, char *surname, char *sex, char *date, char *grades);

int is_equal(person_s *person1, person_s *person2);
int find_in_arr(person_s **arr, int size, person_s *person);

#endif
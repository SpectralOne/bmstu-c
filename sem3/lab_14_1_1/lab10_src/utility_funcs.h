#ifndef __UTILITY_FUNCS_H__
#define __UTILITY_FUNCS_H__

#include "custom_errors.h"
#include "custom_defines.h"
#include "memmory_funcs.h"

void delete_struct_by_pos(person_s **array, const int array_size, const int pos);
void split_date(const date_str_t date, int *b_year, int *b_month, int *b_day);
int calculate_person_age(const date_str_t date);
int normalize_array(person_s ***array, int *array_size, const sex_str_t delete_sex, const int acceptable_age);
int add_three_all(person_s **array, const int array_size);
float grades_average(const grades_s *grades);
void string_to_lower(char *destination_str, const char *source_str);
int check_sex_string(const string_t string);
int check_date_string(const string_t string, const char *format);
int check_string(const string_t string);

int digits_space_only(char *s);
int check_grades(char *grades);


#endif
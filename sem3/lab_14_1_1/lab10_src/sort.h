#ifndef __SORT_H__
#define __SORT_H__

#include "custom_defines.h"
#include "custom_errors.h"
#include "utility_funcs.h"

void swap(person_s **x, person_s **y);
int compare_surname(const person_s *item1, const person_s *item2);
int compare_sex(const person_s *item1, const person_s *item2);
int compare_birth_date(const person_s *item1, const person_s *item2);
int compare_grade_average(const person_s *item1, const person_s *item2);

void sort_arr(person_s **array, const int array_size, int (*compare)(const person_s *, const person_s *));
void partial_sort(person_s **array, const int array_size, int (*compare)(const person_s *, const person_s *), const int pos);

#endif

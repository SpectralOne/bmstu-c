#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include "defines.h"
#include "cdio.h"

int count_file(FILE *f);

int is_equal(const student_t student1, const student_t student2);

int array_search(student_t *arr, const int size, student_t student);

student_t *get_sym_diff_arr(student_t *arr1, const int size1, student_t *arr2, const int size2, int *size_res);


#endif // UTILITY_H

#ifndef CDIO_H
#define CDIO_H

#include "defines.h"
#include "utility.h"
#include "cdio.h"
#include <stdio.h>

void free_arr(student_t *arr, int size);
int compress(student_t **arr, const int actual_size, int size);
student_t *allocate_array(const int size);
int get_string(FILE *f, char *string);
int read_struct(FILE *f, student_t *student);
student_t *get_struct_array(FILE *f, int *size);
void print_arr(FILE *f, student_t *arr, const int size);


#endif // CDIO_H

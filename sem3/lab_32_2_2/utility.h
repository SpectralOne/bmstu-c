#ifndef UTILITY_H
#define UTILITY_H

#define SWAP(x, y) do { __typeof__(x) __TMP__ = x; x = y; y = __TMP__; } while (0)

#include "mem.h"

int find_digit_sum(int number);

int count_digits(int **matrix, const int row, const int column);

int *get_num_array(int **matrix, const int row, const int column, int *arr_size);

void sort(int *array, const int size);

void replace(int **matrix, const int row, const int column, int *array, const int arr_size);

#endif // UTILITY_H

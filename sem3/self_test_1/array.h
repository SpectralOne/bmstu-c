#ifndef ARRAY_FUNC
#define ARRAY_FUNC

#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEM 10
#define OK 0
#define CMD_ERR -1
#define FILE_ERR -2
#define READ_ERR -3
typedef int array[MAX_ELEM];

void print_array(const array a, const int n);
int read_array(FILE* f, array a, int *n);
int find_min(const array a, const int size, const int pos);
void sort_array(array a, const int n);
#endif

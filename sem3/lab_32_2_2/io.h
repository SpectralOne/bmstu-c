#ifndef __IO_H__
#define __IO_H__

#include "mem.h"

void print_matrix(int **matrix, const int row, const int column);
int **create_matrix(FILE *f, int *row, int *column, int *status);

#endif

#ifndef MEM_H
#define MEM_H

void free_matrix(int **matrix, int row);
int **allocate_matrix(const int row, const int column, int *status);
int *allocate_array(const int count);

#endif // MEM_H

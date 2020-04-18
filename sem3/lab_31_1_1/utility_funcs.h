#ifndef UTILITY_FUNCS_H
#define UTILITY_FUNCS_H

#include "custom_defines.h"
#include "custom_errors.h"
#include "io_funcs.h"

int count_films_in_file(int *count, FILE* f);
void shift_array(film_s **array, const int size, const int pos);
int binary_search(film_s **array, int low, int high, const char *value, int (*compare_key) (const film_s *, const char *));

#endif 

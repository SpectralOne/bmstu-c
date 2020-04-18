#ifndef MEMMORY_FUNC_H
#define MEMMORY_FUNC_H

#include "custom_defines.h"
#include "custom_errors.h"

film_s *allocate_struct(int *status);
film_s **allocate_struct_array(size_t size);
char *allocate_string(size_t n_bytes);
void free_film_array(film_s **array, int size);
void free_struct(film_s *film);

#endif 

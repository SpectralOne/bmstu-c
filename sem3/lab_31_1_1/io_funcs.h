#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#include "custom_defines.h"
#include "custom_errors.h"
#include "memmory_funcs.h"
#include "utility_funcs.h"

void info(void);
void print_film_info(const film_s *film);
void print_film_array(film_s **array, const int size);
int get_string(string_t string, FILE* f);
int read_film_from_file(film_s *film, FILE* f);
film_s **get_film_array(const int size, int (*compare) (const film_s *, const film_s *), int *status, FILE *f);

#endif

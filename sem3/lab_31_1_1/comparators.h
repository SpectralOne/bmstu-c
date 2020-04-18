#ifndef __COMPARATORS_H__
#define __COMPARATORS_H__

#include "custom_defines.h"

int compare_name(const film_s *item1, const film_s *item2);
int compare_title(const film_s *item1, const film_s *item2);
int compare_year(const film_s *item1, const film_s *item2);
int compare_key_name(const film_s *film, const char *string);
int compare_key_title(const film_s *film, const char *string);
int compare_key_year(const film_s *film, const char *string);

#endif 
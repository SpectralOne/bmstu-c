#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "comparators.h"

int compare_name(const film_s *item1, const film_s *item2)
{
    assert(item1 && item2);

    if (strcmp(item1->name, item2->name) > 0)
        return 1;
    else
        return 0;
}

int compare_title(const film_s *item1, const film_s *item2)
{
    assert(item1 && item2);

    if (strcmp(item1->title, item2->title) > 0)
        return 1;
    else
        return 0;
}

int compare_year(const film_s *item1, const film_s *item2)
{
    assert(item1 && item2);

    if ((item1->year - item2->year) > 0)
        return 1;
    else 
        return 0;
}

int compare_key_name(const film_s *film, const char *string)
{
    assert(film && string);

    return strcmp(film->name, string); 
}

int compare_key_title(const film_s *film, const char *string)
{
    assert(film && string);

    return strcmp(film->title, string);
}

int compare_key_year(const film_s *film, const char *string)
{
    assert(film && string);

    return film->year - (int) atol(string);
}
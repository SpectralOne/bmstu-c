#include <stdlib.h>
#include <assert.h>

#include "memmory_funcs.h"

film_s *allocate_struct(int *status)
{
    film_s *tmp = NULL;
    tmp = (film_s *) malloc(sizeof(film_s));
    if (tmp)
    {
        *status = OK;
        return tmp;
    }

    *status = -3;

    return NULL;
}

film_s **allocate_struct_array(size_t size)
{
    film_s **array_tmp = NULL;
    
    array_tmp = (film_s **) calloc(size, sizeof(film_s *));

    return array_tmp;
}

char *allocate_string(size_t n_bytes)
{
    char *tmp = NULL;
    tmp = (char *) malloc((n_bytes + 1) * sizeof(char));
    tmp[0] = 0;

    return tmp;
}

void free_film_array(film_s **array, int size)
{
    assert(array);

    for (int film = 0; film < size; film++)
        if (array[film])
            free_struct(array[film]);

    free(array);
}

void free_struct(film_s *film)
{
    assert(film);

    if (film->title)
        free(film->title);
    if (film->name)
        free(film->name);

    free(film);
}

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "utility_funcs.h"

int count_films_in_file(int *count, FILE* f)
{
    assert(f && count);

    int status;
    film_s *tmp;

   *count = 0;

    do
    {
        tmp = allocate_struct(&status);
        if (tmp && status == OK)
        {
            status = read_film_from_file(tmp, f);
            if (status == OK)
                (*count)++;
        }
        if (tmp)
            free_struct(tmp);

    } while (status == OK);


    if (status == READ_ERR)
        status = OK;

    return status;
}

int binary_search(film_s **array, int low, int high, const char *value, int (*compare_key) (const film_s *, const char *)) 
{ 
    if (high < low) 
        return NOT_FOUND; 

    int mid = (low + high) / 2;

    if (compare_key(array[mid], value) == 0) 
        return mid; 
    if (compare_key(array[mid], value) < 0) 
        return binary_search(array, (mid + 1), high, value, compare_key); 

    return binary_search(array, low, (mid - 1), value, compare_key); 
} 

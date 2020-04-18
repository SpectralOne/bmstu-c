#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "custom_defines.h"
#include "custom_errors.h"
#include "io_funcs.h"
#include "memmory_funcs.h"
#include "utility_funcs.h"
#include "comparators.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);

    if (argc < 3 || argc > 4)
    {
        info();
        return INV_ARGS;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f)
        return INV_FILE;

    int array_size = 0, status = OK;
    film_s **array = NULL;

    status = count_films_in_file(&array_size, f);
    if (status == OK)
    {
        if (array_size)
        {
            rewind(f);
            
            if (strcmp(argv[2], "name") == 0)
                array = get_film_array(array_size, &compare_name, &status, f);
            else if (strcmp(argv[2], "title") == 0)
                array = get_film_array(array_size, &compare_title, &status, f);
            else if ((strcmp(argv[2], "year") == 0))
                array = get_film_array(array_size, &compare_year, &status, f);
            else
                status = INV_KEY;

            if (status == OK)
            {
                if (argc == 4)
                {
                    int index = 0;
                    if (strcmp(argv[2], "name") == 0)
                        index = binary_search(array, 0, array_size, argv[3], &compare_key_name);
                    else if (strcmp(argv[2], "title") == 0)
                        index = binary_search(array, 0, array_size, argv[3], &compare_key_title);
                    else
                    {
                        if (atol(argv[3]) <= 0)
                            status = INV_KEY_YEAR;
                        else
                            index = binary_search(array, 0, array_size, argv[3], &compare_key_year);
                    }
                    if (status == OK)
                    {
                        if (index != NOT_FOUND)
                            print_film_info(array[index]);
                        else
                            puts("Not found");
                    }
                }
                else
                    print_film_array(array, array_size);
            }
        }
        else
            status = EMPTY_FILE;
    }
    fclose(f);
    
    if (array)
        free_film_array(array, array_size);
    return status;
}

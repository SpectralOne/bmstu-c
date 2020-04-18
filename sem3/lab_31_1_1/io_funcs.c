#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "io_funcs.h"

void info(void)
{
    puts("Usage: app.exe FILE_NAME FIELD KEY");
    puts("FILE_NAME: file name");
    puts("FILED: title, name, year");
    puts("KEY: FIELD value");
}

void print_film_info(const film_s *film)
{
    assert(film);

    printf("%s\n", film->title);
    printf("%s\n", film->name);
    printf("%d\n", film->year);
}

void print_film_array(film_s **array, const int size)
{
    assert(array);
    assert(size > 0);

    for (int film = 0; film < size; film++)
        print_film_info(array[film]);
}

int get_string(string_t string, FILE* f)
{
    if (fgets(string, sizeof(string_t), f) == NULL)
        return READ_ERR;
    if (string[strlen(string) - 1] != '\n')
        return OVERFLOW_STR;
    string[strlen(string) - 1] = 0;
    if (!strlen(string))
        return EMPTY_STR;
    return OK;
}

int read_film_from_file(film_s *film, FILE* f)
{
    int status = READ_ERR;
    string_t buf;
    char tmp[4];

    film->title = NULL;
    film->name = NULL;

    status = get_string(buf, f);
    if (status == OK)
    {
        film->title = allocate_string(strlen(buf));
        if (film->title)
        {
            strcpy(film->title, buf);
            status = get_string(buf, f);
            if (status == OK)
            {
                film->name = allocate_string(strlen(buf));
                if (film->name)
                {
                    strcpy(film->name, buf);
                    if (fscanf(f, "%d", &film->year) == 1 && film->year > 0)
                        status = OK;
                    else
                        status = INV_YEAR;
                }
                else
                    status = MEM_ALLOC_ERR;
            }
        }
        else
            status = MEM_ALLOC_ERR;
    }

    fgets(tmp, sizeof(tmp), f);

    return status;
}

film_s **get_film_array(const int size, int (*compare) (const film_s *, const film_s *), int *status, FILE *f)
{
    *status = OK;
    film_s *tmp;
    
    film_s **array = allocate_struct_array(size);

    if (!array)
        return NULL;

    for (int cur_size = 0; cur_size < size; ++cur_size)
    {
        tmp = allocate_struct(status); 
        if (tmp && *status == OK)
        {
            *status = read_film_from_file(tmp, f);
            if (tmp && *status == OK)
            {
                if (!cur_size)
                    array[cur_size] = tmp;
                else
                {
                    int i = cur_size - 1; 
                    for (; i >= 0 && compare(array[i], tmp) > 0; i--) 
                        array[i + 1] = array[i]; 
                
                    array[i + 1] = tmp; 
                }
            }
        }
    }

    if (*status == READ_ERR)
        *status = OK;

    return array;
}

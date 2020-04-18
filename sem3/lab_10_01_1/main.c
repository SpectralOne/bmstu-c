#include <stdio.h>
#include <string.h>
#include "io_funcs.h"
#include "custom_defines.h"
#include "custom_errors.h"
#include "err_handler.h"
#include "memmory_funcs.h"
#include "utility_funcs.h"
#include "sort.h"

int main(void)
{
    setbuf(stdout, NULL);

    int status = OK, size = 0;
    person_s **arr = NULL;
    string_t sort_key;
    FILE *out_file;
    
    arr = get_struct_array(&size, &status);
    if (arr && status == OK && size)
    {
        status = normalize_array(&arr, &size, DELETE_FORMAT);
        if (arr && status == OK && size)
        {   
            status = add_three_all(arr, size);
            if (arr && status == OK)
            {
                status = read_string(sort_key);
                if (status == OK)
                {
                    if (strcmp(sort_key, "SURNAME") == 0)
                        sort_arr(arr, size, &compare_surname);
                    else if (strcmp(sort_key, "SEX") == 0)
                        sort_arr(arr, size, &compare_sex);
                    else if (strcmp(sort_key, "BIRTHDATE") == 0)
                        sort_arr(arr, size, &compare_birth_date);
                    else if (strcmp(sort_key, "GRADE") == 0)
                        sort_arr(arr, size, &compare_grade_average);
                    else
                        status = INVALID_SORT_KEY; 

                    if (size && status == OK)
                    {
                        out_file = fopen(OUT_FILE, "w");
                        if (out_file)
                        {
                            print_struct_array(arr, size, out_file);
                            fclose(out_file);
                        }
                        else
                            status = ERR_FILE;
                    }
                }
            }
        }
    }

    err_handler(status);

    if (arr)
        free_struct_array(arr, size);

    return status;
}

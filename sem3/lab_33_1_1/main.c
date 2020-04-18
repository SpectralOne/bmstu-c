#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "utility.h"
#include "cdio.h"

int main(int argc, char **argv)
{
    student_t *arr1 = NULL, *arr2 = NULL, *res_arr = NULL;
    int size1, size2, size_res, status = 0;

    FILE *f1, *f2;
    if (argc == 3)
    {
        f1 = fopen(argv[1], "r");
        if (f1)
        {
            arr1 = get_struct_array(f1, &size1);
            fclose(f1);
            if (size1 > -1)
            {
                f2 = fopen(argv[2], "r");
                if (f2)
                {
                    arr2 = get_struct_array(f2, &size2);
                    fclose(f2);
                    
                    if (size2 > -1)
                    {
                        if (size1 || size2)
                        {
                            res_arr = get_sym_diff_arr(arr1, size1, arr2, size2, &size_res);
                            if (res_arr)
                                print_arr(stdout, res_arr, size_res);
                            else
                                status = -1;
                        }
                        else
                            status = -1;
                    }
                    else
                        status = -1;
                }
                else
                    status = -1;
            }
            else
                status = -1;
        }
        else
            status = -1;
    }
    else
        status = -1;
    
    if (arr1)
        free_arr(arr1, size1);
    if (arr2)
        free_arr(arr2, size2);
    if (res_arr)
        free(res_arr);

    return status;
}

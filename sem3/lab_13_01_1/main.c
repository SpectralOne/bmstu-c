#include <stdio.h>
#include <stdlib.h>
#define AMOUNT_TO_ADD 3

#include "err.h"
#include "non_lib.h"
#include "da_lib.h"

#ifdef LOAD
#include <dlfcn.h>
#endif

int main(void)
{
    setbuf(stdout, NULL);

    int status = OK, size, pos;
    double mu1, mu2;
    double *array = NULL, *end_array = NULL;

    #ifdef LOAD
    void *hlib = dlopen("./libdaf.so", RTLD_LAZY);

    fn_normalize_array_t da_normalize_array = dlsym(hlib, "da_normalize_array");
    fn_reallocate_array_t da_reallocate_array = dlsym(hlib, "da_reallocate_array");
    fn_insert_to_pos_t da_insert_to_pos = dlsym(hlib, "da_insert_to_pos");
    fn_compute_mu1_t da_compute_mu1 = dlsym(hlib, "da_compute_mu1");
    fn_compute_mu2_t da_compute_mu2 = dlsym(hlib, "da_compute_mu2");
    fn_print_array_t da_print_array = dlsym(hlib, "da_print_array");
    fn_fill_array_t da_fill_array = dlsym(hlib, "da_fill_array");
    fn_free_array_t da_free_array = dlsym(hlib, "da_free_array");

    if (hlib)
    {
        if (!da_normalize_array || !da_reallocate_array || !da_insert_to_pos ||\
            !da_compute_mu1     || !da_compute_mu2      || !da_print_array   \
                                || !da_fill_array       || !da_free_array)
            status = ERR_LOAD;
    }
    else
    {
        printf("Cannot open library (%s).\n", dlerror());
        status = ERR_LIBRARY;
    }
    #endif
    if (status == OK)
    {
        status = get_array_size(&size);
        if (status == OK)
        {
            status = da_reallocate_array(&array, &end_array, size);
            if (status == OK)
            {
                status = da_fill_array(array, end_array);
                if (status == OK)
                {
                    mu1 = da_compute_mu1(array, end_array);
                    
                    status = da_normalize_array(&array, &end_array, mu1);
                    if (status == OK)
                    {
                        mu2 = da_compute_mu2(array, end_array);
                        size -= AMOUNT_TO_DELETE;

                        status = da_reallocate_array(&array, &end_array, size + AMOUNT_TO_ADD);
                        if (status == OK)
                        {
                            status = get_pos(&pos, size);
                            if (status == OK)
                            {
                                da_insert_to_pos(array, end_array, pos, mu2);
                                da_insert_to_pos(array, end_array, 0, mu2);
                                da_insert_to_pos(array, end_array, size + 2, mu2);

                                da_print_array(array, end_array);
                            }
                        }
                    }
                }
            }
        }
    }

    #ifdef LOAD
    if (hlib)
        dlclose(hlib);
    #endif

    err_handler(status);
    if (array)
    {
        da_free_array(array);
		array = NULL;
        end_array = NULL;
    }

    return status;
}

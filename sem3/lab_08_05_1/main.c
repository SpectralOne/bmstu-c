#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "custom_defines.h"
#include "err_handler.h"
#include "array_utility_funcs.h"
#include "io_funcs.h"
#include "mu_funcs.h"

int main(void)
{
    setbuf(stdout, NULL);

    int status = OK, size, pos;
    double mu1, mu2;
    double *array = NULL, *end_array = NULL;

    status = get_array_size(&size);
    if (status == OK)
    {
        status = reallocate_array(&array, &end_array, size);
        if (status == OK)
        {
            status = fill_array(array, end_array);
            if (status == OK)
            {
                mu1 = compute_mu1(array, end_array);
				
				// Теперь перевыделение происходит здесь
                status = normalize_array(&array, &end_array, mu1);

                // status = reallocate_array(&array, &end_array, size - AMOUNT_TO_DELETE);
                if (status == OK)
                {
                    mu2 = compute_mu2(array, end_array);
                    size -= AMOUNT_TO_DELETE;

                    status = reallocate_array(&array, &end_array, size + AMOUNT_TO_ADD);
                    if (status == OK)
                    {
                        status = get_pos(&pos, size);
                        if (status == OK)
                        {
                            insert_to_pos(array, end_array, pos, mu2);
                            insert_to_pos(array, end_array, 0, mu2);
                            insert_to_pos(array, end_array, size + 2, mu2);

//                            insertion(array, end_array, pos, mu2);
                            print_array(array, end_array);
                        }
                    }
                }
            }
        }
    }

    err_handler(status);
    if (array)
    {
        free(array);
		array = NULL;
        end_array = NULL;
    }

    return status;
}

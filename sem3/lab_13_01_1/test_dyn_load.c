#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "err.h"
#include "da_lib.h"

#include <dlfcn.h>

int f_equal(double num1, double num2)
{
    if (fabs(num1 - num2) < PRECISION)
        return TRUE;
    return FALSE;
}

/*
 * Функция сравнения элементов двух массивов
 * Принимает на вход указатели на массивы и их длину
 * Тип данных: double, int
 * Возвращает 1 если два массива равны, иначе 0
 --- Допущения ---
 * Массивы существуют
 * Массивы имеют положительный размер
 * Массивы одинаковы по длине
 --- Параметры ---
   [in]  *array1 : указатель на первый массив
   [in]  *array2 : указатель на второй массив
   [in]   len_array : длина массивов
 [return] : признак равенства массивов (0 или 1)
*/
int compare_array(const double *array1, const double *array2, const int len_array)
{
    assert(array1 && array2);

    for (int i = 0; i < len_array; i++)
        if (!(f_equal(array1[i], array2[i])))
            return 0;
    return 1;
}

int main(void)
{
    setbuf(stdout, NULL);
    int status = OK;

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
    if (status == OK)
    
    {
        printf("\n--- %s ---\n\n", "da_insert_to_pos");
        int err_count = 0;

        printf("Normal test: ");
        {
            double test_array[4] = { 1.2, 3.4, 5.6 };
            double result_array[] = { 1.2, -1, 3.4, 5.6 };
            int pos = 1;

            da_insert_to_pos(test_array, test_array + 4, pos, -1);
            if (compare_array(test_array, result_array, 4))
                printf("OK\n");
            else
            {
                printf("FAILED\n");
                err_count++;
            }
        }

        printf("Insert to end: ");
        {
            double test_array[4] = { 1.2, 3.4, 5.6 };
            double result_array[] = { 1.2, 3.4, 5.6, -1 };
            int pos = 3;

            da_insert_to_pos(test_array, test_array + 4, pos, -1);
            if (compare_array(test_array, result_array, 4))
                printf("OK\n");
            else
            {
                printf("FAILED\n");
                err_count++;
            }
        }

        printf("Insert to begining: ");
        {
            double test_array[4] = { 1.2, 3.4, 5.6 };
            double result_array[] = { -1, 1.2, 3.4, 5.6 };
            int pos = 0;

            da_insert_to_pos(test_array, test_array + 4, pos, -1);
            if (compare_array(test_array, result_array, 4))
                printf("OK\n");
            else
            {
                printf("FAILED\n");
                err_count++;
            }
        }
        printf("\n%s: %s\n\n", "da_insert_to_pos: ", err_count ? "FAILED" : "OK");
    }
    {
        printf("\n--- %s ---\n\n", "da_normalize_array");
        int err_count = 0;

        printf("First and last: ");
        {
            double *test_array = malloc(5 * sizeof(double));

            assert(test_array);

            double *end = test_array + 5;
            test_array[0] = 1.2;
            test_array[1] = 2.;
            test_array[2] = 2.;
            test_array[3] = 3.;
            test_array[4] = 1.1;

            double result_array[] = { 2., 2., 3. };

            da_normalize_array(&test_array, &end, 1.1);
            if (compare_array(test_array, result_array, 3))
                printf("OK\n");
            else
            {
                printf("FAILED\n");
                err_count++;
            }
            da_free_array(test_array);
        }

        printf("First and second (same): ");
        {
            double *test_array = malloc(5 * sizeof(double));

            assert(test_array);

            double *end = test_array + 5;
            test_array[0] = 1.1;
            test_array[1] = 1.1;
            test_array[2] = 2.;
            test_array[3] = 3.;
            test_array[4] = 2.;

            double result_array[] = { 2., 3., 2. };

            da_normalize_array(&test_array, &end, 1.1);
            if (compare_array(test_array, result_array, 3))
                printf("OK\n");
            else
            {
                printf("FAILED\n");
                err_count++;
            }
            da_free_array(test_array);
        }

        printf("Following (first with 0 diff): ");
        {
            double *test_array = malloc(5 * sizeof(double));

            assert(test_array);

            double *end = test_array + 5;
            test_array[0] = 1.1;
            test_array[1] = 2.1;
            test_array[2] = 4.;
            test_array[3] = 5.;
            test_array[4] = 4.1;

            double result_array[] = { 4., 5., 4.1 };

            da_normalize_array(&test_array, &end, 1.1);
            if (compare_array(test_array, result_array, 3))
                printf("OK\n");
            else
            {
                printf("FAILED\n");
                err_count++;
            }
            da_free_array(test_array);
        }

        printf("First and last (not same): ");
        {
            double *test_array = malloc(5 * sizeof(double));

            assert(test_array);

            double *end = test_array + 5;
            test_array[0] = 3.1;
            test_array[1] = 4.1;
            test_array[2] = 4.;
            test_array[3] = 5.;
            test_array[4] = 1.1;

            double result_array[] = { 4.1, 4., 5. };

            da_normalize_array(&test_array, &end, 1.1);
            if (compare_array(test_array, result_array, 3))
                printf("OK\n");
            else
            {
                printf("FAILED\n");
                err_count++;
            }
            da_free_array(test_array);
        }

        printf("Two minimal following: ");
        {
            double *test_array = malloc(5 * sizeof(double));

            assert(test_array);

            double *end = test_array + 5;
            test_array[0] = -2.;
            test_array[1] = -2.;
            test_array[2] = -2.;
            test_array[3] = 2.;
            test_array[4] = 2.;

            double result_array[] = { -2., 2., 2. };

            da_normalize_array(&test_array, &end, 2.);
            if (compare_array(test_array, result_array, 3))
                printf("OK\n");
            else
            {
                printf("FAILED\n");
                err_count++;
            }
            da_free_array(test_array);
        }

        printf("\n%s: %s\n\n", "da_normalize_array", err_count ? "FAILED" : "OK");
    }
    {
        printf("\n--- %s ---\n\n", "da_reallocate_array");
        int err_count = 0;

        printf("Malloc behavior test (allocation): ");
        {
            double *test_array = NULL, *end_array = NULL;

            int status = da_reallocate_array(&test_array, &end_array, 3);

            assert(status == 0);
            printf("OK\n");
            da_free_array(test_array);
            end_array = NULL;
        }

        printf("Realloc behavior test (reallocation): ");
        {
            double *test_array = NULL, *end_array = NULL;
            test_array = (double*) malloc(3 * sizeof(double));

            int status = da_reallocate_array(&test_array, &end_array, 6);

            assert(status == 0);
            printf("OK\n");

            da_free_array(test_array);
            end_array = NULL;
        }

        printf("Realloc for same size: ");
        {
            double *test_array = NULL, *end_array = NULL;

            test_array = (double*) malloc(3 * sizeof(double));
            end_array = test_array + 3;

            double *clone_test_array = test_array;
            double *clone_end_array = end_array;

            int status = da_reallocate_array(&test_array, &end_array, 3);

            assert(status == 0);
            assert((test_array == clone_test_array) && (end_array == clone_end_array));
            printf("OK\n");

            da_free_array(test_array);
            end_array = NULL;
            clone_test_array = NULL;
            clone_end_array = NULL;
        }
        printf("\n%s: %s\n\n", "da_reallocate_array", err_count ? "FAILED" : "OK");
    }

    if (hlib)
        dlclose(hlib);

}

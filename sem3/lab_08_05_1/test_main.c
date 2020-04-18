#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "array_utility_funcs.h"

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

void test_find_min(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("First element min: ");
    {
        double test_array[] = { 1., 2., 3., 4. };
        double *end_array = test_array + 4;
        double value = find_min(test_array, end_array);

        if (!(value - test_array[0]))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("Last element min: ");
    {
        double test_array[] = { 4., 4., 1., -1.2 };
        double *end_array = test_array + 4;
        double value = find_min(test_array, end_array);

        if (!(value - test_array[3]))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("Element in the middle: ");
    {
        double test_array[] = { 4., 4., -2., -1.2 };
        double *end_array = test_array + 4;
        double value = find_min(test_array, end_array);

        if (!(value - test_array[2]))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("All elements are min: ");
    {
        double test_array[] = { 0., 0., 0., 0. };
        double *end_array = test_array + 4;
        double value = find_min(test_array, end_array);

        if (!(value - 0.))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("Normal test: ");
    {
        double test_array[] = { 7., -1., -0.99999, 0. };
        double *end_array = test_array + 4;
        double value = find_min(test_array, end_array);

        if (!(value - test_array[1]))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_find_max(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("First element max: ");
    {
        double test_array[] = { 4., 2., 3., 4. };
        double *end_array = test_array + 4;
        double value = find_max(test_array, end_array);

        if (!(value - test_array[0]))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("Last element max: ");
    {
        double test_array[] = { 4., 4., 1., 4.1 };
        double *end_array = test_array + 4;
        double value = find_max(test_array, end_array);

        if (!(value - test_array[3]))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("Element in the middle: ");
    {
        double test_array[] = { 4., 4., 6.3, -1.2 };
        double *end_array = test_array + 4;
        double value = find_max(test_array, end_array);

        if (!(value - test_array[2]))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("All elements are max: ");
    {
        double test_array[] = { 0., 0., 0., 0. };
        double *end_array = test_array + 4;
        double value = find_max(test_array, end_array);

        if (!(value - 0.))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("Normal test: ");
    {
        double test_array[] = { -10., 11., 10.9999, 0. };
        double *end_array = test_array + 4;
        double value = find_max(test_array, end_array);

        if (!(value - test_array[1]))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_move_to_end(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Move first element: ");
    {
        double array1[] = { 1., 2., 3., 4. };
        double array2[] = { 2., 3., 4., 4. };
        move_to_end(array1, array1 + 4);

        if (compare_array(array1, array2, 4))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("Move middle element: ");
    {
        double array1[] = { 1., 2., 3., 4. };
        double array2[] = { 1., 2., 4., 4. };
        move_to_end(array1 + 2, array1 + 4);

        if (compare_array(array1, array2, 4))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("Move last element: ");
    {
        double array1[] = { 1., 2., 3., 4. };
        double array2[] = { 1., 2., 3., 4. };
        move_to_end(array1 + 3, array1 + 4);

        if (compare_array(array1, array2, 4))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }
    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_reallocate_array(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Malloc behavior test (allocation): ");
    {
        double *test_array = NULL, *end_array = NULL;

        int status = reallocate_array(&test_array, &end_array, 3);

        assert(status == 0);
        printf("OK\n");
        free(test_array);
        end_array = NULL;
    }

    printf("Realloc behavior test (reallocation): ");
    {
        double *test_array = NULL, *end_array = NULL;
        test_array = (double*) malloc(3 * sizeof(double));

        int status = reallocate_array(&test_array, &end_array, 6);

        assert(status == 0);
        printf("OK\n");

        free(test_array);
        end_array = NULL;
    }

    printf("Realloc for same size: ");
    {
        double *test_array = NULL, *end_array = NULL;

        test_array = (double*) malloc(3 * sizeof(double));
        end_array = test_array + 3;

        double *clone_test_array = test_array;
        double *clone_end_array = end_array;

        int status = reallocate_array(&test_array, &end_array, 3);

        assert(status == 0);
        assert((test_array == clone_test_array) && (end_array == clone_end_array));
        printf("OK\n");

        free(test_array);
        end_array = NULL;
        clone_test_array = NULL;
        clone_end_array = NULL;
    }
// Тест успешно проходит, но:
// Argument 'size' of function realloc has a fishy (possibly negative) value: -24 (valgrind)
/*
    printf("Realloc with negative size: ");
    {
        double *test_array = NULL, *end_array = NULL;
        int status;

        test_array = (double*) malloc(3 * sizeof(double));
        end_array = test_array + 3;

        status = reallocate_array(&test_array, &end_array, -3);

        if (status == -1)
            printf("OK\n");
        else
        {
            printf("FAILED\n");

            err_count++;
        }

        free(test_array);
        end_array = NULL;
    }
*/
//    printf("OS denial test: ");
//    {
//        double *test_array = NULL, *end_array = NULL;
//        int status;

//        status = reallocate_array(&test_array, &end_array, 0, 3276799999);

//        if (status == -1)
//            printf("OK\n");
//        else
//        {
//            printf("FAILED\n");

//            err_count++;
//        }

//        free(test_array);
//        end_array = NULL;
//    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_normalize_array(void)
{
    printf("\n--- %s ---\n\n", __func__);
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

        normalize_array(&test_array, &end, 1.1);
        if (compare_array(test_array, result_array, 3))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
        free(test_array);
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

        normalize_array(&test_array, &end, 1.1);
        if (compare_array(test_array, result_array, 3))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
        free(test_array);
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

        normalize_array(&test_array, &end, 1.1);
        if (compare_array(test_array, result_array, 3))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
        free(test_array);
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

        normalize_array(&test_array, &end, 1.1);
        if (compare_array(test_array, result_array, 3))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
        free(test_array);
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

        normalize_array(&test_array, &end, 2.);
        if (compare_array(test_array, result_array, 3))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
        free(test_array);
    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}


void test_f_equal(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Equal: ");
    {
        double num1 = 1.1;
        double num2 = 1.1;

        if (f_equal(num1, num2))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("Not equal: ");
    {
        double num1 = 2.1;
        double num2 = 1.1;

        if (!f_equal(num1, num2))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }

    printf("CLose to zero equality: ");
    {
        double num1 = 0.000000000000001;
        double num2 = 0.000000000000001;

        if (f_equal(num1, num2))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }
    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_insert_to_pos(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Normal test: ");
    {
        double test_array[4] = { 1.2, 3.4, 5.6 };
        double result_array[] = { 1.2, -1, 3.4, 5.6 };
        int pos = 1;

        insert_to_pos(test_array, test_array + 4, pos, -1);
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

        insert_to_pos(test_array, test_array + 4, pos, -1);
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

        insert_to_pos(test_array, test_array + 4, pos, -1);
        if (compare_array(test_array, result_array, 4))
            printf("OK\n");
        else
        {
            printf("FAILED\n");
            err_count++;
        }
    }
    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

int main(void)
{
    setbuf(stdout, NULL);

    test_find_min();
    test_find_max();
    test_move_to_end();
    test_reallocate_array();
    test_normalize_array();
    test_f_equal();
    test_insert_to_pos();
}

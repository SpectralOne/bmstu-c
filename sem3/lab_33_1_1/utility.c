#include "utility.h"
#include <string.h>
#include <stdlib.h>

int count_file(FILE *f)
{
    int count = 0, status = 1;
    student_t *tmp = malloc(sizeof(student_t));
   
    while ((status = read_struct(f, tmp)) == 1)
    {
        if (tmp->name)
            free(tmp->name);
        if (status == 1)
            count++;
    }
    
    if (tmp->name)
        free(tmp->name);
    free(tmp);
    
    if (status == 0)
        return count;

    return -1;
}

int is_equal(const student_t student1, const student_t student2)
{
    if (!strcmp(student1.name, student2.name))
        if (student1.year == student2.year)
            return 1;
    return 0;
}

int array_search(student_t *arr, const int size, student_t student)
{
    if (!arr)
        return 0;
    else
        for (int i = 0; i < size; i++)
            if (is_equal(arr[i], student))
                return 1;
    return 0;
}

student_t *get_sym_diff_arr(student_t *arr1, const int size1, student_t *arr2, const int size2, int *size_res)
{
    if (!arr1 && !arr2)
        return NULL;

    student_t *res_arr = allocate_array(MAX_ARR_SIZE * 2);
    if (!res_arr)
        return NULL;

    int cur_size = 0;

    for (int i = 0; i < size1; i++)
        if (!array_search(arr2, size2, arr1[i]))
            res_arr[cur_size++] = arr1[i];

    for (int i = 0; i < size2; i++)
        if (!array_search(arr1, size1, arr2[i]))
            res_arr[cur_size++] = arr2[i];

    if (!cur_size)
    {
        free(res_arr);
        return NULL;
    }

    if (compress(&res_arr, cur_size, MAX_ARR_SIZE) != 0)
    {
        free_arr(res_arr, cur_size);
        return NULL;
    }

    *size_res = cur_size;

    return res_arr;
}

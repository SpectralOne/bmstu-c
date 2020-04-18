#include "cdio.h"
#include <stdlib.h>
#include <string.h>

void free_arr(student_t *arr, int size)
{
    for (int i = 0; i < size; i++)
        if (arr[i].name)
            free(arr[i].name);

    free(arr);
}

int compress(student_t **arr, const int actual_size, int cur_size)
{
    // for (int i = cur_size - 1; i > actual_size; i--)
        // if ((*arr)[i].name)
            // free((*arr)[i].name);

    student_t *tmp = (student_t *) realloc(*arr, sizeof(student_t) * actual_size);
    if (tmp)
    {
        *arr = tmp;
        return 0;
    }

    return -1;
}

student_t *allocate_array(const int size)
{
    student_t *tmp = NULL;
    tmp = (student_t *) malloc(size * sizeof(student_t));

    return tmp;
}

char *allocate_string(const int size)
{
    char *tmp = malloc((size + 1) * sizeof(char));
    if (tmp)
        return tmp;

    return NULL;
}

int get_string(FILE *f, char *string)
{
    if (fgets(string, MAX_NAME_LEN, f) != NULL)
    {
        if (string[strlen(string) - 1] == '\n')
        {
            string[strlen(string) - 1] = 0;
            if (strlen(string))
                return 0;
        }
    }
    return -1;
}

int read_struct(FILE *f, student_t *student)
{
    char buf[4];
    int fields = 0;
    student->name = NULL;

    char string[MAX_NAME_LEN + 1] = { 0 };

    if (get_string(f, string) == 0)
    {
        fields++;
        student->name = allocate_string(strlen(string));
        if (student->name)
            strcpy(student->name, string);
        else 
            return -1;   
    }

    if (fscanf(f, "%d", &(student->year)) == 1 && student->year > 1)
        fields++;
    fgets(buf, sizeof(buf), f);

    if (fields == 2)
        return 1;
    
    if (fields > 0)
        return -1;

    return 0;
}

student_t *get_struct_array(FILE *f, int *size)
{
    student_t *arr = allocate_array(MAX_ARR_SIZE);
    if (!arr)
        return NULL;
    
    *size = count_file(f);

    if (*size < 1)
    {
        free(arr);
        return NULL;
    }

    if (compress(&arr, *size, MAX_ARR_SIZE) != 0) 
    {
        free_arr(arr, *size);
        return NULL;
    }

    rewind(f);

    for (int i = 0; i < *size; i++)
        read_struct(f, &arr[i]);

    return arr;
}

void print_arr(FILE *f, student_t *arr, const int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", arr[i].name);
        printf("%d\n", arr[i].year);
    }
}

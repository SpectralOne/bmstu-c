#include <stdio.h>
#include <string.h>
#define OK             0
#define WRONG_CMD_ERR -1
#define FILE_ERR      -2
#define READ_ERR      -3
#define MAX_LEN_ERR   -4
#define MAX_NAME_LEN  20
#define MAX_COUNT      5
typedef char name_t[MAX_NAME_LEN + 1];
typedef long square_t;
typedef long population_t;
typedef struct
{
    name_t name;
    square_t square;
    population_t population;
}country_t;

void usage(void)
{
    printf("Usage: app.exe [file]\n\nfile - file name");
}

void print_struct(const country_t* country)
{
    printf("Name: %s\n", country->name);
    printf("Square: %ld\n", country->square);
    printf("Population: %ld\n", country->population);
}

void print_struct_array(const country_t* arr, const int size)
{
    for (int i = 0; i < size; i++)
    {
        print_struct(&arr[i]);
        printf("\n");
    }
}

int read_country_country(FILE* f, country_t* country)
{
    char buf[4];
    int status = READ_ERR, len;

    if (fgets(country->name, sizeof(country->name), f) != NULL)
    {
        len = strlen(country->name);
        if (country->name[len - 1] == '\n')
        {
            country->name[len - 1] = '\0';
            if (fscanf(f, "%ld %ld", &country->square, &country->population) == 2)
                status = OK;
        }
        else
            status = MAX_LEN_ERR;
    }
    fgets(buf, sizeof(buf), f);

    return status;
}

void read_country_array(FILE* f, country_t* arr, int *size)
{
    country_t country;
    int flag = 1;
    *size = 0;

    while ((read_country_country(f, &country) == OK) && flag)
    {
        if (*size < MAX_COUNT)
        {
            arr[*size] = country;
            *size += 1;
        }
        else
            flag = 0;
    }
}

double calc_density(country_t* country)
{
     return (double) country->population / country->square;
}

double get_average_density(country_t* arr, int size)
{
    double buf = 0.0;
    for (int i = 0; i < size; i++)
        buf += calc_density(&arr[i]);
    return buf / size;
}

void rearrange_struct_array(country_t* arr, int size, double avg_density)
{
    int to = 0;
    country_t tmp;
    for (int i = 0; i < size; i++)
    {
        if (calc_density(&arr[i]) > avg_density)
        {
            tmp = arr[to];
            arr[to] = arr[i];
            arr[i] = tmp;

            to++;
        }
    }
}

int main(int argc, char **argv)
{
    int status = OK, size = 0;
    double average_density;
    country_t arr[MAX_COUNT];
    FILE* f;

    if (argc != 2)
    {
        usage();
        status = WRONG_CMD_ERR;
    }
    else
    {
        f = fopen(argv[1], "r");
        if (f)
        {
            read_country_array(f, arr, &size);
            if (size)
            {
//                print_struct_array(arr, size);

                average_density = get_average_density(arr, size);
                rearrange_struct_array(arr, size, average_density);

                print_struct_array(arr, size);
            }
            else
            {
                printf("Empty or corrupted file");
                status = READ_ERR;
            }
            fclose(f);
        }
        else
        {
            printf("File error!");
            status = FILE_ERR;
        }
    }
    return status;
}
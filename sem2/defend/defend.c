#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define MAX_STR_LEN 128
#define OK 0
#define WRONG_CMD -1
#define FILE_ERR -2
#define FILE_READ_ERR -3
#define NO_STRINGS -4

void usage(void)
{
    printf("usage: app.exe [file]\n"
           "[file] - file name\n");
}

int find_max(FILE *f, int *max_len)
{
    int current_len, status = FILE_READ_ERR;
    *max_len = NO_STRINGS;
    char str[MAX_STR_LEN + 1];

    while (fgets(str, sizeof(str), f))
    {
        status = OK;
        current_len = strlen(str);
        str[current_len - 1] = 0;

        if (str[0] == str[current_len - 2] && str[0] != '\0')
            if (current_len - 1 > *max_len)
                *max_len = current_len - 1;
    }
    return status;
}

int main(int argc, char **argv)
{
    int status = OK;

    if (argc != 2)
    {
        status = WRONG_CMD;
        printf("Wrong command line arguments!\n");
        usage();
    }
    else
    {
        FILE *f = fopen(argv[1], "r");
        if (f)
        {
            int max_len = 0;
            status = find_max(f, &max_len);

            if (status != OK)
                printf("Error while reading file!");
            else if (max_len == NO_STRINGS)
            {
                status = NO_STRINGS;
                printf("No special strings in file!");
            }
            else
                printf("Max string length = %d", max_len);
        }
        else
        {
            status = FILE_ERR;
            fprintf(stderr, "Error! Can't open file %s due to: %s \n", argv[1], strerror(errno));
        }
    }
    return status;
}
#include "array.h"

int main(int argc, char** argv)
{
    int size, status = OK;
    array a;
    FILE* f;
    if (argc == 2)
    {
        f = fopen(argv[1], "r");

        if (f != NULL)
        {
            status = read_array (f, a, &size);
            if (!status)
            {
                sort_array(a, size);
                print_array(a, size);
            }
            else
                printf ("Read error");
        }
        else
        {
            fclose(f);
            printf("File error");
            status = FILE_ERR;
        }
    }
    else
    {
        printf("Bad cmd");
        status = CMD_ERR;
    }
    return status;
}

/*
   Программа создаёт и заполняет файл указанным числом случайных чисел
   Выводит числовую последовательность файла, затем сортирует её
   Метод сортировки: пузырьком
   Сортировка в порядке возрастания
   Тип чисел: int
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#define OK 0
#define WRONG_CMD_ERR -1
#define READ_ERR -2
#define WRITE_ERR -3
#define ERROR -4
#define FILE_ERR -5
#define NO_NUM -6

void usage(void)
{
    printf("usage: app.exe [c] [p] [s] [file] [amount] \n"
        "[file] - file name\n"
        "[c] - create file\n"
        "[p] - print file\n"
        "[s] - sort file\n"
        "[amount] - amount of number to write to file");
}

int create(FILE *f, long amount)
{
    int rand_num, status = OK;
    srand(time(NULL));

    for (long i = 0; i < amount && status == OK; i++)
    {
        rand_num = rand() % 10;
        if (fwrite(&rand_num, sizeof(int), 1, f) != 1)
            status = WRITE_ERR;
    }
    return status;
}

int print(FILE *f)
{
    int num = 0, status = READ_ERR;
    while (fread(&num, sizeof(int), 1, f) == 1)
    {
        status = OK;
        printf("%d ", num);
    }
    return status;
}

int get_num_by_pos(FILE *f, int pos, int *num)
{
    int status = ERROR;
    pos *= sizeof(int);

    if (fseek(f, pos, SEEK_SET) == 0)
        if (fread(num, sizeof(int), 1, f) == 1)
            status = OK;

    return status;
}

int put_num_by_pos(FILE *f, int pos, int num)
{
    int status = ERROR;
    pos *= sizeof(int);

    if (fseek(f, pos, SEEK_SET) == 0)
        if (fwrite(&num, sizeof(int), 1, f) == 1)
            status = OK;

    return status;
}

int get_file_size(FILE* f, int *size)
{
    int status = OK;
    long check;

    if (fseek(f, 0, SEEK_END) == 0)
    {
        if ((check = ftell(f)) == -1L)
            status = ERROR;
        *size = check / sizeof(int);
    }
    return status;
}

int sort(FILE *f)
{
    int a1 = 0, a2 = 0, size, status = ERROR;
    status = get_file_size(f, &size);

    if (size > 0)
    {
        status = OK;
        for (int i = 0; i < (size - 1) && status == OK; i++)
            for (int j = 0; j < (size - i - 1) && status == OK; j++)
            {
                status = get_num_by_pos(f, j, &a1);
                status = get_num_by_pos(f, j + 1, &a2);

                if (a1 > a2)
                {
                    status = put_num_by_pos(f, j, a2);
                    status = put_num_by_pos(f, j + 1, a1);
                }
            }
    }
    else
        status = ERROR;
    return status;
}


int main(int argc, char **argv)
{
    int status = OK;
    FILE *f;

    if (argc < 3 || argc > 4)
    {
        usage();
        status = WRONG_CMD_ERR;
    }
    else
    {
        if (strcmp(argv[1], "c") == 0)
        {
            f = fopen(argv[2], "wb");
            if (f)
            {
                char *buf;
                long amount = strtol(argv[3], &buf, 10);

                if (*buf == '\0' && amount)
                {
                    status = create(f, amount);
                    fclose(f);
                    if (status != OK)
                        printf("Error while writing to file!");
                }
                else
                {
                    status = NO_NUM;
                    printf("Amount not properly given!");
                }
            }
            else
            {
                fprintf(stderr, "Error! Can't open file %s due to: %s \n", argv[2], strerror(errno));
                status = FILE_ERR;
                usage();
            }
        }
        else if (strcmp(argv[1], "p") == 0)
        {
            f = fopen(argv[2], "rb");
            if (f)
            {
                status = print(f);
                fclose(f);

                if (status != OK)
                    printf("File read error!");
            }
            else
            {
                fprintf(stderr, "Error! Can't open file %s due to: %s \n", argv[2], strerror(errno));
                status = FILE_ERR;
                usage();
            }
            if (status == READ_ERR)
                printf("Input error!");
        }
        else if (strcmp(argv[1], "s") == 0)
        {
            f = fopen(argv[2], "r+b");
            if (f)
            {
                status = sort(f);
                fclose(f);

                if (status != OK)
                    printf("Error while operating with file!");
            }
            else
            {
                fprintf(stderr, "Error! Can't open file %s due to: %s \n", argv[2], strerror(errno));
                status = FILE_ERR;
                usage();
            }
        }
    }
    return status;
}

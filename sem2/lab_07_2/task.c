#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define VALID 1
#define OK 0
#define FILE_ERR -1
#define ERROR -2
#define READ_ERR -3
#define OVERFLOW_ERR -4
#define FILE_READ_ERR -5
#define CORRUPTED_FILE -6
#define WRONG_CMD_ERR 53
#define MAX_NAME_LEN 30
#define MAX_MANUFACTURER_LEN 15
typedef char name_t[MAX_NAME_LEN + 1];
typedef char manufacturer_t[MAX_MANUFACTURER_LEN + 1];
typedef uint32_t price_t;
typedef uint32_t amount_t;
typedef struct
{
    name_t name;
    manufacturer_t manufacturer;
    price_t price;
    amount_t amount;
}product_t;

/*
 Функция-справка по использованию приложения
 Ничего не принимает, ничего не возвращает
*/
void usage(void)
{
    printf("General usage: app.exe [sb] [at] [file_in] [file_out] [file_in_out]\n\n"
        "Sort binary file (result to another file): app.exe [sb] [file_in] [file_out]\n"
        "Append to text file: app.exe [at] [file_in_out]\n\n"
        "[sb] - sort binary file mode\n"
        "[at] - append to text file mode\n"
        "[file_in] -  input file\n"
        "[file_out] - output file\n"
        "[file_in_out] - file to read from and write to");
}

/*
 Функция вывода структуры на экран
 Принимает на вход указатель на структуру
 Ничего не возвращает
*/
void print_struct(const product_t *unit)
{
    printf("%s\n", unit->name);
    printf("%s\n", unit->manufacturer);
    printf("%u\n", unit->price);
    printf("%u\n", unit->amount);
}

// ----Binary file fucntions---- //

/* Далее подразумевается описание функций, относящихся только к бинарному файлу */

/*
 Функция определяет количество структур в файле
 Принимает на вход указатель на файл и размер
 Вернёт ОК если всё прошло успешно, иначе код ошибки
 Побочный эффект: смещается указатель в файле
*/
long filelen_binary(FILE* f, long *size)
{
    int status = OK;
    long whole_size = 0;
    *size = 0;

    if (fseek(f, 0, SEEK_END) == 0)
    {
        if ((whole_size = ftell(f)) == -1L)
            status = FILE_READ_ERR;
        else
        {
            if (whole_size % sizeof(product_t))
                status = CORRUPTED_FILE;
            else
                *size = whole_size / sizeof(product_t);
        }
    }
    return status;
}

/*
 Функция получает структуру из файла по заданной позиции
 Получает на вход указатель на файл, позицию и указатель на структуру
 Вернёт ОК если всё прошло успешно, иначе код ошибки
 Побочный эффект: смещается указатель в файле
*/
int get_struct_by_pos(FILE* f, int pos, product_t *to)
{
    int status = ERROR;
    pos *= sizeof(product_t);

    if (fseek(f, pos, SEEK_SET) == 0)
        if (fread(to, sizeof(product_t), 1, f) == 1)
            status = OK;
    return status;
}

/*
 Функция записывает структуру в файла на заданную позицию
 Получает на вход указатель на файл, позицию и структуру
 Вернёт ОК если всё прошло успешно, иначе код ошибки
 Побочный эффект: смещается указатель в файле
*/
int put_struct_by_pos(FILE* f, int pos, product_t from)
{
    int status = ERROR;
    pos *= sizeof(product_t);

    if (fseek(f, pos, SEEK_SET) == 0)
        if (fwrite(&from, sizeof(product_t), 1, f) == 1)
            status = OK;
    return status;
}

/*
 Функция сортирует структуры в файле
 Принимает на вход указатель на файл
 Тип сортировки: по убыванию цены за единицу товара
                * сначала идут товары с наибоольшем количеством
 Вернёт ОК если всё прошло успешно, иначе код ошибки
 Побочный эффект: смещается указатель в файле
*/
int sort_binary_file(FILE* f, long size)
{
    int status = OK;
    product_t unit1, unit2;

    for (int i = 0; i < (size - 1) && status == OK; i++)
        for (int j = 0; j < (size - i - 1) && status == OK; j++)
        {
            status = get_struct_by_pos(f, j, &unit1);
            status = get_struct_by_pos(f, j + 1, &unit2);

            if (unit1.price < unit2.price)
            {
                status = put_struct_by_pos(f, j, unit2);
                status = put_struct_by_pos(f, j + 1, unit1);
            }
            if ((unit1.price == unit2.price) && (unit1.amount < unit2.amount))
            {
                status = put_struct_by_pos(f, j, unit2);
                status = put_struct_by_pos(f, j + 1, unit1);
            }
        }
    return status;
}

/*
 Функция копирует содержимое из одного файла в другой
 Принимает на вход указатели на файлы:
             * Откуда будут копироваться данные
             * Куда будут копироваться данные
 Функция ничего не возвращает
 Побочный эффект: смещается указатель в файлах
*/
void copy_binary(FILE* from, FILE* to)
{
    void *buf;
    size_t size, read;

    fseek(from, 0L, SEEK_END);
    size = ftell(from);
    fseek(from, 0L, SEEK_SET);

    buf = malloc(size);

    read = fread(buf, 1, size, from);
    fwrite(buf, 1, read, to);

    free(buf);
}

// ----Text file functions---- //

/* Далее подразумевается описание функций, относящихся только к текстовому файлу */

/*
 Функция считывает из файла структуру
 Принимает на вход указатель на файл и указатель на структуру
 Вернёт ОК если всё прошло успешно, иначе код ошибки
 Побочный эффект: смещается указатель в файле
*/
int read_product_info(FILE* f, product_t *unit)
{
    char buf[4];
    int status = READ_ERR, len, checker = 0;

    if (fgets(unit->name, sizeof(unit->name), f) != NULL)
    {
        len = strlen(unit->name);
        if (unit->name[len - 1] == '\n')
        {
            unit->name[len - 1] = '\0';
            checker++;
            if (fgets(unit->manufacturer, sizeof(unit->manufacturer), f) != NULL)
            {
                len = strlen(unit->manufacturer);
                if (unit->manufacturer[len - 1] == '\n')
                {
                    unit->manufacturer[len - 1] = '\0';
                    checker++;
                    if (fscanf(f, "%u %u", &unit->price, &unit->amount) == 2)
                    {
                        checker++;
                        status = OK;
                    }
                    else
                        status = READ_ERR;
                }
                else
                    status = OVERFLOW_ERR;
            }
            else
                status = READ_ERR;
        }
        else
            status = OVERFLOW_ERR;
    }
    else
        status = READ_ERR;
    fgets(buf, sizeof(buf), f);

    if (checker && checker != 3)
        status = CORRUPTED_FILE;
    return status;
}

/*
 Функция определяет количество структур в файле
 Принимает на вход указатель на файл
 Возвращает размер файла
 Побочный эффект: указатель в файле смещается в начало
*/
long filelen_text(FILE* f)
{
    product_t unit;
    long size = 0;

    fseek(f, 0L, SEEK_SET);
    while (read_product_info(f, &unit) == OK)
        size++;

    fseek(f, 0L, SEEK_SET);
    return size;
}

/*
 Функция считывает содержимое файла в массив
 Принимает на вход указатель на файл и на массив
 Функция ничего не возвращает
 Допущение: файл заполнен правильными данными (успешность функции is_valid_text)
 Побочный эффект: смещается указатель в файле
*/
void read_product_array(FILE* f, product_t *arr)
{
    long i = -1;
    product_t unit;

    while (read_product_info(f, &unit) == OK)
        arr[++i] = unit;
}

/*
 Функция записывает структуру в файл
 Принимает на вход указатель на файл и на структуру
 Функция ничего не возвращает
 Побочный эффект: смещается указатель в файле
*/
void write_struct(FILE* f, const product_t *unit)
{
    fprintf(f, "%s\n", unit->name);
    fprintf(f, "%s\n", unit->manufacturer);
    fprintf(f, "%u\n", unit->price);
    fprintf(f, "%u\n", unit->amount);
}

/*
 Функция вставляет новую запись о продукте в массив структур таким образом, что бы не нарушить порядок
 Принимает на вход указатель на массив структур, размер массива и структуру
 Функция ничего не возвращает
 Побочный эффект: смещается указатель в файле
*/
void insert_product(product_t *arr, long *size, product_t unit)
{
    int i = 0;
    int flag = 0;
    while (flag == 0 && i < *size)
    {
        if (arr[i].price < unit.price)
        {
            for (int j = *size; j >= i ; j--)
            {
                arr[j] = arr[j - 1];
            }
            arr[i] = unit;
            flag = 1;
            *size += 1;
        }
        if (arr[i].price == unit.price)
        {
            if (arr[i].amount < unit.amount)
            {
                for (int j = *size; j >= i ; j--)
                {
                    arr[j] = arr[j - 1];
                }
                arr[i] = unit;
                flag = 1;
                *size += 1;
            }
        }
        i++;
    }
    if (flag == 0)
    {
        arr[*size] = unit;
        *size += 1;
    }
}

/*
 Функция проверяет правильность данных в файле
 Получает на вход указатель на файл
 Возвращает признак VALID или ошибку
 Побочный эффект: указатель в файле смещается в начало
*/
int is_valid_text(FILE* f, long *size)
{
    product_t unit;
    int status;
    *size = 0;

    while ((status = (read_product_info(f, &unit))) == OK);
    fseek(f, 0L, SEEK_SET);

    if (status != CORRUPTED_FILE)
    {
        *size = filelen_text(f);
        if (*size)
            status = VALID;
        else
            status = FILE_ERR;
    }
    return status;
}

/*
 Функция записывает массив структур в файл
 Принимает на вход указатель файл, массив структур и размер массива структур
 Функция ничего не возвращает
 Побочный эффект: смещается указатель в файле
*/
void write_array_to_file(FILE *f, const product_t *arr, const long size)
{
    for (int i = 0; i < size; i++)
        write_struct(f, &arr[i]);
}

int main(int argc, char **argv)
{
    int status = OK;

    if (argc < 3 || argc > 4)
    {
        usage();
        status = WRONG_CMD_ERR;
    }
    else
    {
        if (strcmp(argv[1], "sb") == 0)
        {
            FILE* unsorted_b = fopen(argv[2], "rb");
            if (unsorted_b)
            {
                long size;
                status = filelen_binary(unsorted_b, &size);
                if (status == OK && size)
                {
                    FILE* sorted_b = fopen(argv[3], "w+b");
                    copy_binary(unsorted_b, sorted_b);
                    status = sort_binary_file(sorted_b, size);

                    fclose(sorted_b);
                    fclose(unsorted_b);
                }
                else
                {
                    fclose(unsorted_b);
                    if (!size)
                        status = FILE_ERR;
                }
            }
            else
            {
                status = FILE_ERR;
                usage();
            }
        }
        else if (strcmp(argv[1], "at") == 0)
        {
            FILE* append_t = fopen(argv[2], "r");
            if (append_t)
            {
                long size;
                status = is_valid_text(append_t, &size);
                if (status == VALID)
                {
                    product_t arr[size + 1], unit;

                    read_product_array(append_t, arr);
                    fclose(append_t);

                    status = read_product_info(stdin, &unit);
                    if (status == OK)
                    {
                        insert_product(arr, &size, unit);

                        FILE* append_t = fopen(argv[2], "w");
                        write_array_to_file(append_t, arr, size);
                        fclose(append_t);
                    }
                }
                else
                    fclose(append_t);
            }
            else
            {
                usage();
                status = FILE_ERR;
            }
        }
        else
        {
            status = WRONG_CMD_ERR;
            usage();
        }
    }
    return status;
}

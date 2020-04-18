#include <stdio.h>
#include <stdarg.h>

int count_lines(char *file_name, ...)
{
    int count = 0;

    char *buf = file_name;
    if (!buf)
        return count;

    va_list argv;
    va_start(argv, file_name);

    do
    {
        FILE *f = fopen(buf, "r");
        buf = NULL;
        if (f)
        {
//            char line_buf[1000]; <- плохой вариант
//            while (fgets(line_buf, sizeof(line_buf), f)) count++;
            char c;
            while (fscanf(f, "%c", &c) == 1)
                if (c == '\n')
                    count++;
            count++;
            fclose(f);
        }
    } while ((buf = va_arg(argv, char *)) != NULL);
    va_end(argv);

    return count;
}

int main(void)
{
    printf("Lines count = %d", count_lines("1.txt", "2.txt", "3.txt", NULL));
    return 0;
}

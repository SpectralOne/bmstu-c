#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define OK 0
#define INP_ERR -1
#define EMPTY_STR -2
#define STR_OVERFLOW -3
#define MAX_STR_LEN 128
typedef char string_t[MAX_STR_LEN + 1];

void form_string(string_t str)
{
    const char punct_marks[] = ",!?;:";
    string_t buf;
    int i = 0, j = - 1, space = 0;

    while (++j < strlen(str) && str[j] == ' ');

    if (!isupper(str[j]))
        str[j] = str[j] - 32;

    while (j < strlen(str))
    {
        if (str[j] != ' ')
        {
            if (strchr(punct_marks, str[i]) && i - 1 >= 0 && str[i - 1] == ' ')
                str[i - 1] = str[j++];
            else
                str[i++] = str[j++];
            space = 0;
        }
        else if (str[j++] == ' ')
        {
            if (!space)
            {
                str[i++] = ' ';
                space = 1;
            }
        }
    }

    str[i] = 0;
    if (str[strlen(str) - 1] == ' ')
       str[strlen(str) - 1] = 0;

    for (i = 0, j = 0; i < strlen(str); i++)
    {
        if (strchr(punct_marks, str[i]) && (str[i + 1] != ' ' || str[i + 1] != '\0'))
        {
            buf[j++] = str[i];
            buf[j++] = ' ';
        }
        else
            buf[j++] = str[i];
    }

    if ((buf[j] != '.' && buf[j-1] != '.'))
        if ((buf[j-1] != '!' && buf[j-2] != '!') && (buf[j-1] != '?' && buf[j-2] != '?'))
            buf[j++] = '.';
    buf[j] = 0;

    str[0] = 0;
    strcpy(str, buf);
    buf[0]= 0;
}

int main(void)
{
    int status = OK;
    string_t str;

    printf("Enter string: ");
    if (fgets(str, sizeof str, stdin) == NULL)
        status = INP_ERR;
    else if (str[strlen(str) - 1] != '\n')
        status = STR_OVERFLOW;
    else
    {
        str[strlen(str) - 1] = '\0';
        if (strlen(str) == 0)
            status = EMPTY_STR;
        else
        {
            status = OK;
            form_string(str);
            //"      test,string    and!word? "
            printf("Formed = %s", str);
        }
    }
    return status;
}
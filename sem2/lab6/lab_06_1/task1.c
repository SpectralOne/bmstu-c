#include <stdio.h>
#include <string.h>

char *my_strchr(char *str, int c)
{
    while (*str != c && *str != '\0')
        str++;

    if (*str == c)
        return str;

    return NULL;
}
char *my_strpbrk(char *str, char *ch)
{
    while (*str)
        if (my_strchr(ch, *str++))
            return --str;
    return NULL;
}

void test_my_strchr(void)
{
    int err_count = 0;

    char string[] = "abcd  efgh\0";
    char *pos;

    // Normal test
    pos = my_strchr(string, 'd');
    if (pos != (string + 3))
        err_count += 1;
    // Start finding
    pos = my_strchr(string, 'a');
    if (pos != string)
        err_count += 1;
    // Char not in str
    pos = my_strchr(string, 's');
    if (pos)
        err_count += 1;
    // End finding
    pos = my_strchr(string, '\0');
    if (pos != (string + 10))
        err_count += 1;
    // Char not in empty string
    pos = my_strchr("", 'a');
    if (pos)
        err_count += 1;

    printf("%s: %s\n", __func__, err_count ? "FAILED" : "OK");
}

void test_my_strpbrk(void)
{
    int err_count = 0;

    char string[] = "this is a string\0";
    char *ptr;

    // Normal test
    ptr = my_strpbrk(string, "s");
    if (strcmp(ptr, "s is a string") != 0)
        err_count += 1;
    // Substring not in string
    ptr = my_strpbrk(string, "zz");
    if (ptr)
        err_count += 1;
    // Last char finding
    ptr = my_strpbrk(string, "g");
    if (strcmp(ptr, (string + 15)) != 0)
        err_count += 1;
    // Empty string and empty substring
    ptr = my_strpbrk("", "");
    if (ptr)
        err_count += 1;
    // Empty substring
    ptr = my_strpbrk(string, "");
    if (ptr)
        err_count += 1;

    printf("%s: %s\n", __func__, err_count ? "FAILED" : "OK");
}

int main(void)
{
    test_my_strpbrk();
    test_my_strchr();

    return 0;
}

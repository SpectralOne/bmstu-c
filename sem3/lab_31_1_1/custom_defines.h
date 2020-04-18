#ifndef CUSTOM_DEFINES_H
#define CUSTOM_DEFINES_H

#define OK 0
#define NOT_FOUND -1

#define MAX_STR_LEN 100

typedef char string_t[MAX_STR_LEN + 1];

typedef struct
{
    char *title;
    char *name;
    int year;
} film_s;

#endif

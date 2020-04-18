#include <stdio.h>
#include "err_handler.h"

char *err_handler(const int status)
{
    switch (status)
    {
        case OK:
            return "Added!";
        case GRADE_ADDED:
            return "Grade added!";
        case MEM_ALLOC_ERR:
            return "Memmory allocation/reallocation error!";
        case INV_SEX:
            return "Invalid sex!";
        case INV_DATE:
            return "Invalid date!";
        case OVERFLOW_ERR:
            return "String overflow!";
        case EMPTY_STR:
            return "Empty string!";
        case EMPTY_ARRAY:
            puts("Empty array");
            break;
        case INV_STRING:
            return "Invalid character found!";
        case INV_GRADES:
            return "Invalid grades";
        case DUPLICATE:
            return "This person already exists";
        default:
            printf("Unknown error code: %d\n", status);
            break;
    }
    return "bleep-blop";
}

#include <stdio.h>

#define OK 0

#include "err_handler.h"

/**
 * @brief Handles error codes
 * 
 * @param status - error code
 */
void err_handler(const int status)
{
    return;
    
    switch (status)
    {
        case OK:
            break;
        case MEM_ALLOC_ERR:
            puts("Memmory allocation/reallocation error!");
            break;
        case READ_ERR:
            puts("I/O Error!");
            break;
        case INV_MODE:
            puts("Invalid mode!");
            break;
        case OVERFLOW_ERR:
            puts("String overflow!");
            break;
        case EMPTY_STR:
            puts("Empty string!");
            break;
        default:
            printf("Unknown error code: %d\n", status);
            break;
    }
}

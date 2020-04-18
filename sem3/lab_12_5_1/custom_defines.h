#ifndef __CUSTOM_DEFINES_H__
#define __CUSTOM_DEFINES_H__

/* --- DEFINES --- */

// Exit code
#define OK 0

// Len of string part
#define CHAR_COUNT 4

// Max string len
#define MAX_STR_LEN 256

// Position of substring outside string
#define NOT_FOUND -1

// Char to delete repetitions of
#define DELETE_CHAR ' '

// List structure
typedef struct node node_t;
struct node
{
    char data[CHAR_COUNT];
    int data_len;

    node_t *next;
};

#endif
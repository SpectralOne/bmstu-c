#include <stdio.h>
#include <string.h>

#include "custom_errors.h"
#include "custom_defines.h"
#include "list_operations.h"
#include "err_handler.h"

int read_string(char *string, const size_t size)
{
    int status = OK;

    if (fgets(string, size, stdin) == NULL)
        status = READ_ERR;
    else 
    {
        if (string[strlen(string) - 1] != '\n')
            status = OVERFLOW_ERR;
        else
        {
            string[strlen(string) - 1] = '\0';
            if (strlen(string) == 0)
                status = EMPTY_STR;
        }
    }
    return status;
}

int main(void)
{
    int status = OK;
    char mode[CHAR_COUNT + 1];

    status = read_string(mode, sizeof(mode));
    if (status != OK)
    {
        err_handler(status);
        
        return status; 
    }   

    if (!strcmp(mode, "out"))
    {
        node_t *string = NULL;

        string = read_stream(string, stdin);
        if (string)
            list_str_out(string); 
        else 
            status = MEM_ALLOC_ERR;

        if (string)
            free_list(string);
    }
    else if (!strcmp(mode, "cat"))
    {
        node_t *string1 = NULL, *string2 = NULL;

        string1 = read_stream(string1, stdin);
        if (string1)
        {
            string2 = read_stream(string2, stdin);
            if (string2)
            {
                list_str_cat(string1, string2);
                list_str_out(string1);
            }
        }

        if (!string1 || !string2)
            status = MEM_ALLOC_ERR;
            
        if (string1)
            free_list(string1);
    }
    else if (!strcmp(mode, "sps"))
    {
        node_t *string = NULL;

        string = read_stream(string, stdin);
        if (string)
        {
            list_str_sps(string);
            list_str_out(string); 
        }
        else 
            status = MEM_ALLOC_ERR;

        if (string)
            free_list(string);  
    }
    else if (!strcmp(mode, "pos"))
    {
        node_t *string = NULL;

        string = read_stream(string, stdin);
        if (string)
        {
            char sub_string[MAX_STR_LEN + 1];
            status = read_string(sub_string, sizeof(sub_string));

            if (status == OK)
            {
                status = list_str_pos(string, sub_string);

                if (status < 0)
                    printf("%d", NOT_FOUND);
                else
                    printf("%d", status);

                status = OK;
            }
        }   
        else 
            status = MEM_ALLOC_ERR;

        if (string)
            free_list(string);
    }
    else
        status = INV_MODE;
    
    err_handler(status);

    return status;
}

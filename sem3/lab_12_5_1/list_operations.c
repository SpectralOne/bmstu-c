#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list_operations.h"

/**
 * @brief Concatenates one list into another
 * 
 * @param string1 - pointer to destination list
 * @param string2 - pointer to source list
 */
void list_str_cat(node_t *string1, node_t *string2)
{
    assert(string1 && string2);

    if (string1->next == NULL)
        string1->next = string2;
    else
        list_str_cat(string1->next, string2);
}

/**
 * @brief Deletes repeated characters from string parts
 * 
 * @param string - pointer to list
 */
void list_str_sps(node_t *string)
{
    assert(string);

    int prev = 0;
    while (string)
    {
        int pos = 0;
        while (pos < string->data_len)
        {
            if (string->data[pos] == DELETE_CHAR)
            {
                if (prev)
                {
                    memmove(string->data + pos, string->data + pos + 1, string->data_len - 1 - pos);
                    string->data_len--;

                    pos--;
                }
                prev = 1;
            }
            else
                prev = 0;
            pos++;
        }
        string = string->next;
    }
}

/**
 * @brief Finds poistion of given substring in list
 * 
 * @param string - pointer to list
 * @param substring - pointer to substring
 * @return int - position
 */
int list_str_pos(node_t *string, const char *substring)
{
    assert(string && substring);

    int j = 0, str_offset = 0;
    while (string)
    {
        for (int i = 0; i < string->data_len; i++)
        {
            str_offset++;

            if (string->data[i] == substring[j])
                j++;
            else
                j = 0;
    
            if (j == (strlen(substring)))
                return str_offset - j;
        }

        string = string->next;
    }

    return NOT_FOUND;
}

/**
 * @brief Prints out list
 * 
 * @param string - pointer to list
 */
void list_str_out(node_t *string)
{
    assert(string);

    while (string)
    {
        for (int i = 0; i < string->data_len; i++)
            printf("%c", string->data[i]);

        string = string->next;
    }
}

/**
 * @brief This program purpose only char-copying function
 * 
 * @param dst - pointer to destination string
 * @param src - pointer to source string
 */
void my_cpy(char *dst, const char *src)
{
    assert(dst && src);

    for (int i = 0; i < CHAR_COUNT && src[i] != 0; i++)
        dst[i] = src[i];
}

/**
 * @brief Creates a node element
 * 
 * @param string - pointer to string part
 * @param size - size of string part
 * @return node_t* - pointer to created node
 */
node_t *create_node(const char *string, const int size)
{
    assert(string);

    node_t *tmp = (node_t*)malloc(sizeof(node_t));
    if (tmp)
    {
        my_cpy(tmp->data, string);
            
        tmp->data_len = size;
        tmp->next = NULL;
    }

    return tmp;
}

/**
 * @brief Appends new node
 * 
 * @param head - pointer to head of list
 * @param node - pointer to node
 * @return node_t* - pointer to head of list
 */
node_t *add_node(node_t *head, node_t *node)
{
    if (!head)
        return node;
 
    node_t *cur = head;
    
    while (cur->next)
        cur = cur->next;
        
    cur->next = node;
    
    return head;
}

/**
 * @brief Reads given stream into list
 * 
 * @param head - pointer to head of list
 * @param stream - pointer to stream
 * @return node_t* - pointer to head of list
 */
node_t *read_stream(node_t *head, FILE *stream)
{
    assert(stream);

    node_t *tmp;
    char string[CHAR_COUNT], c = 0; 
    int i;
    while (c != '\n')
    {
        i = 0;
        while (i < CHAR_COUNT)
        {
            fscanf(stream, "%c", &c);
            if (c == '\n')
            {
                string[i] = 0;
                break;
            }   
            string[i++] = c;
        }
        
        tmp = create_node(string, i);
        if (tmp)
            head = add_node(head, tmp);
        else
        {
            free_list(head);
            return NULL;
        }
    }
    
    return head;
}

/**
 * @brief Frees a list
 * 
 * @param head - pointer to head of list
 */
void free_list(node_t *head)
{
    node_t *tmp;
    
    while (head)
    {
        tmp = head;
        head = head->next;

        free(tmp);
    }
}

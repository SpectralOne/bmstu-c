#include <stdio.h>
#include <stdlib.h>

#include "cdio.h"

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

node_t *create_node(int data)
{
    node_t *node = (node_t*) malloc(sizeof(node_t));
    if (!node)
        return NULL;
    
    node->data = data;
    node->next = NULL;
    
    return node;
}

void free_list(node_t *head)
{
    node_t *tmp = head;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

node_t *read_file(FILE *f)
{
    node_t *head = NULL, *tmp = NULL;
    int number;
    
    while (fscanf(f, "%d", &number) == 1)
    {
        tmp = create_node(number);
        if (!tmp)
            return free_list(head), NULL;
        head = add_node(head, tmp);
    }
        
    return head;
}

void print_list(node_t *head)
{
    while (head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
}
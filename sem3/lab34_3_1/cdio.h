#ifndef __CDIO_H__
#define __CDIO_H__


#include "custom_defines.h"

node_t *add_node(node_t *head, node_t *node);
node_t *create_node(int data);
void free_list(node_t *head);
node_t *read_file(FILE *f);
void print_list(node_t *head);

#endif
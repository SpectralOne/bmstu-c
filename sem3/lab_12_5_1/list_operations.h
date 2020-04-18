#ifndef __LIST_OPERATIONS_H__
#define __LIST_OPERATIONS_H__

#include "custom_defines.h"
#include "custom_errors.h"

#include <stdio.h>

void list_str_out(node_t *head);
void list_str_cat(node_t *string1, node_t *string2);
void list_str_sps(node_t *string);
int list_str_pos(node_t *string, const char *substring);

void my_cpy(char *dst, const char *src);
node_t *create_node(const char *string, const int size);
node_t *add_node(node_t *head, node_t *node);
node_t *read_stream(node_t *head, FILE *stream);
node_t *list_reverse(node_t *head);
void free_list(node_t *head);

#endif

#define NULL ((void*)0)

#include "task.h"

node_t *magic(node_t *head1, node_t *head2)
{
    if (!head1)
        return head2;
    
    if (!head2)
        return head1;

    node_t *res = NULL, *res_head;
    
    if (head1->data < head2->data)
    {
        res = head1;
		res_head = res;
		head1 = head1->next;
		res->next = NULL;
	}
	else
	{
		res = head2;
		res_head = res;
		head2 = head2->next;
		res->next = NULL;
	}
	
    while (head1 && head2)
    {
		if (head1->data < head2->data)
		{
			res->next = head1;
			res = res->next;
			head1 = head1->next;
		}
		else
		{
			res->next = head2;
			res = res->next;
			head2 = head2->next;
		}
	/*	if (res->next)
			res->next = NULL;*/
    }
	if (!head1)
		res->next = head2;
	if (!head2)
		res->next = head1;

	return res_head;
}
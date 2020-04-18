#include <stdio.h>

#include "custom_defines.h"
#include "cdio.h"
#include "task.h"

int main(int argc, char **argv)
{
    if (argc != 3)
        return -1;
    
    FILE *f_1 = fopen(argv[1], "r");
    if (!f_1)
        return -1;
    node_t *head1 = read_file(f_1);
    fclose(f_1);
    
    FILE *f_2 = fopen(argv[2], "r");
    if (!f_2)
        return free_list(head1), -1;
    node_t *head2 = read_file(f_2);
    fclose(f_2);
    
    if (!head1 && !head2)
        return printf("Empty list\n"), 0;
    
	//print_list(head1);
	//puts("");
	//print_list(head2);
	//puts("");

    node_t *res = magic(head1, head2);
	print_list(res);
	free_list(res);
    
	puts("");

    return 0;
}

#ifndef __NON_LIB_H__
#define __NON_LIB_H__

#define AMOUNT_TO_DELETE 2
#include "err.h"

int get_array_size(int *size);
int get_pos(int *pos, const int size);
void err_handler(const int status);

#endif
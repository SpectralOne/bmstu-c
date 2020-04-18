#ifndef __MY_SNPRINTF_H__
#define __MY_SNPRINTF_H__

#include <stdarg.h>

#ifdef TRUE
#undef TRUE
#endif
#define TRUE 1

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

#define MAKE_CHAR(c) ((c) + '0')
#define ASCHI_JUMP(c) ((c) + 39)
#define UPPR_CHAR(c) ((c) - 32)
#define IS_LWR_CHAR(c) ((c) >= 'a' && (c) <= 'z') ? TRUE : FALSE
#define ABS(x) ((x) < 0) ? -(x) : (x)

#define OCT_BASE 8
#define DEC_BASE 10
#define HEX_BASE 16

typedef unsigned long size_t;

#ifdef __MY_FUNC_ONLY
int my_snprintf(char *s, size_t n, const char *format, ...);
#else

int my_snprintf(char *s, size_t n, const char *format, ...);

void determine_format(const char **format, char **string, int *string_len, const size_t size, va_list *argv);

void check_negative(char **string, int *string_len, long long int *number, const size_t size);
int get_number_len(const long long unsigned int number, const int base);

void process_number(char **string, int *string_len, long long unsigned int number, const int base, const int upcase_flag, const size_t size);
void process_string(char **string, int *string_len, char *buf, const size_t size);

size_t my_strlen(const char *string);
#endif /* __MY_FUNC_ONLY */

#endif /* __MY_SNPRINTF_H__ */
#include <string.h>
#include <stdio.h>
#include <limits.h>

#define __MY_FUNC_ONLY
#include "my_snprintf.h"

#define STR_SIZE 300

#define S_ARGS "", "c", "answer_42", ",gawh", "kk,kkmmk.k!@", "str%s"
#define S_ADDICTIONAL_ARGS "String", "StringString", "StringStringString"
#define CHAR_ARGS 'a', '\n', '\"', CHAR_MIN, CHAR_MAX

#define D_ARGS -1, -1, 0, -777, 555, INT_MIN, INT_MAX
#define X_ARGS 0xB, 0xFB, 0x1, 0x0, 00, 0x777, UINT_MAX
#define O_ARGS 01, 02, 03, 03, 0124, 0515, 051, 01231, 0121521, UINT_MAX, 0x0, 00

#define HD_ARGS 255, -42, 0, SHRT_MIN, SHRT_MAX, -222, 195
#define HX_ARGS 0, 0x0, 0x1F51F, 0x123, 0xABC, 0x777, 0x600, USHRT_MAX
#define HO_ARGS 0111, 0133, 04121, 01223, 0x0, 00, 01, 02, USHRT_MAX

#define LD_ARGS 1000, -42, 98, -1, 1, 0, 12345, 123458, LONG_MAX, LONG_MIN
#define LX_ARGS ULONG_MAX, 255, 0x100, 0x0 , 42, 0x0, 0xFFF, LLONG_MAX, (-LONG_MAX - 1L)
#define LO_ARGS 0123, 054325, 0321232, 01, 02, 0x0, 00, ULONG_MAX

#define LLD_ARGS 1000, -42, 98, -1, 1, 0, 12345, 12345678, LLONG_MAX, LLONG_MIN
#define LLX_ARGS ULLONG_MAX, 255, 0x100, 0 , 42, 0x0, 0xFFF, LLONG_MAX, (-LLONG_MAX - 1LL)
#define LLO_ARGS 0123, 054325, 0321232, 01, 02, 0x0, 00, ULLONG_MAX

char buf1[STR_SIZE], buf2[STR_SIZE];
int i, j, r1, r2, failed = 0, cnt = 0;
#define TEST(fmt, val)                                             \
do {                                                               \
	for (i = 0; fmt[i] != NULL; i++)                               \
		for (j = 0; j == 0 || val[j] != 0; j++)                    \
        {                                                          \
			r1 = snprintf(buf1, sizeof(buf1), fmt[i], val[j]);     \
			r2 = my_snprintf(buf2, sizeof(buf2), fmt[i], val[j]);  \
			if (strcmp(buf1, buf2) != 0 || r1 != r2)               \
            {                                                      \
				printf("Results don't match, "                     \
				    "format string: %s\n"                          \
				    "\tsystem snprintf: [%s] (%d)\n"               \
				    "\t    my_snprintf: [%s] (%d)\n",              \
				    fmt[i], buf1, r1, buf2, r2);                   \
				failed++;                                          \
			}                                                      \
			cnt++;                                                 \
		}                                                          \
} while (0)

/**
 * @brief Сравнение работы самописной функции с функцией из стандартной библиотеки
 * 
 * @param my_return - my_snprintf возврат
 * @param std_return - snprintf возврат
 * @param my_res - my_snprintf результат
 * @param std_res - msnprintf результат
 * @return 1, если совпало, 0 иначе
 */
int result_check(const int my_return, const int std_return, const char *my_res, const char *std_res)
{
    if (!strcmp(my_res, std_res) && my_return == std_return)
        return printf("OK\n"), 1;

    return printf("FAILED (returned|expected) (%d)|(%d): [%s]|[%s]\n", my_return, std_return, my_res, std_res), 0;
}

void test_my_snprintf_args_overflow(void)
{
    printf("\n--- %s ---\n", __func__);
    int err_count = 0;

    char my_res[STR_SIZE] = { 0 }, std_res[STR_SIZE] = { 0 };

    printf("Args overflow: ");
    {
        char format[] = "Test: %s, %s";

        int my_return = my_snprintf(my_res, STR_SIZE, format, S_ADDICTIONAL_ARGS);
        int std_return = snprintf(std_res, STR_SIZE, format, S_ADDICTIONAL_ARGS);

        if (!result_check(my_return, std_return, my_res, std_res))
            err_count++;
    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_my_snprintf_utility(void)
{
    printf("\n--- %s ---\n", __func__);
    int err_count = 0;

    printf("Empty format string: ");
    {
        char format[] = "";

        char my_res[STR_SIZE] = { 0 }, std_res[STR_SIZE] = { 0 };

        int my_return = my_snprintf(my_res, STR_SIZE, format);
        int std_return = snprintf(std_res, STR_SIZE, format);

        if (!result_check(my_return, std_return, my_res, std_res))
            err_count++;
    }

    printf("%% test: ");
    {
        char format[] = "%%";

        char my_res[STR_SIZE] = { 0 }, std_res[STR_SIZE] = { 0 };

        int my_return = my_snprintf(my_res, STR_SIZE, format);
        int std_return = snprintf(std_res, STR_SIZE, format);

        if (!result_check(my_return, std_return, my_res, std_res))
            err_count++;
    }

    printf("Normal test: ");
    {
        char format[] = "Test";

        char my_res[STR_SIZE] = { 0 }, std_res[STR_SIZE] = { 0 };

        int my_return = my_snprintf(my_res, STR_SIZE, format);
        int std_return = snprintf(std_res, STR_SIZE, format);

        if (!result_check(my_return, std_return, my_res, std_res))
            err_count++;
    }

    printf("Format string is larger that string size: ");
    {
        char format[] = "12345";

        char my_res[3] = { 0 }, std_res[3] = { 0 };

        int my_return = my_snprintf(my_res, 3, format);
        int std_return = snprintf(std_res, 3, format);

        if (!result_check(my_return, std_return, my_res, std_res))
            err_count++;
    }

    printf("String overflow: ");
    {
        char format[] = "%s";

        char my_res[3] = { 0 }, std_res[3] = { 0 };

        int my_return = my_snprintf(my_res, 3, format, "Overflow");
        int std_return = snprintf(std_res, 3, format, "Overflow");

        if (!result_check(my_return, std_return, my_res, std_res))
            err_count++;
    }

    printf("Number overflow: ");
    {
        char format[] = "%llx";

        char my_res[3] = { 0 }, std_res[3] = { 0 };

        int my_return = my_snprintf(my_res, 3, format, ULLONG_MAX);
        int std_return = snprintf(std_res, 3, format, ULLONG_MAX);

        if (!result_check(my_return, std_return, my_res, std_res))
            err_count++;
    }
    
    printf("Format overflow: ");
    {
        char format[] = "%s test %s %llx";

        char my_res[13] = { 0 }, std_res[13] = { 0 };

        int my_return = my_snprintf(my_res, 13, format, "String", "String", LLONG_MAX);
        int std_return = snprintf(std_res, 13, format, "String", "String", LLONG_MAX);

        if (!result_check(my_return, std_return, my_res, std_res))
            err_count++;
    }

    printf("Cafedral all #4: ");
    {
        char format[] = "%s test %s %llx";

        char my_res[13] = { 0 }, std_res[13] = { 0 };

        int my_return = my_snprintf(my_res, 0, format, "String", "String", LLONG_MAX);
        int std_return = snprintf(std_res, 0, format, "String", "String", LLONG_MAX);

        if (!result_check(my_return, std_return, my_res, std_res))
            err_count++;
    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void null_string_size_test(void)
{
    printf("\n--- %s ---\n", __func__);
    int err_count = 0;

    int my_return = my_snprintf(NULL, 0, "qwe");
    int std_return = snprintf(NULL, 0, "qwe");

    printf("NULL string and zero size: ");
    if (my_return == std_return)
        puts("OK");
    else
    {
        printf("FAILED (returned|expected) %d|%d: \n", my_return, std_return);
        err_count++;
    }
    
    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

int main(void)
{   
    const char *s_fmt[] = { "Test [%s]", NULL }, *s_val[] = { S_ARGS, NULL };
    const char *c_fmt[] = { "Test [%c]", NULL }; const char c_val[] = { CHAR_ARGS  };

    const char *d_fmt[] = { "Test [%d]", NULL }; const int d_val[] = { D_ARGS };
    const char *i_fmt[] = { "Test [%i]", NULL }; const int i_val[] = { D_ARGS };
    const char *x_fmt[] = { "Test [%x]", NULL }; const unsigned int x_val[] = { X_ARGS };
    const char *x_b_fmt[] = { "Test [%X]", NULL }; const unsigned int x_b_val[] = { X_ARGS };
    const char *o_fmt[] = { "Test [%o]", NULL }; const unsigned int o_val[] = { O_ARGS };

    const char *hd_fmt[] = { "Test [%hd]", NULL }; const int hd_val[] = { HD_ARGS };
    const char *hi_fmt[] = { "Test [%hi]", NULL }; const int hi_val[] = { HD_ARGS };
    const char *hx_fmt[] = { "Test [%hx]", NULL }; const unsigned int hx_val[] = { HX_ARGS };
    const char *hx_b_fmt[] = { "Test [%hX]", NULL }; const unsigned int hx_b_val[] = { HX_ARGS };
    const char *ho_fmt[] = { "Test [%ho]", NULL }; const unsigned int ho_val[] = { HO_ARGS };

    const char *ld_fmt[] = { "Test [%ld]", NULL }; const long int ld_val[] = { LD_ARGS };
    const char *li_fmt[] = { "Test [%li]", NULL }; const long int li_val[] = { LD_ARGS };
    const char *lx_fmt[] = { "Test [%lx]", NULL }; const unsigned long int lx_val[] = { LX_ARGS };
    const char *lx_b_fmt[] = { "Test [%lX]", NULL }; const unsigned long int lx_b_val[] = { LX_ARGS };
    const char *lo_fmt[] = { "Test [%lo]", NULL }; const unsigned long int lo_val[] = { LO_ARGS };

    const char *lld_fmt[] = { "Test [%lld]", NULL }; const long long int lld_val[] = { LLD_ARGS };
    const char *lli_fmt[] = { "Test [%lli]", NULL }; const long long int lli_val[] = { LLD_ARGS };
    const char *llx_fmt[] = { "Test [%llx]", NULL }; const unsigned long long int llx_val[] = { LLX_ARGS };
    const char *llx_b_fmt[] = { "Test [%llX]", NULL }; const unsigned long long int llx_b_val[] = { LLX_ARGS };
    const char *llo_fmt[] = { "Test [%llo]", NULL }; const unsigned long long int llo_val[] = { LLO_ARGS };

    printf("Functional tests: ");

    TEST(s_fmt, s_val);
    TEST(c_fmt, c_val);

    TEST(d_fmt, d_val);
    TEST(i_fmt, i_val);
    TEST(x_fmt, x_val);
    TEST(x_b_fmt, x_b_val);
    TEST(o_fmt, o_val);

    TEST(hd_fmt, hd_val);
    TEST(hi_fmt, hi_val);
    TEST(hx_fmt, hx_val);
    TEST(hx_b_fmt, hx_b_val);
    TEST(ho_fmt, ho_val);

    TEST(ld_fmt, ld_val);
    TEST(li_fmt, li_val);
    TEST(lx_fmt, lx_val);
    TEST(lx_b_fmt, lx_b_val);
    TEST(lo_fmt, lo_val);

    TEST(lld_fmt, lld_val);
    TEST(lli_fmt, lli_val);
    TEST(llx_fmt, llx_val);
    TEST(llx_b_fmt, llx_b_val);
    TEST(llo_fmt, llo_val);

    printf("%d of %d\n", cnt - failed, cnt);

    puts("\n--- Special tests ---");

    test_my_snprintf_args_overflow();
    test_my_snprintf_utility();
    null_string_size_test();

    return 0;
}
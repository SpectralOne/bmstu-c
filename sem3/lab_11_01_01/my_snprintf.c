#include "my_snprintf.h"

/**
 * Релизация snprintf
 * Спецификаторы: все (в рамках учебного задания)
 * @param string - указатель на начало строки
 * @param size - максимальная длина строки
 * @param format - строка формата
 * @param ... - аргументы строки формата
 * @return длину строки или OVERFLOW в случае переполнения
 */
int my_snprintf(char *string, size_t size, const char *format, ...)
{
    va_list argv;
    va_start(argv, format);

    int string_len = 0;
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
                case ('%'):
                    if (string && string_len < (size - 1) && size)
                        *string++ = '%';
                    string_len++;
                    break;
                case ('c'):
                    if (string && string_len < (size - 1) && size)
                        *string++ = va_arg(argv, int);
                    string_len++;
                    break;
                case ('s'):
                    if (string && string_len < (size - 1) && size)
                        process_string(&string, &string_len, va_arg(argv, char *), size);
                    else
                        string_len += my_strlen(va_arg(argv, char *));
                    break;
                case ('h'):
                    format++;
                    determine_format(&format, &string, &string_len, size, &argv);
                    break;
                case ('l'):
                    format++;
                    if (*format == 'l')
                        format++, determine_format(&format, &string, &string_len, size, &argv);
                    else
                        determine_format(&format, &string, &string_len, size, &argv);
                    break;
                default:
                    determine_format(&format, &string, &string_len, size, &argv);
                    break;
            }
        }
        else
        {
            if (string && string_len < (size - 1) && size)
                *string++ = *format;
            string_len++;
        }
        format++;
    }

    if (string)
        *string = 0;

    va_end(argv);

    return string_len;
}

/**
 * @brief Определение формата
 * 
 * @param format - указатель на указатель на текущую позицию строки-формата
 * @param string - указатель на указатель на текущую позиция строки-результата
 * @param string_len - указатель на длину строки
 * @param size - максимально допустимый размер результата строки 
 * @param argv - указатель на переменную с аргументами
 */
void determine_format(const char **format, char **string, int *string_len, const size_t size, va_list *argv)
{
    long long int number;

    switch (**format)
    {
        case ('d'):
            if ((*format)[-1] == 'l')
                number = va_arg(*argv, long long int);
            else
                number = (long long int) va_arg(*argv, int);
            
            if (number < 0)
            {
                number = ABS(number);
                if (*string && *string_len < (size - 1) && size)
                {
                    **string = '-';
                    *string += 1;
                }
                *string_len += 1;
            }

            process_number(string, string_len, (long long int) number, DEC_BASE, FALSE, size);
            break;
        case ('x'):
            process_number(string, string_len, va_arg(*argv, long long int), HEX_BASE, FALSE, size);
            break;
        case ('X'):
            process_number(string, string_len, va_arg(*argv, long long int), HEX_BASE, TRUE, size);
            break;
        case ('o'):
            process_number(string, string_len, va_arg(*argv, long long int), OCT_BASE, TRUE, size);
            break;
        default:
            if ((*format)[-1] == 'l')
                number = va_arg(*argv, long long int);
            else
                number = (long long int) va_arg(*argv, int);
            
            if (number < 0)
            {
                number = ABS(number);
                if (*string && *string_len < (size - 1) && size)
                {
                    **string = '-';
                    *string += 1;
                }
                *string_len += 1;
            }

            process_number(string, string_len, (long long int) number, DEC_BASE, FALSE, size);
            break;
    }
}

/**
 * @brief Проверка числа на отрицательность 
 * Если отрицательное - превратится в положительное, а в строку запишется минус
 * @param string - указатель на строку-результат
 * @param string_len - указатель на длину строки
 * @param number - указатель на число
 * @param size - максимально допустимый размер результата строки
 */
void check_negative(char **string, int *string_len, long long int *number, const size_t size)
{
    if (*number < 0)
    {
        *number = ABS(*number);
        if (*string && *string_len < (size - 1) && size)
        {
            **string = '-';
            *string += 1;
        }

        *string_len += 1;
    }
}

/**
 * @brief Определить количество символов числа (длину)
 * 
 * @param number - число
 * @param base - основание (система счисления) числа
 * @return количество символов (длина числа) 
 */
int get_number_len(const long long unsigned int number, const int base)
{
    int len = 0;
    long long unsigned int tmp = number;
    do 
    {
        len++;
        tmp /= base;
    } while (tmp);
    
    return len;
}

/**
 * @brief Вписать число в строку
 * 
 * @param string - указатель на строку (текущая позиция)
 * @param string_len - указатель на длину строки
 * @param number - число
 * @param base_chars - символы, соответствующие системе счисления 
 * @param size - максимально допустимый размер результата строки
 */
void process_number(char **string, int *string_len, long long unsigned int number, const int base, const int upcase_flag, const size_t size)
{
    int number_len = 0;

    //check_negative(string, string_len, &number, size);
    
    number_len = get_number_len(number, base);

    char str_num[number_len + 1];
    str_num[number_len--] = 0;

    do
    {
        str_num[number_len] = MAKE_CHAR(number % base);
        
        if (str_num[number_len] > '9')
            str_num[number_len] = ASCHI_JUMP(str_num[number_len]);
    
        if (upcase_flag && base == HEX_BASE && IS_LWR_CHAR(str_num[number_len]))
            str_num[number_len] = UPPR_CHAR(str_num[number_len]);

        number /= base;
        number_len--;
    } while (number);

    process_string(string, string_len, str_num, size);
}

/**
 * @brief Вписать строку в строку
 * 
 * @param string - указатель на указатель на строку-результат
 * @param string_len - указатель на длину строки
 * @param buf - строка, которую следует вписать в строку-результат
 * @param size - максимально допустимый размер результата строки
 */
void process_string(char **string, int *string_len, char *buf, const size_t size)
{   
    if (*string && size)
    {
        while ((*string_len < size - 1) && (*buf != 0))
        {
            **string = *buf;
            *string += 1;
            *string_len += 1;
            buf++;
        }
    }
    *string_len += my_strlen(buf);
}

/**
 * @brief Функция определения длины строки 
 * 
 * @param string - строка 
 * @return - длинa
 */
size_t my_strlen(const char *string)
{
    size_t i = 0;
    while (string[i])
        i++;

    return i;
}

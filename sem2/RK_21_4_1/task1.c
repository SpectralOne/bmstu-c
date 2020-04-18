#include<stdio.h>
#define TRUE 1
#define OK 0
#define INP_ERR -1
#define EMPTY_NUM -2
#define N 10

int form_number(int number, int dig_to_del)
{
    int tmp, result = 0, ten = 1;
    for(; number != 0; number /= 10)
    {
        tmp = number % 10;

        if (tmp != dig_to_del)
        {
            result = tmp * ten + result;
            ten *= 10;
        }
    }
    return result;
}

int main(void)
{
    int number, a, b, result, status = OK;

    printf("Enter number and two digits to remove: ");
    if (scanf("%d%d%d", &number, &a, &b) != 3)
    {
        printf("Input error!");
        status = INP_ERR;
    }
    else
    {
        result = form_number(form_number(number, a), b);
        //result = form_number(result, b);

        if (!result)
        {
            printf("Number has been deleted!");
            status = EMPTY_NUM;
        }
        else
        {
            printf("Number = %d", result);
        }
    }
    return status;
}

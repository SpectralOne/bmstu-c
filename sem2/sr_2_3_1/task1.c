#include <stdio.h>

void swap(int *num1, int *num2)
{
    int tmp;
    tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

int main(void)
{
    int a, b;

    printf("Enter two integers: ");
    scanf("%d%d", &a, &b);
    swap(&a, &b);
    printf("Swaped! %d %d", a, b);

    return 0;
}

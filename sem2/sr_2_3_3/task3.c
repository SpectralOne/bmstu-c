#include <stdio.h>
#include <math.h>

void process(int number, int digit, int *count)
{
    //int i = 0;

    while (abs(number) > 0)
    {
      if (abs(number % 10) == digit)
          *count += 1;
      number /= 10;
    }
}

int main(void)
{
    int number, count = 0, digit;

    printf("Enter number and a digit: ");
    scanf("%d %d", &number, &digit);

    process(number, digit, &count);
    printf("\nFound specified digit %d time(s)", count);

    return 0;
}

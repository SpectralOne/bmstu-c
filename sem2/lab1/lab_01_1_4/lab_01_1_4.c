#include <stdio.h>
#define APF 4 // Количество квартир на этаж (Appartments Per Floor)
#define APP 36 // Количество квартир на подъезд (Appartments Per Porch)

int main(void)
{
    int n, et, pd;

    printf("Enter appartment number:\n");
    scanf("%d", &n);

    pd = ((n - 1) / APP) + 1;
    et = (((n - 1) % APP) / APF) + 1;

    printf("Porch Floor: %d %d", pd, et);

    return 0;
}

#include <stdio.h>
#include <math.h>
#define PI 3.14159265

int main(void)
{
    float a, b, alpha, h, s, c, val;

    printf("input a, b, alpha:\n");
    scanf("%f%f%f", &a, &b, &alpha);

    val = PI / 180;
    c = fabs((a - b)) / 2;

    h = c * (tan(alpha * val));
    s = ((a + b) / 2) * h;

    printf("S = %.5g", s);

    return 0;
}

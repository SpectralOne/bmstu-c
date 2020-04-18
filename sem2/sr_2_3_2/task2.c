#include <stdio.h>
#define PI 3.14159

void process(float r, float *l, float *s)
{
    *s = PI * r *r;
    *l = 2 * PI * r;
}

int main(void)
{
    float r, l, s;

    printf("Enter radius: ");
    scanf("%f", &r);

    process(r, &l, &s);
    printf("\nL = %f, S = %f", l, s);

    return 0;
}

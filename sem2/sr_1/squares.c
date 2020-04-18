#include <stdio.h>
#define PI 3.14

float rect_square(float a, float b)
{
    return a * b;
}

float circle_square(float r)
{
    return PI * r * r;
}

int main(void)
{
    float s, sr, sc, a, b, r;

    printf("Input a and b and r: ");
    scanf("%f%f%f", &a, &b, &r);

    sr = rect_square(a, b);
    sc = circle_square(r);
    s = sr + sc;
    printf("\nSquare of rectangle is %8.3f\nSquare of circle is %8.3f\nSum of squares is %8.3f", sr, sc, s);

    return 0;
}

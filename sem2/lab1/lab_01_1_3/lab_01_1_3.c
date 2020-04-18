#include <stdio.h>

int main(void)
{
    float v1, v2, t1, t2, q, v3;

    printf("Enter v1, t1, v2, t2:\n");
    scanf("%f%f%f%f", &v1, &t1, &v2, &t2);

    q = (-v2 * t2 - v1 * t1) / (-v1 - v2);
    v3 = v1 + v2;
    
    printf("v t : %.5g %.5g", v3, q);

    return 0;
}


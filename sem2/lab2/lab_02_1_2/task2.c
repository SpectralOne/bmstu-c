#include <stdio.h>
#include <math.h>
#define OK 0
#define INP_ERR 1
#define NOT_EXIST 2
#define TRUE 1
#define FALSE 0
#define PRECISION 0.00001

/*
 Функция вычисляет площадь треугольника
 На вход получает парные координаты вершин треугольника (X, Y)
 Тип данных: float
 Возвращает площадь треугольника
*/

float square_of_triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float ab, ac, bc, p, s;

    ab = sqrt(fabs((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1)));
    ac = sqrt(fabs((y3 - y1) * (y3 - y1) + (x3 - x1) * (x3 - x1)));
    bc = sqrt(fabs((y2 - y3) * (y2 - y3) + (x3 - x2) * (x3 - x2)));
    p = (ab + ac + bc) / 2;
    s = sqrt(p * (p - ab) * (p - ac) * (p - bc));

    return s;
}

/*
 Функция сравнивает два числа между собой
 Если одно число равно другому - возвращает True
 Если числа отличны друг от друга - False
 Тип входящих данных: float
 Тип вовзращаемых данных: int
*/

int f_equal(float num1, float num2)
{
    if (fabs(num1 - num2) < PRECISION)
        return TRUE;
    else
        return FALSE;
}

/*
 Функция проверяет возможность существования треугольника
 Принимает на вход парные координаты вершин треугольника (X, Y)
 Тип данных: float
 Возвращает 'OK' если треугольник существует и 'NOT_EXIST' если не существует
*/


int input_check(float x1, float y1, float x2, float y2, float x3, float y3)
{
    if ((f_equal(x1, x2) && f_equal(y1, y2)) ||
        (f_equal(x1, x3) && f_equal(y1, y3)) ||
        (f_equal(x2, x3) && f_equal(y2, y3)) ||
        (f_equal(x1, y1) && f_equal(x2, y2) && f_equal(x3, y3)) ||
        (f_equal(((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)), 0)))
        return NOT_EXIST;
    else
        return OK;
}

int main(void)
{
    float x1, y1, x2, y2, x3, y3;
    int status = 0;

    printf("Enter coords: ");

    if (scanf("%f%f%f%f%f%f", &x1, &y1, &x2, &y2, &x3, &y3) == 6)
    {
        if (input_check(x1, y1, x2, y2, x3, y3))
        {
            status = NOT_EXIST;
            printf("Triangle doesn't exist!");
        }
        else
        {
            status = OK;
            printf("s = %.5f", square_of_triangle(x1, y1, x2, y2, x3, y3));
        }
    }
    else
    {
        status = INP_ERR;
        printf("I/O error!");
    }

    return status;
}

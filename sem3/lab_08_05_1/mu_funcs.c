#include "mu_funcs.h"
#include "array_utility_funcs.h"
#include <math.h>
#include <assert.h>

/*
 * Функция расчёта mu1
 * Расчитывает среднее геометрическое модулей
 * Принимает на вход указатели на массив и его конец
 * Тип данных: double
 * Вернёт: результат вычисления
 --- Допущения ---
 * Массив существует
 * Массив имеет положительный размер
 --- Параметры ---
   [in]  *array : указатель на начало массива
   [in]  *end_array : указатель на конец массива
 [return] mu1 : значение mu1
*/
double compute_mu1(const double *array, const double *end_array)
{
    // массив существует и имеет положительный размер
    assert(array);
    assert(end_array);
    assert(array < end_array);

    double temp = 1.;

    for (const double *pcur = array; pcur < end_array; pcur++)
        temp *= fabs(*pcur);

    return pow(temp, 1. / (end_array - array));
}

/*
 * Функция расчёта mu2
 * Расчитывает отношение произведения минимального и максимального элементов к
   их сумме с единицой
 * Принимает на вход указатель на массив и указатель на размер массива
 * Тип данных: double
 * Вернёт: результат вычисления
 --- Допущения ---
 * Массив существует
 * Массив имеет положительный размер
 --- Параметры ---
   [in]  *array : указатель на начало массива
   [in]  *end_array : указатель на конец массива
 [return] mu1 : значение mu2
*/
double compute_mu2(const double *array, const double *end_array)
{
    // массив существует и имеет положительный размер
    assert(array);
    assert(end_array);
    assert(array < end_array);

    double min, max;

    min = find_min(array, end_array);
    max = find_max(array, end_array);

    return (min * max) / (1 + fabs(max) + fabs(min));
}

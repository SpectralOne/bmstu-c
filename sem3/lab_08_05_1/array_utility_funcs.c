#include "array_utility_funcs.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // memmove

/*
 * Функция поиска минимального элемента
 * Принимает на вход указатели на начало массива и его конец
 * Тип данных: double
 * Возвращает значение минимального элемента
 --- Допущения ---
 * Массив существует
 * Массив имеет положительный размер
 --- Параметры ---
   [in]  *array : указатель на начало массива
   [in]  *end_array : указатель на конец массива
 [return] min : минимальный элемент массива
*/
double find_min(const double *array, const double *end_array)
{
    // массив существует и имеет положительный размер
    assert(array);
    assert(end_array);
    assert(array < end_array);

    double min = *(array);

    for (const double *pcur = (array + 1); pcur < end_array; pcur++)
        if (*pcur < min)
            min = *pcur;
    return min;
}

/*
 * Функция поиска максимального элемента
 * Принимает на вход указатели на начало массива и его конец
 * Тип данных: double
 * Возвращает значение максимального элемента
 --- Допущения ---
 * Массив существует
 * Массив имеет положительный размер
 --- Параметры ---
   [in]  *array : указатель на начало массива
   [in]  *end_array : указатель на конец массива
 [return] max : максимальный элемент массива
*/
double find_max(const double *array, const double *end_array)
{
    // массив существует и имеет положительный размер
    assert(array);
    assert(end_array);
    assert(array < end_array);

    double max = *(array);

    for (const double *pcur = (array + 1); pcur < end_array; pcur++)
        if (*pcur > max)
            max = *pcur;
    return max;
}

/*
 * Функция сдвига элемента, находящегося на переданной позиции, в конец массива
 * Принимает на вход указатели на начало массива и его конец
 * Тип данных: double
 * Функция ничего не возвращает
 --- Допущения ---
 * Массив существует
 * Массив имеет положительный размер
 --- Параметры ---
   [in]  *array : указатель на начало массива
   [in]  *end_array : указатель на конец массива
*/
void move_to_end(double *const array, double *const end_array)
{
    // массив существует и имеет положительный размер
    assert(array);
    assert(end_array);
    assert(array < end_array);

    // double *start = array;
    //double temp = *array;

    memmove(array, array + 1, (end_array - array - 1) * sizeof(double));

    /*
    for (; start < (end_array - 1); start++)
        *start = *(start + 1);

    *start = temp;
    */
}

/* --- Old function ---

void move_to_end(double *const array, double *const end_array)
{
    // массив существует и имеет положительный размер
    assert(array);
    assert(end_array);
    assert(array < end_array);

    double temp;
    for (double *start = array; start < (end_array - 1); start++)
    {
        temp = *start;
        *start = *(start + 1);
        *(start + 1) = temp;
    }
}

*/

/*
 * Функция находит позицию элемента, имеющего минимальную разницу с mu1
 * Принимает на вход указатели на начало массива, его конец, указатель на указатель позиции и переменную mu1
 * Тип данных: double
 * Функция ничего не возвращает
 --- Допущения ---
 * Массив существует
 * Массив имеет положительный размер
 --- Параметры ---
   [in]  *array : указатель на начало массива
   [in]  *end_array : указатель на конец массива
   [in] **pos : указатель на указатель позиции
   [in]   mu1 : значение mu1
*/
void find_element(double *array, double *end_array, double **pos, const double mu1)
{
    // массив существует и имеет положительный размер
    assert(array);
    assert(end_array);
    assert(array < end_array);

    double diff = fabs(fabs(*array) - mu1);
    int flag = 1;

    *pos = array;
    for (double *pcur = array; (pcur < end_array) && flag; pcur++)
    {
        if (fabs(fabs(*pcur) - mu1) < diff)
        {
            *pos = pcur;
            diff = fabs(fabs(*pcur) - mu1);

            if (f_equal(0.0, diff))
                flag = 0;
        }
    }
}

/*
 * Функция удаляет два элемента, имеющих минимальную разницу с mu1
 * Принимает на вход указатели на начало массива, его конец и переменную mu1
 * Тип данных: double
 * Функция возвращает код ошибки
 * Побочные эффекты: изменение указателей на начало и конец массива, изменение размера области
 --- Допущения ---
 * Массив существует
 * Массив имеет положительный размер
 --- Параметры ---
   [in] **array : указатель на указатель начала массива
   [in] **end_array : указатель на указатель конца массива
   [in]   mu1 : значение mu1
 [return] : код ошибки
*/
int normalize_array(double **array, double **end_array, const double mu1)
{
    // массив существует и имеет положительный размер
    assert(*array);
    assert(*end_array);
    assert(*array < *end_array);

    // количество удаляемых элементов не превышает количества элементов массива
    assert((*end_array - *array) > AMOUNT_TO_DELETE);

    int status = OK;
    double *pos = NULL;

    for (int i = 0; i < AMOUNT_TO_DELETE && status == OK; i++)
    {
        find_element(*array, *end_array - i, &pos, mu1);
        status = delete_element(array, end_array, pos);

        // memmove заменяет собой полностью функцию move_to_end
        // memmove(pos, pos + 1, (end_array - pos - 1) * sizeof(double));

        // move_to_end(pos, end_array);
    }
    return status;
}

/*
 * Функция удаляет элемент, стоящий на переданной позиции
 * Принимает на вход указатели на указатель на начало массива, его конец и указатель на позицию
 * Тип данных: double
 * Функция возвращает код ошибки
 * Побочные эффекты: изменение указателей на начало и конец массива, изменение размера области
 --- Допущения ---
 * Ряд допущений гарантируется в функции, вызывающей данную: normalize_array
 --- Параметры ---
   [in] **array : указатель на указатель начала массива
   [in] **end_array : указатель на указатель конца массива
   [in]  *pos : позиция элемента
 [return] : код ошибки
*/
int delete_element(double **array, double **end_array, double *pos)
{
    int status;

    memmove(pos, pos + 1, (*end_array - pos - 1) * sizeof(double));
    status = reallocate_array(array, end_array, *end_array - *array - 1);

    return status;
}

/*
 * Функция перераспределения или выделения области памяти для хранения массива
 * Принимает на вход указатели на указатели начала массива, его конца,
   а также переменные переменную, задающую размер нужной области
 * Типы входящих данных: double, int
 * Типы возвращаемых данных: int
 * Тип выделяемой памяти: double
 --- Описание ---
 ** Если новый размер совпадает со старым - функция возврвщает ОК, ничего не меняется
 ** Если не удалось выделить/перевыделить память - возвращается код ошибки
 ** В случае успеха переназначает указатели на указатели областей памяти, содержащих массив, зануляет старые
 --- -- -- -- ---
 * Возвращает код ошибки
 * Возможный побочный эффект: изменение указателей на область памяти
 --- Допущения ---
 * Верно переданы указатели на начало и конец массива
 * Конец массива не может быть расположен раньше начала
 --- Параметры ---
   [in] **array : указатель на указатель начала массива
   [in] **end_array : указатель на указатель конца массива
   [in]   new_size : переменная нового размера
 [return] : код ошибки
*/
int reallocate_array(double **array, double **end_array, int new_size)
{
    if ((*end_array - *array) == new_size)
        return OK;

    double *new_array = (double*) realloc(*array, new_size * sizeof(double));

    if (new_array)
    {
        *array = new_array;
        *end_array = new_array + new_size;

        new_array = NULL;

        return OK;
    }

    return MEM_ALLOC_ERR;
}

/*
 * Функция вставки переданного элемента на заданную позицию
 * Принимает на вход указатели на начало массива и его конец, а также переменные позиции и элемента
 * Тип данных: double
 * Функция ничего не возвращает
 --- Допущения ---
 * Массив существует
 * Массив имеет положительный размер
 --- Параметры ---
   [in]  *array : указатель на начало массива
   [in]  *end_array : указатель на конец массива
   [in]   pos : позиция для вставки элемента
   [in]   item : элемент, который будет вставлен
*/
void insert_to_pos(double *array, double *end_array, const int pos, const double item)
{
    if ((array + pos) == (end_array - 1))
        *(array + pos) = item;
    else
    {
        memmove(array + pos + 1, array + pos, (end_array - (array + pos) - 1) * sizeof(double));
        *(array + pos) = item;
        /*
        double *pcur = NULL;
        for (pcur = (end_array - 1); pcur > (array + pos); pcur--)
            *pcur = *(pcur - 1);
        *pcur = item;
        */
    }
}

/*
 * Функция сравнивает два числа между собой
 --- Описание ---
 ** Если одно число равно другому - возвращает True
 ** Если числа отличны друг от друга - False
 --- -- -- -- ---
 * Тип входящих данных: float
 * Тип вовзращаемых данных: int
 --- Допущения ---
 * Не требуются
 --- Параметры ---
   [in]   num1 : первое число
   [in]   num2 : второе число
 [return] : TRUE || FALSE
*/
int f_equal(double num1, double num2)
{
    if (fabs(num1 - num2) < PRECISION)
        return TRUE;
    return FALSE;
}

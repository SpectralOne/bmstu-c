#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "custom_defines.h"
#include "memmory_funcs.h"
#include "utility_funcs.h"
#include "io_funcs.h"

/*
 * Функция сравнения элементов двух матриц
 * Принимает на вход указатели на структуры
 * Тип данных: matrix_s
 * Возвращает 1 если две матрицы равны, иначе 0
--- Допущения ---
 * Передающиеся указатели валидны
 * Указатели под указателями matrix_s валидны и не содержат неинициализированную память
 * Количество строк и столбцов переданных матриц совпадают
 --- Параметры ---
   [in]  *matrix_a : указатель на первую структуру
   [in]  *matrix_b : указатель на вторую структуру
 [return] : признак равенства (0 или 1)
*/
int matrix_cmp(const matrix_s *matrix_a, const matrix_s *matrix_b)
{
    assert(matrix_a && matrix_b);
    
    if ((matrix_a->cur_rows != matrix_b->cur_rows) && (matrix_a->cur_columns == matrix_b->cur_columns))
        return 0;
    else
    {
        for (size_t row = 0; row < matrix_a->cur_rows; row++)
            for (size_t column = 0; column < matrix_b->cur_columns; column++)
                if (matrix_a->data[row][column] != matrix_b->data[row][column])
                    return 0;
    }

    return 1;
}

void test_find_max_element_pos(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Normal test (column index test): ");
    {
        matrix_s *test_matrix = NULL;
        int pos_row, pos_column, status = OK;
        test_matrix = allocate_matrix(2, 3, &status);

        assert(test_matrix && status == OK);
        test_matrix->data[0][0] = 2, test_matrix->data[0][1] = 9, test_matrix->data[0][2] = 7;
        test_matrix->data[1][0] = 9, test_matrix->data[1][1] = 1, test_matrix->data[1][2] = 6;

        /*
          2 9 7
          9 1 6
        */
        find_max_element_pos(test_matrix, &pos_row, &pos_column);
        if (pos_row == 0 && pos_column == 1)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
    }
    
    printf("Two following (column index test): ");
    {
        matrix_s *test_matrix = NULL;
        int pos_row, pos_column, status = OK;
        test_matrix = allocate_matrix(2, 3, &status);

        assert(test_matrix && status == OK);
        test_matrix->data[0][0] = 2, test_matrix->data[0][1] = 9, test_matrix->data[0][2] = 9;
        test_matrix->data[1][0] = 9, test_matrix->data[1][1] = 0, test_matrix->data[1][2] = 6;

        /*
          2 9 9
          9 0 1
        */
        find_max_element_pos(test_matrix, &pos_row, &pos_column);
        if (pos_row == 0 && pos_column == 1)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
    }

    printf("Normal test (row index test): ");
    {
        matrix_s *test_matrix = NULL;
        int pos_row, pos_column, status = OK;
        test_matrix = allocate_matrix(3, 2, &status);

        assert(test_matrix && status == OK);
        test_matrix->data[0][0] = 2, test_matrix->data[0][1] = 9;
        test_matrix->data[1][0] = 2, test_matrix->data[1][1] = 1;
        test_matrix->data[2][0] = 9, test_matrix->data[2][1] = 1;

        /*
          2 9
          2 1
          9 1
        */
        find_max_element_pos(test_matrix, &pos_row, &pos_column);
        if (pos_row == 0 && pos_column == 1)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
    }

    printf("Two following (row index test): ");
    {
        matrix_s *test_matrix = NULL;
        int pos_row, pos_column, status = OK;
        test_matrix = allocate_matrix(3, 2, &status);

        assert(test_matrix && status == OK);
        test_matrix->data[0][0] = 4, test_matrix->data[0][1] = 7;
        test_matrix->data[1][0] = 7, test_matrix->data[1][1] = 1;
        test_matrix->data[2][0] = 5, test_matrix->data[2][1] = 3;

        /*
          4 7
          7 1
          5 3
        */
        find_max_element_pos(test_matrix, &pos_row, &pos_column);
        if (pos_row == 0 && pos_column == 1)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
    }
    
    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_round_matrix(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Delete one column test: ");
    {
        matrix_s *test_matrix = NULL, *result_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(2, 3, &status);
        result_matrix = allocate_matrix(2, 2, &status);
        
        assert(test_matrix && result_matrix && status == OK);
        test_matrix->data[0][0] = 2, test_matrix->data[0][1] = 9, test_matrix->data[0][2] = 7;
        test_matrix->data[1][0] = 9, test_matrix->data[1][1] = 1, test_matrix->data[1][2] = 6;
        result_matrix->data[0][0] = 2, result_matrix->data[0][1] = 7;
        result_matrix->data[1][0] = 9, result_matrix->data[1][1] = 6;
        
        /*
          2 9 7 ---> 2 7
          9 1 6 ---> 9 6
        */
        round_matrix(test_matrix);
        if (matrix_cmp(test_matrix, result_matrix))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(result_matrix);
    }
    
    printf("Delete one row test: ");
    {
        matrix_s *test_matrix = NULL, *result_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(3, 2, &status);
        result_matrix = allocate_matrix(2, 2, &status);
        
        assert(test_matrix && result_matrix && status == OK);
        test_matrix->data[0][0] = 2, test_matrix->data[0][1] = 9;
        test_matrix->data[1][0] = 7, test_matrix->data[1][1] = 1;
        test_matrix->data[2][0] = 9, test_matrix->data[2][1] = 2;
        result_matrix->data[0][0] = 7, result_matrix->data[0][1] = 1;
        result_matrix->data[1][0] = 9, result_matrix->data[1][1] = 2;
        
        /*
          2 9 -X-> 
          7 1 ---> 7 1
          9 2 ---> 9 2
        */
        round_matrix(test_matrix);
        if (matrix_cmp(test_matrix, result_matrix))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(result_matrix);
    }

    printf("Remove two rows: ");
    {
        matrix_s *test_matrix = NULL, *result_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(4, 2, &status);
        result_matrix = allocate_matrix(2, 2, &status);
        
        assert(test_matrix && result_matrix && status == OK);
        test_matrix->data[0][0] = 2, test_matrix->data[0][1] = 9;
        test_matrix->data[1][0] = 3, test_matrix->data[1][1] = 6;
        test_matrix->data[2][0] = 7, test_matrix->data[2][1] = 1;
        test_matrix->data[3][0] = 9, test_matrix->data[3][1] = 2;
        result_matrix->data[0][0] = 3, result_matrix->data[0][1] = 6;
        result_matrix->data[1][0] = 7, result_matrix->data[1][1] = 1;
        
        /*
          2 9 -X-> 
          3 6 ---> 3 6
          7 1 ---> 7 1
          9 2 -X-> 
        */
        round_matrix(test_matrix);
        if (matrix_cmp(test_matrix, result_matrix))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(result_matrix);
    }

    printf("Remove two columns: ");
    {
        matrix_s *test_matrix = NULL, *result_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(2, 4, &status);
        result_matrix = allocate_matrix(2, 2, &status);
        
        assert(test_matrix && result_matrix && status == OK);
        test_matrix->data[0][0] = 9, test_matrix->data[0][1] = 3, test_matrix->data[0][2] = 6, test_matrix->data[0][3] = 4;
        test_matrix->data[1][0] = 1, test_matrix->data[1][1] = 0, test_matrix->data[1][2] = 7, test_matrix->data[1][3] = 8;
        result_matrix->data[0][0] = 3, result_matrix->data[0][1] = 6;
        result_matrix->data[1][0] = 0, result_matrix->data[1][1] = 7;
        
        /*
          9 3 6 4 ---> 3 6
          1 0 7 8 ---> 0 7
        */
        round_matrix(test_matrix);
        if (matrix_cmp(test_matrix, result_matrix))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(result_matrix);
    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}


void test_find_row_max(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    matrix_s *test_matrix = NULL;
    int status = OK;
    test_matrix = allocate_matrix(3, 3, &status);
    
    assert(test_matrix && status == OK);
    test_matrix->data[0][0] = 9, test_matrix->data[0][1] = 7, test_matrix->data[0][2] = 2;
    test_matrix->data[1][0] = 3, test_matrix->data[1][1] = 0, test_matrix->data[1][2] = 7;
    test_matrix->data[2][0] = 8, test_matrix->data[2][1] = 8, test_matrix->data[2][2] = 1;
    
    /*
        9 7 2 ---> max = 9
        3 0 7 ---> max = 7
        8 8 1 ---> max = 8
    */

    printf("First elemnt max: ");
    if (find_row_max(test_matrix->data[0], test_matrix->cur_columns) == 9)
        puts("OK");
    else
    {
        puts("FAILED");
        err_count++;
    }

    printf("last elemnt max: ");
    if (find_row_max(test_matrix->data[1], test_matrix->cur_columns) == 7)
        puts("OK");
    else
    {
        puts("FAILED");
        err_count++;
    }

    printf("Two max following: ");
    if (find_row_max(test_matrix->data[2], test_matrix->cur_columns) == 8)
        puts("OK");
    else
    {
        puts("FAILED");
        err_count++;
    }

    free_matrix(test_matrix);

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_find_col_avg(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    matrix_s *test_matrix = NULL;
    int status = OK;
    test_matrix = allocate_matrix(3, 3, &status);
    
    assert(test_matrix && status == OK);
    test_matrix->data[0][0] = 9, test_matrix->data[0][1] = 7, test_matrix->data[0][2] = -2;
    test_matrix->data[1][0] = 3, test_matrix->data[1][1] = 1, test_matrix->data[1][2] = 7;
    test_matrix->data[2][0] = 9, test_matrix->data[2][1] = 8, test_matrix->data[2][2] = 1;
    
    /*
        9 7 -2 
        3 1 7 
        9 8 1 
        | | |
        v v v
        7 5 3
    */
    printf("Int test: ");
    if (find_col_avg(test_matrix, 0) == 7)
        puts("OK");
    else
    {
        puts("FAILED");
        err_count++;
    }

    printf("Float test: ");
    if (find_col_avg(test_matrix, 1) == 5)
        puts("OK");
    else
    {
        puts("FAILED");
        err_count++;
    }

    printf("Negative number test: ");
    if (find_col_avg(test_matrix, 2) == 2)
        puts("OK");
    else
    {
        puts("FAILED");
        err_count++;
    }

    free_matrix(test_matrix);

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_equalize(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Normal test: ");
    {
        matrix_s *test_matrix = NULL, *result_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(2, 2, &status);
        result_matrix = allocate_matrix(3, 3, &status);
        
        assert(test_matrix && result_matrix && status == OK);
        test_matrix->data[0][0] = 4, test_matrix->data[0][1] = 1;
        test_matrix->data[1][0] = 3, test_matrix->data[1][1] = 7;
        result_matrix->data[0][0] = 4, result_matrix->data[0][1] = 1, result_matrix->data[0][2] = 4;
        result_matrix->data[1][0] = 3, result_matrix->data[1][1] = 7, result_matrix->data[1][2] = 7;
        result_matrix->data[2][0] = 3, result_matrix->data[2][1] = 4, result_matrix->data[2][2] = 4;
        
        /*
          4 1      4 1 4
          3 7 ---> 3 7 7
                   3 4 4
        */
        equalize(test_matrix, 1);
        if (matrix_cmp(test_matrix, result_matrix))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(result_matrix);
    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_multiply_matrix(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Normal test: ");
    {
        matrix_s *matrix_a = NULL, *matrix_b = NULL, *result_matrix = NULL, *control_matrix = NULL;
        int status = OK;
        matrix_a = allocate_matrix(2, 2, &status);
        matrix_b = allocate_matrix(2, 2, &status);
        result_matrix = allocate_matrix(2, 2, &status);
        control_matrix = allocate_matrix(2, 2, &status);
        
        assert(matrix_a && matrix_b && result_matrix && control_matrix && status == OK);
        matrix_a->data[0][0] = 2, matrix_a->data[0][1] = 4;
        matrix_a->data[1][0] = 6, matrix_a->data[1][1] = 7;
        matrix_b->data[0][0] = 0, matrix_b->data[0][1] = 1;
        matrix_b->data[1][0] = 7, matrix_b->data[1][1] = 8;
        control_matrix->data[0][0] = 28, control_matrix->data[0][1] = 34;
        control_matrix->data[1][0] = 49, control_matrix->data[1][1] = 62;
        
        /*
          2 4  \/  0 1  ---  28 34
          6 7  /\  7 8  ---  49 62
        */
        multiply_matrix(matrix_a, matrix_b, result_matrix);
        if (matrix_cmp(result_matrix, control_matrix))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(matrix_a);
        free_matrix(matrix_b);
        free_matrix(result_matrix);
        free_matrix(control_matrix);
    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_pow_matrix(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Cubic power: ");
    {
        matrix_s *test_matrix = NULL, *control_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(2, 2, &status);
        control_matrix = allocate_matrix(2, 2, &status);

        assert(test_matrix && control_matrix && status == OK);
        test_matrix->data[0][0] = 2, test_matrix->data[0][1] = 4;
        test_matrix->data[1][0] = 6, test_matrix->data[1][1] = 7;
        control_matrix->data[0][0] = 272, control_matrix->data[0][1] = 364;
        control_matrix->data[1][0] = 546, control_matrix->data[1][1] = 727;       

        /*
          2 4   ^3   272 364
          6 7  --->  546 727
        */
        status = matrix_pow(test_matrix, 3);
        if (matrix_cmp(test_matrix, control_matrix) && status == OK)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(control_matrix);
    }

    printf("Square power: ");
    {
        matrix_s *test_matrix = NULL, *control_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(2, 2, &status);
        control_matrix = allocate_matrix(2, 2, &status);

        assert(test_matrix && control_matrix && status == OK);
        test_matrix->data[0][0] = 2, test_matrix->data[0][1] = 4;
        test_matrix->data[1][0] = 6, test_matrix->data[1][1] = 7;
        control_matrix->data[0][0] = 28, control_matrix->data[0][1] = 36;
        control_matrix->data[1][0] = 54, control_matrix->data[1][1] = 73;       

        /*
          2 4   ^2   28 36
          6 7  --->  54 73
        */
        status = matrix_pow(test_matrix, 2);
        if (matrix_cmp(test_matrix, control_matrix) && status == OK)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(control_matrix);
    }

    printf("Zero power: ");
    {
        matrix_s *test_matrix = NULL, *control_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(2, 2, &status);
        control_matrix = allocate_matrix(2, 2, &status);

        assert(test_matrix && control_matrix && status == OK);
        test_matrix->data[0][0] = 2, test_matrix->data[0][1] = 4;
        test_matrix->data[1][0] = 6, test_matrix->data[1][1] = 7;
        turn_matrix_to_unity(control_matrix);

        /*
          2 4   ^0   1 0
          6 7  --->  0 1
        */
        status = matrix_pow(test_matrix, 0);
        if (matrix_cmp(test_matrix, control_matrix) && status == OK)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(control_matrix);
    }

    printf("Power of one: ");
    {
        matrix_s *test_matrix = NULL, *control_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(2, 2, &status);
        control_matrix = allocate_matrix(2, 2, &status);

        assert(test_matrix && control_matrix && status == OK);
        test_matrix->data[0][0] = 2, test_matrix->data[0][1] = 4;
        test_matrix->data[1][0] = 6, test_matrix->data[1][1] = 7;
        control_matrix->data[0][0] = 2, control_matrix->data[0][1] = 4;
        control_matrix->data[1][0] = 6, control_matrix->data[1][1] = 7;       

        /*
          2 4   ^1   2 4
          6 7  --->  6 7
        */
        status = matrix_pow(test_matrix, 1);
        if (matrix_cmp(test_matrix, control_matrix) && status == OK)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(control_matrix);
    }
    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_transpose(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Normal test 3x3: ");
    {
        matrix_s *test_matrix = NULL, *control_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(3, 3, &status);
        control_matrix = allocate_matrix(3, 3, &status);

        assert(test_matrix && control_matrix && status == OK);

        test_matrix->data[0][0] = 1, test_matrix->data[0][1] = 2, test_matrix->data[0][2] = 3;
        test_matrix->data[1][0] = 4, test_matrix->data[1][1] = 5, test_matrix->data[1][2] = 6;
        test_matrix->data[2][0] = 7, test_matrix->data[2][1] = 8, test_matrix->data[2][2] = 9;
        
        control_matrix->data[0][0] = 1, control_matrix->data[0][1] = 4, control_matrix->data[0][2] = 7;
        control_matrix->data[1][0] = 2, control_matrix->data[1][1] = 5, control_matrix->data[1][2] = 8;
        control_matrix->data[2][0] = 3, control_matrix->data[2][1] = 6, control_matrix->data[2][2] = 9;      

        /*
          1 2 3      1 4 7
          4 5 6 ---> 2 5 8
          7 8 9      3 6 9
        */
        transpose(test_matrix);
        if (matrix_cmp(test_matrix, control_matrix) && status == OK)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(control_matrix);
    }

    printf("Unity matrix transpose: ");
    {
        matrix_s *test_matrix = NULL, *control_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(3, 3, &status);
        control_matrix = allocate_matrix(3, 3, &status);

        assert(test_matrix && control_matrix && status == OK);

        test_matrix->data[0][0] = 1, test_matrix->data[0][1] = 0, test_matrix->data[0][2] = 0;
        test_matrix->data[1][0] = 0, test_matrix->data[1][1] = 1, test_matrix->data[1][2] = 0;
        test_matrix->data[2][0] = 0, test_matrix->data[2][1] = 0, test_matrix->data[2][2] = 1;
        
        control_matrix->data[0][0] = 1, control_matrix->data[0][1] = 0, control_matrix->data[0][2] = 0;
        control_matrix->data[1][0] = 0, control_matrix->data[1][1] = 1, control_matrix->data[1][2] = 0;
        control_matrix->data[2][0] = 0, control_matrix->data[2][1] = 0, control_matrix->data[2][2] = 1;      

        /*
          1 0 0      1 0 0
          0 1 0 ---> 0 1 0
          0 0 1      0 0 1
        */
        transpose(test_matrix);
        if (matrix_cmp(test_matrix, control_matrix) && status == OK)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(control_matrix);
    }

    printf("Normal test 2x2: ");
    {
        matrix_s *test_matrix = NULL, *control_matrix = NULL;
        int status = OK;
        test_matrix = allocate_matrix(2, 2, &status);
        control_matrix = allocate_matrix(2, 2, &status);

        assert(test_matrix && control_matrix && status == OK);

        test_matrix->data[0][0] = 1, test_matrix->data[0][1] = 2;
        test_matrix->data[1][0] = 3, test_matrix->data[1][1] = 4;
        
        control_matrix->data[0][0] = 1, control_matrix->data[0][1] = 3;
        control_matrix->data[1][0] = 2, control_matrix->data[1][1] = 4;

        /*
          1 2 ---> 1 3
          3 4 ---> 2 4
        */
        transpose(test_matrix);
        if (matrix_cmp(test_matrix, control_matrix) && status == OK)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(test_matrix);
        free_matrix(control_matrix);
    }
    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_multiply_transpose_matrix(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Normal test: ");
    {
        matrix_s *matrix_a = NULL, *matrix_b = NULL, *result_matrix = NULL, *control_matrix = NULL;
        int status = OK;
        matrix_a = allocate_matrix(2, 2, &status);
        matrix_b = allocate_matrix(2, 2, &status);
        result_matrix = allocate_matrix(2, 2, &status);
        control_matrix = allocate_matrix(2, 2, &status);
        
        assert(matrix_a && matrix_b && result_matrix && control_matrix && status == OK);
        matrix_a->data[0][0] = 2, matrix_a->data[0][1] = 4;
        matrix_a->data[1][0] = 6, matrix_a->data[1][1] = 7;
        matrix_b->data[0][0] = 0, matrix_b->data[0][1] = 7;
        matrix_b->data[1][0] = 1, matrix_b->data[1][1] = 8;
        control_matrix->data[0][0] = 28, control_matrix->data[0][1] = 34;
        control_matrix->data[1][0] = 49, control_matrix->data[1][1] = 62;
        
        /*
          2 4  \/  0 7  ---  28 34
          6 7  /\  1 8  ---  49 62
        */
        multiply_transpose_matrix(matrix_a, matrix_b, result_matrix);
        if (matrix_cmp(result_matrix, control_matrix))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
        free_matrix(matrix_a);
        free_matrix(matrix_b);
        free_matrix(result_matrix);
        free_matrix(control_matrix);
    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

int main(void)
{
    setbuf(stdout, NULL);

    test_find_max_element_pos();
    test_round_matrix();
    test_find_row_max();
    test_find_col_avg();
    test_equalize();
    test_multiply_matrix();
    test_pow_matrix();
    test_transpose();
    test_multiply_transpose_matrix();
}

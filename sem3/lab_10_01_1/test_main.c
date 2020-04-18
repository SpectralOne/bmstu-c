#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "custom_errors.h"
#include "custom_defines.h"
#include "utility_funcs.h"
#include "sort.h"

#define ABS(x) ((x) < 0) ? -(x) : (x)
#define PRECISION 0.0000001

int f_equal(float num1, float num2)
{
    if (ABS(num1 - num2) < PRECISION)
        return 1;
    return 0;
}

int compare_struct_arrays(person_s **array1, person_s **array2, const int count)
{
    for (int i = 0; i < count; i++)
        if (strcmp(array1[i]->surname, array2[i]->surname) != 0)
            return 0;
    return 1;
}

void test_check_date_string(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;
    const char format[] = "%Y.%m.%d";

    printf("Empty string: ");
    {
        const char date[] = "";
        if (check_date_string(date, format) == INV_DATE)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }
    
    printf("Non-leap year: ");
    {
        const char date[] = "2019.02.29";
        if (check_date_string(date, format) == INV_DATE)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }

    printf("Normal test: ");
    {
        const char date[] = "2012.04.02";
        if (check_date_string(date, format) == VALID)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }

    printf("Leap year check: ");
    {
        const char date[] = "2012.02.29";
        if (check_date_string(date, format) == VALID)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_check_sex_string(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Empty string: ");
    {
        const char date[] = "";
        if (check_sex_string(date) == INV_SEX)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }
    
    printf("Mixed: ");
    {
        const char date[] = "fEmAlE";
        if (check_sex_string(date) == FEMALE)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }

    printf("Lower case: ");
    {
        const char date[] = "male";
        if (check_sex_string(date) == MALE)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }

    printf("Random string: ");
    {
        const char date[] = "Hello!";
        if (check_sex_string(date) == INV_SEX)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }

    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_grades_average(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0, status = OK;
    
    person_s *person = allocate_struct(&status);
    assert(status == OK && person);

    printf("Normal test (posisitive numbers): ");
    {
        int grades[] = { 1, 2, 3, 4 };
        person->grades->count = 4;
        person->grades->grades_array = grades;

        float avg = grades_average(person->grades);

        if (f_equal(avg, 2.5))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }
    
    printf("Normal test (negative numbers): ");
    {
        int grades[] = { -1, -2, -3, -4 };
        person->grades->count = 4;
        person->grades->grades_array = grades;

        float avg = grades_average(person->grades);

        if (f_equal(avg, -2.5))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }
    
    free(person->grades);
    free(person);
    
    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_sort(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0, status = OK;
    
    person_s *person1 = allocate_struct(&status);
    assert(person1 && status == OK);

    char surname1[] = "Cameron", sex1[] = "male", birth_date1[] = "1954.08.16";
    int grades1[] = { 1, 2, 3, 4 };
    person1->surname = surname1, person1->sex = sex1, person1->birth_day = birth_date1;
    person1->grades->count = 4, person1->grades->grades_array = grades1;

    person_s *person2 = allocate_struct(&status);
    assert(person2 && status == OK);

    char surname2[] = "Hamilton", sex2[] = "male", birth_date2[] = "1985.01.07";
    int grades2[] = { 1, 1, 1, 1 };
    person2->surname = surname2, person2->sex = sex2, person2->birth_day = birth_date2;
    person2->grades->count = 4, person2->grades->grades_array = grades2;

    person_s *person3 = allocate_struct(&status);
    assert(person3 && status == OK);

    char surname3[] = "Hathaway", sex3[] = "female", birth_date3[] = "1982.11.12";
    int grades3[] = { 5, 2, 1, 4 };
    person3->surname = surname3, person3->sex = sex3, person3->birth_day = birth_date3;
    person3->grades->count = 4, person3->grades->grades_array = grades3;

    person_s *person4 = allocate_struct(&status);
    assert(person4 && status == OK);

    char surname4[] = "test", sex4[] = "male", birth_date4[] = "1985.01.08";
    int grades4[] = { 1, 2, 2, 1 };
    person4->surname = surname4, person4->sex = sex4, person4->birth_day = birth_date4;
    person4->grades->count = 4, person4->grades->grades_array = grades4;

    person_s **test_arr = reallocate_struct_array(NULL, &status, 4);
    assert(test_arr && status == OK);
    
    person_s **result_arr = reallocate_struct_array(NULL, &status, 4);
    assert(result_arr && status == OK);

    printf("Surname sort: ");
    {
        test_arr[0] = person1, test_arr[1] = person2, test_arr[2] = person3, test_arr[3] = person4;
        result_arr[0] = person1, result_arr[1] = person2, result_arr[2] = person3, result_arr[3] = person4;
        
        sort_arr(test_arr, 4, &compare_surname);
        if (compare_struct_arrays(test_arr, result_arr, 4))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }
    
    printf("Sex sort (steady check): ");
    {
        test_arr[0] = person1, test_arr[1] = person2, test_arr[2] = person3, test_arr[3] = person4;
        result_arr[0] = person3, result_arr[1] = person1, result_arr[2] = person2, result_arr[3] = person4;
        
        sort_arr(test_arr, 4, &compare_sex);
        if (compare_struct_arrays(test_arr, result_arr, 4))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }

    printf("Birth date sort: ");
    {
        test_arr[0] = person1, test_arr[1] = person2, test_arr[2] = person3, test_arr[3] = person4;
        result_arr[0] = person1, result_arr[1] = person3, result_arr[2] = person2, result_arr[3] = person4;
        
        sort_arr(test_arr, 4, &compare_birth_date);
        if (compare_struct_arrays(test_arr, result_arr, 4))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }

    printf("Grade sort: ");
    {
        test_arr[0] = person1, test_arr[1] = person2, test_arr[2] = person3, test_arr[3] = person4;
        result_arr[0] = person2, result_arr[1] = person4, result_arr[2] = person1, result_arr[3] = person3;
        
        sort_arr(test_arr, 4, &compare_grade_average);
        if (compare_struct_arrays(test_arr, result_arr, 4))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }

    free(person1->grades), free(person2->grades), free(person3->grades), free(person4->grades);
    free(person1), free(person2), free(person3), free(person4);
    free(test_arr), free(result_arr);
    
    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_calculate_person_age(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Normal test: ");
    {
        if (calculate_person_age("2000.04.15") == 19)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }
    
    printf("Logic test: ");
    {
        if (calculate_person_age("2001.11.11") == 17 && calculate_person_age("2002.10.30") == 17)
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }
    
    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

void test_check_string(void)
{
    printf("\n--- %s ---\n\n", __func__);
    int err_count = 0;

    printf("Normal test: ");
    {
        if (!check_string("String"))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }
    
    printf("Restricted character: ");
    {
        if (check_string("Strin!g"))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }
    
    printf("First not upper: ");
    {
        if (check_string("string"))
            puts("OK");
        else
        {
            puts("FAILED");
            err_count++;
        }
    }
    
    printf("\n%s: %s\n\n", __func__, err_count ? "FAILED" : "OK");
}

int main(void)
{
    setbuf(stdout, NULL);

    test_check_date_string();
    test_check_sex_string();
    test_grades_average();
    test_sort();
    test_calculate_person_age();
    test_check_string();

    return OK;
}

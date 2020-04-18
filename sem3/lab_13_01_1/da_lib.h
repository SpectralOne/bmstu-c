#ifndef __ARRAY_UTILITY_FUNCS_H__
#define __ARRAY_UTILITY_FUNCS_H__

#define PRECISION 0.0000000000001

#define TRUE 1
#define FALSE 0

#define AMOUNT_TO_DELETE 2

#define OK 0

#define MEM_ALLOC_ERR -1
#define READ_ERR -2
#define RNG_ERR_ARR_SIZE -3
#define RNG_ERR_POS -4

typedef int (*fn_normalize_array_t)(double **, double **, const double);
typedef int (*fn_reallocate_array_t)(double **, double **, int);
typedef void (*fn_insert_to_pos_t)(double *, double *, const int, const double);
typedef double (*fn_compute_mu1_t)(const double *, const double *);
typedef double (*fn_compute_mu2_t)(const double *, const double *);
typedef void (*fn_print_array_t)(const double *, const double *);
typedef int (*fn_fill_array_t)(double *, double *);
typedef void (*fn_free_array_t)(double *);

double find_min(const double *array, const double *end_array);
double find_max(const double *array, const double *end_array);
void move_to_end(double *const array, double *const end_array);
void find_element(double *array, double *end_array, double **pos, const double mu1);
int da_normalize_array(double **array, double **end_array, const double mu1);
int delete_element(double **array, double **end_array, double *pos);
int da_reallocate_array(double **array, double **end_array, int new_size);
int f_equal(double num1, double num2);
void da_insert_to_pos(double *array, double *end_array, const int pos, const double item);
double da_compute_mu1(const double *array, const double *end_array);
double da_compute_mu2(const double *array, const double *end_array);
void da_print_array(const double *array, const double *end_array);
int da_fill_array(double *array, double *end_array);
void da_free_array(double *array);

#endif

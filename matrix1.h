#pragma once 
#include "complex.h"
#include "complex_main.h"
#include "int.h"

typedef struct {
    void* data;
    int size;
    type_info* type; 
} matrix;

type_info* get_int_type(void);
type_info* get_complex_type(void);

matrix* matrix_create(int size, type_info* type);
void matrix_free(matrix* m);
void matrix_print(matrix* m);
matrix* matrix_summ(matrix* a, matrix* b);
matrix* matrix_mul(matrix* a, matrix* b);
matrix* matrix_mul_scalar(matrix* m, float scalar);
int matrix_fill_random(matrix* m, int max_val);
int matrix_fill_manual(matrix* m, int max_val);
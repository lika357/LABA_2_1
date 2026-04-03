#pragma once 
#include "complex.h"
#include "complex_main.h"
#include "int.h"


typedef struct {
    void* data;
    int size;
    type_info* type; 
} matrix;

matrix* matrix_create(int size, type_info* type);
void matrix_free(matrix* m);
char* matrix_to_string(const matrix* m);
matrix* matrix_summ(matrix* a, matrix* b);
matrix* matrix_mul(matrix* a, matrix* b);
matrix* matrix_mul_scalar(matrix* m, float scalar);
matrix* matrix_mul_scalar_complex(matrix* m, void* scalar);
int matrix_fill_random(matrix* m, int max_val);
int matrix_fill_manual(matrix* m, int max_val);
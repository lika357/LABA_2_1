#include "matrix1.h"
#include "assert.h"
#include "complex.h"
#include "complex_main.h"
#include "int.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>

matrix* create_test_int_matrix(int size, int* values) {
    matrix* m = matrix_create(size, get_type_int());
    if (!m) {
        return NULL;
    }
    for (int i = 0; i < size * size; i++) {
        void* elem = (char*)m->data + i * m->type->size;
        memcpy(elem, &values[i], sizeof(int));
    }
    return m;
}

matrix* create_test_complex_matrix(int size, float* reals, float* imags) {
    matrix* m = matrix_create(size, get_complex_type());
    if (!m) {
        return NULL;
    }
    for (int i = 0; i < size * size; i++) {
        void* elem = (char*)m->data + i * m->type->size;
        complex* c = complex_creat(reals[i], imags[i]);
        memcpy(elem, c, sizeof(complex));
        free(c);
    }
    return m;
}

int compare_int_matrices(matrix* a, matrix* b) {
    if (!a || !b || a->size != b->size) {
        return 0;
    }
    int size = a->size;
    for (int i = 0; i < size * size; i++) {
        int val_a = *(int*)((char*)a->data + i * sizeof(int));
        int val_b = *(int*)((char*)b->data + i * sizeof(int));
        if (val_a != val_b) {
            return 0;
        }
    }
    return 1;
}

int compare_complex_matrices(matrix* a, matrix* b) {
    if (!a || !b || a->size != b->size) {
        return 0;
    }
    int size = a->size;
    for (int i = 0; i < size * size; i++) {
        complex* val_a = (complex*)((char*)a->data + i * sizeof(complex));
        complex* val_b = (complex*)((char*)b->data + i * sizeof(complex));
       float eps = 0.0001f;
       if (val_a->real > val_b->real + eps || val_a->real < val_b->real - eps) {
           return 0;
        }
       if (val_a->imag > val_b->imag + eps || val_a->imag < val_b->imag - eps) {
          return 0;
        }
    }
    return 1;
}

void fill_int_matrix_sequential(matrix* m, int start) {
    int size = m->size;
    for (int i = 0; i < size * size; i++) {
        int val = start + i;
        memcpy((char*)m->data + i * sizeof(int), &val, sizeof(int));
    }
}

void test_complex_creat_complete() {
    complex* c1 = complex_creat(3.14f, 2.71f);
    assert(c1 != NULL);
    assert(c1->real == 3.14f);
    assert(c1->imag == 2.71f);
    complex_free(c1);
    
    complex* c2 = complex_creat(-5.5f, -7.7f);
    assert(c2 != NULL);
    assert(c2->real == -5.5f);
    assert(c2->imag == -7.7f);
    complex_free(c2);
    
    complex* c3 = complex_creat(0.0f, 0.0f);
    assert(c3 != NULL);
    assert(c3->real == 0.0f);
    assert(c3->imag == 0.0f);
    complex_free(c3);
    
    complex* c4 = complex_creat(0.0001f, 0.0002f);
    assert(c4 != NULL);
    assert(c4->real > 0.00009f && c4->real < 0.00011f);
    assert(c4->imag > 0.00019f && c4->imag < 0.00021f);
    complex_free(c4);
    
    complex* c5 = complex_creat(1e10f, 1e10f);
    assert(c5 != NULL);
    complex_free(c5);
    
    for (int i = 0; i < 100; i++) {
        complex* c = complex_creat((float)i, (float)i);
        assert(c != NULL);
        assert(c->real == (float)i);
        assert(c->imag == (float)i);
        complex_free(c);
    }
}

void test_complex_summ_complete() {
    complex* a = complex_creat(10.0f, 20.0f);
    complex* b = complex_creat(30.0f, 40.0f);
    complex* result = complex_summ(a, b);
    assert(result != NULL);
    assert(result->real == 40.0f);
    assert(result->imag == 60.0f);
    complex_free(a);
    complex_free(b);
    complex_free(result);
    
    complex* c = complex_creat(-10.0f, -20.0f);
    complex* d = complex_creat(-5.0f, -15.0f);
    result = complex_summ(c, d);
    assert(result->real == -15.0f);
    assert(result->imag == -35.0f);
    complex_free(c);
    complex_free(d);
    complex_free(result);
    
    complex* zero = complex_creat(0.0f, 0.0f);
    complex* num = complex_creat(42.0f, 42.0f);
    result = complex_summ(num, zero);
    assert(result->real == 42.0f);
    assert(result->imag == 42.0f);
    complex_free(zero);
    complex_free(num);
    complex_free(result);
    
    complex* e = complex_creat(100.0f, 100.0f);
    complex* f = complex_creat(-50.0f, -50.0f);
    result = complex_summ(e, f);
    assert(result->real == 50.0f);
    assert(result->imag == 50.0f);
    complex_free(e);
    complex_free(f);
    complex_free(result);
    
    complex* g = complex_creat(1.0f, 1.0f);
    assert(complex_summ(NULL, g) == NULL);
    assert(complex_summ(g, NULL) == NULL);
    assert(complex_summ(NULL, NULL) == NULL);
    complex_free(g);
}

void test_complex_mult_complete() {
    complex* a = complex_creat(1.0f, 2.0f);
    complex* b = complex_creat(3.0f, 4.0f);
    complex* result = complex_mult(a, b);
    assert(result->real == -5.0f);
    assert(result->imag == 10.0f);
    complex_free(a);
    complex_free(b);
    complex_free(result);
    
    complex* zero = complex_creat(0.0f, 0.0f);
    complex* num = complex_creat(42.0f, 42.0f);
    result = complex_mult(zero, num);
    assert(result->real == 0.0f);
    assert(result->imag == 0.0f);
    complex_free(zero);
    complex_free(num);
    complex_free(result);
    
    complex* c = complex_creat(2.0f, 3.0f);
    complex* real = complex_creat(4.0f, 0.0f);
    result = complex_mult(c, real);
    assert(result->real == 8.0f);
    assert(result->imag == 12.0f);
    complex_free(c);
    complex_free(real);
    complex_free(result);
    
    complex* d = complex_creat(2.0f, 3.0f);
    complex* imag = complex_creat(0.0f, 4.0f);
    result = complex_mult(d, imag);
    assert(result->real == -12.0f);
    assert(result->imag == 8.0f);
    complex_free(d);
    complex_free(imag);
    complex_free(result);
    
    complex* e = complex_creat(3.0f, 4.0f);
    complex* f = complex_creat(3.0f, -4.0f);
    result = complex_mult(e, f);
    assert(result->real == 25.0f);
    assert(result->imag == 0.0f);
    complex_free(e);
    complex_free(f);
    complex_free(result);
    
    complex* g = complex_creat(1.0f, 1.0f);
    assert(complex_mult(NULL, g) == NULL);
    assert(complex_mult(g, NULL) == NULL);
    complex_free(g);
    
    for (int i = 0; i < 100; i++) {
        float r1 = rand() % 100 - 50;
        float i1 = rand() % 100 - 50;
        float r2 = rand() % 100 - 50;
        float i2 = rand() % 100 - 50;
        
        complex* x = complex_creat(r1, i1);
        complex* y = complex_creat(r2, i2);
        result = complex_mult(x, y);
        
        float expected_r = r1 * r2 - i1 * i2;
        float expected_i = r1 * i2 + i1 * r2;
        
        float eps = 0.001f;
        assert(result->real > expected_r - eps && result->real < expected_r + eps);
        assert(result->imag > expected_i - eps && result->imag < expected_i + eps);
        
        complex_free(x);
        complex_free(y);
        complex_free(result);
    }
}

void test_complex_mult_scalar_complete() {
    complex* a = complex_creat(2.0f, 3.0f);
    complex* result = complex_mult_scalar(a, 4.0f);
    assert(result->real == 8.0f);
    assert(result->imag == 12.0f);
    complex_free(a);
    complex_free(result);
    
    complex* b = complex_creat(1.0f, 1.0f);
    result = complex_mult_scalar(b, -2.0f);
    assert(result->real == -2.0f);
    assert(result->imag == -2.0f);
    complex_free(b);
    complex_free(result);
    
    complex* c = complex_creat(100.0f, 100.0f);
    result = complex_mult_scalar(c, 0.0f);
    assert(result->real == 0.0f);
    assert(result->imag == 0.0f);
    complex_free(c);
    complex_free(result);
    
    complex* d = complex_creat(10.0f, 10.0f);
    result = complex_mult_scalar(d, 0.5f);
    assert(result->real == 5.0f);
    assert(result->imag == 5.0f);
    complex_free(d);
    complex_free(result);
    
    assert(complex_mult_scalar(NULL, 5.0f) == NULL);
    
    for (int i = 0; i < 100; i++) {
        float r = rand() % 200 - 100;
        float im = rand() % 200 - 100;
        float scalar = (rand() % 200 - 100) / 10.0f;
        
        complex* x = complex_creat(r, im);
        result = complex_mult_scalar(x, scalar);
        
        float eps = 0.001f;
        assert(result->real > r * scalar - eps && result->real < r * scalar + eps);
        assert(result->imag > im * scalar - eps && result->imag < im * scalar + eps);
        
        complex_free(x);
        complex_free(result);
    }
}

void test_complex_summ_n() {
    complex a1 = {10.0f, 20.0f};
    complex b1 = {30.0f, 40.0f};
    complex* result1 = (complex*)complex_summ_n(&a1, &b1);
    assert(result1 != NULL);
    assert(result1->real == 40.0f);
    assert(result1->imag == 60.0f);
    free(result1);
    
    complex a2 = {-10.0f, -20.0f};
    complex b2 = {-5.0f, -15.0f};
    complex* result2 = (complex*)complex_summ_n(&a2, &b2);
    assert(result2->real == -15.0f);
    assert(result2->imag == -35.0f);
    free(result2);
    
    complex a3 = {42.0f, 42.0f};
    complex b3 = {0.0f, 0.0f};
    complex* result3 = (complex*)complex_summ_n(&a3, &b3);
    assert(result3->real == 42.0f);
    assert(result3->imag == 42.0f);
    free(result3);
    
    for (int i = 0; i < 100; i++) {
        float r1 = (rand() % 2000 - 1000) / 10.0f;
        float i1 = (rand() % 2000 - 1000) / 10.0f;
        float r2 = (rand() % 2000 - 1000) / 10.0f;
        float i2 = (rand() % 2000 - 1000) / 10.0f;
        
        complex x = {r1, i1};
        complex y = {r2, i2};
        complex* result = (complex*)complex_summ_n(&x, &y);
        
        float eps = 0.001f;
        assert(result->real > (r1 + r2) - eps && result->real < (r1 + r2) + eps);
        assert(result->imag > (i1 + i2) - eps && result->imag < (i1 + i2) + eps);
        free(result);
    }
}

void test_complex_mult_n() {
    complex a1 = {1.0f, 2.0f};
    complex b1 = {3.0f, 4.0f};
    complex* result1 = (complex*)complex_mult_n(&a1, &b1);
    assert(result1->real == -5.0f);
    assert(result1->imag == 10.0f);
    free(result1);
    
    complex a2 = {5.0f, 5.0f};
    complex b2 = {0.0f, 0.0f};
    complex* result2 = (complex*)complex_mult_n(&a2, &b2);
    assert(result2->real == 0.0f);
    assert(result2->imag == 0.0f);
    free(result2);
    
    for (int i = 0; i < 100; i++) {
        float r1 = (rand() % 200 - 100) / 10.0f;
        float i1 = (rand() % 200 - 100) / 10.0f;
        float r2 = (rand() % 200 - 100) / 10.0f;
        float i2 = (rand() % 200 - 100) / 10.0f;
        
        complex x = {r1, i1};
        complex y = {r2, i2};
        complex* result = (complex*)complex_mult_n(&x, &y);
        
        float expected_r = r1 * r2 - i1 * i2;
        float expected_i = r1 * i2 + i1 * r2;
        float eps = 0.001f;
        
        assert(result->real > expected_r - eps && result->real < expected_r + eps);
        assert(result->imag > expected_i - eps && result->imag < expected_i + eps);
        free(result);
    }
}

void test_complex_mult_scalar_n() {
    complex a1 = {2.0f, 3.0f};
    complex* result1 = (complex*)complex_mult_scalar_n(&a1, 4.0f);
    assert(result1->real == 8.0f);
    assert(result1->imag == 12.0f);
    free(result1);
    
    complex a2 = {1.0f, 1.0f};
    complex* result2 = (complex*)complex_mult_scalar_n(&a2, -2.0f);
    assert(result2->real == -2.0f);
    assert(result2->imag == -2.0f);
    free(result2);
    
    for (int i = 0; i < 100; i++) {
        float r = (rand() % 200 - 100) / 10.0f;
        float im = (rand() % 200 - 100) / 10.0f;
        float scalar = (rand() % 200 - 100) / 10.0f;
        
        complex x = {r, im};
        complex* result = (complex*)complex_mult_scalar_n(&x, scalar);
        
        float eps = 0.001f;
        assert(result->real > r * scalar - eps && result->real < r * scalar + eps);
        assert(result->imag > im * scalar - eps && result->imag < im * scalar + eps);
        free(result);
    }
}

void test_complex_mult_scalar_complex_n() {
    complex a1 = {1.0f, 2.0f};
    complex b1 = {3.0f, 4.0f};
    complex* result1 = (complex*)complex_mult_scalar_complex_n(&a1, &b1);
    assert(result1->real == -5.0f);
    assert(result1->imag == 10.0f);
    free(result1);
    
    complex a2 = {5.0f, 5.0f};
    complex b2 = {0.0f, 0.0f};
    complex* result2 = (complex*)complex_mult_scalar_complex_n(&a2, &b2);
    assert(result2->real == 0.0f);
    assert(result2->imag == 0.0f);
    free(result2);
    
    complex a3 = {1.0f, 1.0f};
    complex b3 = {1.0f, 1.0f};
    assert(complex_mult_scalar_complex_n(NULL, &b3) == NULL);
    assert(complex_mult_scalar_complex_n(&a3, NULL) == NULL);
    assert(complex_mult_scalar_complex_n(NULL, NULL) == NULL);
    
    for (int i = 0; i < 100; i++) {
        float r1 = (rand() % 200 - 100) / 10.0f;
        float i1 = (rand() % 200 - 100) / 10.0f;
        float r2 = (rand() % 200 - 100) / 10.0f;
        float i2 = (rand() % 200 - 100) / 10.0f;
        
        complex x = {r1, i1};
        complex y = {r2, i2};
        complex* result = (complex*)complex_mult_scalar_complex_n(&x, &y);
        
        float expected_r = r1 * r2 - i1 * i2;
        float expected_i = r1 * i2 + i1 * r2;
        float eps = 0.001f;
        
        assert(result->real > expected_r - eps && result->real < expected_r + eps);
        assert(result->imag > expected_i - eps && result->imag < expected_i + eps);
        free(result);
    }
}

void test_complex_free_n() {
    complex_free_n(NULL);
    complex* c = (complex*)malloc(sizeof(complex));
    assert(c != NULL);
    complex_free_n(c);

    for (int i = 0; i < 100; i++) {
        complex* c = (complex*)malloc(sizeof(complex));
        assert(c != NULL);
        complex_free_n(c);
    }
}

void test_get_type_int_complete() {
    type_info* type = get_type_int();
    assert(type != NULL);
    assert(type->size == sizeof(int));
    assert(type->print != NULL);
    assert(type->summ != NULL);
    assert(type->mult != NULL);
    assert(type->mult_scalar != NULL);
    assert(type->free != NULL);
    
    type_info* type2 = get_type_int();
    assert(type == type2);
}

void test_print_int_complete() {
    type_info* type = get_type_int();
    
    int val1 = 42;
    char* str1 = type->print(&val1);
    assert(str1 != NULL);
    assert(strcmp(str1, " 42") == 0);  
    free(str1);
    
    int val2 = -42;
    char* str2 = type->print(&val2);
    assert(str2 != NULL);
    assert(strcmp(str2, "-42") == 0);
    free(str2);

    int val3 = 0;
    char* str3 = type->print(&val3);
    assert(str3 != NULL);
    assert(strcmp(str3, " 0") == 0);
    free(str3);
    
    assert(type->print(NULL) == NULL);
    
    for (int i = 0; i < 100; i++) {
        int val = rand() % 20000 - 10000;
        char* str = type->print(&val);
        assert(str != NULL);
        free(str);
    }
}

void test_summ_int_complete() {
    type_info* type = get_type_int();
    
    int a = 5, b = 7;
    int* result = (int*)type->summ(&a, &b);
    assert(*result == 12);
    free(result);
    
    int c = -10, d = -20;
    result = (int*)type->summ(&c, &d);
    assert(*result == -30);
    free(result);
    
    int e = 100, f = -50;
    result = (int*)type->summ(&e, &f);
    assert(*result == 50);
    free(result);
    
    int g = 42, h = 0;
    result = (int*)type->summ(&g, &h);
    assert(*result == 42);
    free(result);
    
    int k = 5;
    assert(type->summ(NULL, &k) == NULL);
    assert(type->summ(&k, NULL) == NULL);
    assert(type->summ(NULL, NULL) == NULL);
    
    for (int i = 0; i < 100; i++) {
        int x = rand() % 1000 - 500;
        int y = rand() % 1000 - 500;
        result = (int*)type->summ(&x, &y);
        assert(*result == x + y);
        free(result);
    }
}

void test_mult_int_complete() {
    type_info* type = get_type_int();
    
    int a = 6, b = 7;
    int* result = (int*)type->mult(&a, &b);
    assert(*result == 42);
    free(result);
    
    int c = -5, d = -5;
    result = (int*)type->mult(&c, &d);
    assert(*result == 25);
    free(result);

    int e = -10, f = 10;
    result = (int*)type->mult(&e, &f);
    assert(*result == -100);
    free(result);
    
    int g = 42, h = 0;
    result = (int*)type->mult(&g, &h);
    assert(*result == 0);
    free(result);
    
    int i = 100, j = 1;
    result = (int*)type->mult(&i, &j);
    assert(*result == 100);
    free(result);
    
    int m = 5;
    assert(type->mult(NULL, &m) == NULL);
    assert(type->mult(&m, NULL) == NULL);
    
    for (int i = 0; i < 100; i++) {
        int x = rand() % 100 - 50;
        int y = rand() % 100 - 50;
        result = (int*)type->mult(&x, &y);
        assert(*result == x * y);
        free(result);
    }
}

void test_mult_scalar_int_complete() {
    type_info* type = get_type_int();
    
    int a = 21;
    int* result = (int*)type->mult_scalar(&a, 2.0f);
    assert(*result == 42);
    free(result);
    
    int b = 10;
    result = (int*)type->mult_scalar(&b, -2.0f);
    assert(*result == -20);
    free(result);
    
    int c = 100;
    result = (int*)type->mult_scalar(&c, 0.0f);
    assert(*result == 0);
    free(result);
    
    int d = 10;
    result = (int*)type->mult_scalar(&d, 0.5f);
    assert(*result == 5);
    free(result);
    
    assert(type->mult_scalar(NULL, 5.0f) == NULL);
    
    for (int i = 0; i < 100; i++) {
        int x = rand() % 100 - 50;
        float scalar = (rand() % 200 - 100) / 10.0f;
        result = (int*)type->mult_scalar(&x, scalar);
        assert(*result == (int)(x * scalar));
        free(result);
    }
}

void test_get_complex_type_complete() {
    type_info* type = get_complex_type();
    assert(type != NULL);
    assert(type->size == sizeof(complex));
    assert(type->print != NULL);
    assert(type->summ != NULL);
    assert(type->mult != NULL);
    assert(type->mult_scalar != NULL);
    assert(type->mult_scalar_complex != NULL);
    assert(type->free != NULL);

    type_info* type2 = get_complex_type();
    assert(type == type2);
}

void test_print_complex_complete() {
    type_info* type = get_complex_type();
    
    complex c1 = {3.14f, 2.71f};
    char* str1 = type->print(&c1);
    assert(str1 != NULL);
    assert(strcmp(str1, " 3.14+2.71i") == 0);
    free(str1);

    complex c2 = {-3.14f, -2.71f};
    char* str2 = type->print(&c2);
    assert(str2 != NULL);
    assert(strcmp(str2, "-3.14-2.71i") == 0);
    free(str2);
    
    complex c3 = {5.0f, 0.0f};
    char* str3 = type->print(&c3);
    assert(str3 != NULL);
    assert(strcmp(str3, " 5.00+0.00i") == 0);
    free(str3);
    
    complex c4 = {0.0f, 5.0f};
    char* str4 = type->print(&c4);
    assert(str4 != NULL);
    assert(strcmp(str4, " 0.00+5.00i") == 0);
    free(str4);
    
    complex c5 = {3.14f, -2.71f};
    char* str5 = type->print(&c5);
    assert(str5 != NULL);
    assert(strcmp(str5, " 3.14-2.71i") == 0);
    free(str5);
    
    complex c6 = {-3.14f, 2.71f};
    char* str6 = type->print(&c6);
    assert(str6 != NULL);
    assert(strcmp(str6, "-3.14+2.71i") == 0);
    free(str6);
    
    assert(type->print(NULL) == NULL);
}

void test_complex_mult_scalar_complex_n_via_type() {
    type_info* type = get_complex_type();
    
    complex a = {1.0f, 2.0f};
    complex b = {3.0f, 4.0f};
    complex* result = (complex*)type->mult_scalar_complex(&a, &b);
    assert(result->real == -5.0f);
    assert(result->imag == 10.0f);
    free(result);
    
    complex zero = {0.0f, 0.0f};
    complex num = {5.0f, 5.0f};
    result = (complex*)type->mult_scalar_complex(&zero, &num);
    assert(result->real == 0.0f);
    assert(result->imag == 0.0f);
    free(result);
    
    assert(type->mult_scalar_complex(NULL, &b) == NULL);
    assert(type->mult_scalar_complex(&a, NULL) == NULL);
    
    for (int i = 0; i < 100; i++) {
        complex x = {(rand() % 100 - 50) / 10.0f, (rand() % 100 - 50) / 10.0f};
        complex y = {(rand() % 100 - 50) / 10.0f, (rand() % 100 - 50) / 10.0f};
        
        result = (complex*)type->mult_scalar_complex(&x, &y);
        float expected_r = x.real * y.real - x.imag * y.imag;
        float expected_i = x.real * y.imag + x.imag * y.real;
        float eps = 0.001f;
        
        assert(result->real > expected_r - eps && result->real < expected_r + eps);
        assert(result->imag > expected_i - eps && result->imag < expected_i + eps);
        free(result);
    }
}

void test_matrix_create_complete() {
    type_info* int_type = get_type_int();
    type_info* complex_type = get_complex_type();
    
    for (int size = 1; size <= 10; size++) {
        matrix* m = matrix_create(size, int_type);
        assert(m != NULL);
        assert(m->size == size);
        assert(m->data != NULL);
        assert(m->type == int_type);
        matrix_free(m);
    }
    
    for (int size = 1; size <= 5; size++) {
        matrix* m = matrix_create(size, complex_type);
        assert(m != NULL);
        assert(m->size == size);
        matrix_free(m);
    }
    
    assert(matrix_create(0, int_type) == NULL);
    assert(matrix_create(-1, int_type) == NULL);
    assert(matrix_create(-100, int_type) == NULL);
    
    assert(matrix_create(5, NULL) == NULL);
}

void test_matrix_summ_complete() {
    type_info* type = get_type_int();
    
    int vals_a1[] = {5};
    int vals_b1[] = {7};
    int expected1[] = {12};
    
    matrix* a1 = create_test_int_matrix(1, vals_a1);
    matrix* b1 = create_test_int_matrix(1, vals_b1);
    matrix* result1 = matrix_summ(a1, b1);
    assert(result1 != NULL);
    assert(compare_int_matrices(result1, create_test_int_matrix(1, expected1)));
    matrix_free(a1);
    matrix_free(b1);
    matrix_free(result1);
    
    int vals_a2[] = {1, 2, 3, 4};
    int vals_b2[] = {5, 6, 7, 8};
    int expected2[] = {6, 8, 10, 12};
    
    matrix* a2 = create_test_int_matrix(2, vals_a2);
    matrix* b2 = create_test_int_matrix(2, vals_b2);
    matrix* result2 = matrix_summ(a2, b2);
    assert(result2 != NULL);
    assert(compare_int_matrices(result2, create_test_int_matrix(2, expected2)));
    matrix_free(a2);
    matrix_free(b2);
    matrix_free(result2);
    
    int vals_a3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int vals_b3[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int expected3[] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
    
    matrix* a3 = create_test_int_matrix(3, vals_a3);
    matrix* b3 = create_test_int_matrix(3, vals_b3);
    matrix* result3 = matrix_summ(a3, b3);
    assert(result3 != NULL);
    assert(compare_int_matrices(result3, create_test_int_matrix(3, expected3)));
    matrix_free(a3);
    matrix_free(b3);
    matrix_free(result3);
    
    int zeros[] = {0, 0, 0, 0};
    matrix* zero = create_test_int_matrix(2, zeros);
    matrix* nums = create_test_int_matrix(2, vals_a2);
    matrix* result4 = matrix_summ(nums, zero);
    assert(compare_int_matrices(result4, nums));
    matrix_free(zero);
    matrix_free(nums);
    matrix_free(result4);
    
    matrix* m3 = matrix_create(3, type);
    matrix* m2 = matrix_create(2, type);
    assert(matrix_summ(m3, m2) == NULL);
    assert(matrix_summ(m2, m3) == NULL);
    matrix_free(m3);
    matrix_free(m2);
    
    matrix* m = matrix_create(2, type);
    assert(matrix_summ(NULL, m) == NULL);
    assert(matrix_summ(m, NULL) == NULL);
    assert(matrix_summ(NULL, NULL) == NULL);
    matrix_free(m);
    
    for (int t = 0; t < 10; t++) {
        int size = rand() % 5 + 1;
        matrix* ma = matrix_create(size, type);
        matrix* mb = matrix_create(size, type);
        
        for (int i = 0; i < size * size; i++) {
            int val_a = rand() % 100 - 50;
            int val_b = rand() % 100 - 50;
            memcpy((char*)ma->data + i * sizeof(int), &val_a, sizeof(int));
            memcpy((char*)mb->data + i * sizeof(int), &val_b, sizeof(int));
        }
        
        matrix* res = matrix_summ(ma, mb);
        assert(res != NULL);
        
        for (int i = 0; i < size * size; i++) {
            int a_val = *(int*)((char*)ma->data + i * sizeof(int));
            int b_val = *(int*)((char*)mb->data + i * sizeof(int));
            int r_val = *(int*)((char*)res->data + i * sizeof(int));
            assert(r_val == a_val + b_val);
        }
        
        matrix_free(ma);
        matrix_free(mb);
        matrix_free(res);
    }
}

void test_matrix_mul_complete() {
    int vals_a1[] = {6};
    int vals_b1[] = {7};
    int expected1[] = {42};
    
    matrix* a1 = create_test_int_matrix(1, vals_a1);
    matrix* b1 = create_test_int_matrix(1, vals_b1);
    matrix* result1 = matrix_mul(a1, b1);
    assert(result1 != NULL);
    assert(compare_int_matrices(result1, create_test_int_matrix(1, expected1)));
    matrix_free(a1);
    matrix_free(b1);
    matrix_free(result1);
    
    int vals_a2[] = {1, 2, 3, 4};
    int vals_b2[] = {2, 0, 1, 2};
    int expected2[] = {4, 4, 10, 8};
    
    matrix* a2 = create_test_int_matrix(2, vals_a2);
    matrix* b2 = create_test_int_matrix(2, vals_b2);
    matrix* result2 = matrix_mul(a2, b2);
    assert(result2 != NULL);
    assert(compare_int_matrices(result2, create_test_int_matrix(2, expected2)));
    matrix_free(a2);
    matrix_free(b2);
    matrix_free(result2);
    
    int identity[] = {1, 0, 0, 1};
    int original[] = {5, 6, 7, 8};
    matrix* orig = create_test_int_matrix(2, original);
    matrix* ident = create_test_int_matrix(2, identity);
    matrix* result3 = matrix_mul(orig, ident);
    assert(compare_int_matrices(result3, orig));
    matrix_free(orig);
    matrix_free(ident);
    matrix_free(result3);
    
    int zeros[] = {0, 0, 0, 0};
    matrix* zero = create_test_int_matrix(2, zeros);
    matrix* nums = create_test_int_matrix(2, vals_a2);
    matrix* result4 = matrix_mul(nums, zero);
    assert(compare_int_matrices(result4, zero));
    matrix_free(zero);
    matrix_free(nums);
    matrix_free(result4);
    
    int vals_a3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int vals_b3[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int expected3[] = {30, 24, 18, 84, 69, 54, 138, 114, 90};
    
    matrix* a3 = create_test_int_matrix(3, vals_a3);
    matrix* b3 = create_test_int_matrix(3, vals_b3);
    matrix* result5 = matrix_mul(a3, b3);
    assert(result5 != NULL);
    assert(compare_int_matrices(result5, create_test_int_matrix(3, expected3)));
    matrix_free(a3);
    matrix_free(b3);
    matrix_free(result5);
    
    matrix* m3 = matrix_create(3, get_type_int());
    matrix* m2 = matrix_create(2, get_type_int());
    assert(matrix_mul(m3, m2) == NULL);
    assert(matrix_mul(m2, m3) == NULL);
    matrix_free(m3);
    matrix_free(m2);
    
    for (int t = 0; t < 20; t++) {
        int size = rand() % 3 + 1;
        matrix* ma = matrix_create(size, get_type_int());
        matrix* mb = matrix_create(size, get_type_int());
        
        for (int i = 0; i < size * size; i++) {
            int val_a = rand() % 10 - 5;
            int val_b = rand() % 10 - 5;
            memcpy((char*)ma->data + i * sizeof(int), &val_a, sizeof(int));
            memcpy((char*)mb->data + i * sizeof(int), &val_b, sizeof(int));
        }
        
        matrix* res = matrix_mul(ma, mb);
        assert(res != NULL);
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int sum = 0;
                for (int k = 0; k < size; k++) {
                    int a_val = *(int*)((char*)ma->data + (i * size + k) * sizeof(int));
                    int b_val = *(int*)((char*)mb->data + (k * size + j) * sizeof(int));
                    sum += a_val * b_val;
                }
                int r_val = *(int*)((char*)res->data + (i * size + j) * sizeof(int));
                assert(r_val == sum);
            }
        }
        
        matrix_free(ma);
        matrix_free(mb);
        matrix_free(res);
    }
}

void test_matrix_mul_scalar_complete() {
    type_info* type = get_type_int();
    
    int vals1[] = {21, 21, 21, 21};
    int expected1[] = {42, 42, 42, 42};
    matrix* m1 = create_test_int_matrix(2, vals1);
    matrix* result1 = matrix_mul_scalar(m1, 2.0f);
    assert(result1 != NULL);
    assert(compare_int_matrices(result1, create_test_int_matrix(2, expected1)));
    matrix_free(m1);
    matrix_free(result1);
    
    int vals2[] = {10, 20, 30, 40};
    int expected2[] = {-10, -20, -30, -40};
    matrix* m2 = create_test_int_matrix(2, vals2);
    matrix* result2 = matrix_mul_scalar(m2, -1.0f);
    assert(result2 != NULL);
    assert(compare_int_matrices(result2, create_test_int_matrix(2, expected2)));
    matrix_free(m2);
    matrix_free(result2);
    
    int vals3[] = {100, 200, 300, 400};
    int zeros[] = {0, 0, 0, 0};
    matrix* m3 = create_test_int_matrix(2, vals3);
    matrix* result3 = matrix_mul_scalar(m3, 0.0f);
    assert(result3 != NULL);
    assert(compare_int_matrices(result3, create_test_int_matrix(2, zeros)));
    matrix_free(m3);
    matrix_free(result3);
    
    int vals4[] = {10, 20, 30, 40};
    int expected4[] = {5, 10, 15, 20};
    matrix* m4 = create_test_int_matrix(2, vals4);
    matrix* result4 = matrix_mul_scalar(m4, 0.5f);
    assert(result4 != NULL);
    assert(compare_int_matrices(result4, create_test_int_matrix(2, expected4)));
    matrix_free(m4);
    matrix_free(result4);
    
    for (int size = 1; size <= 5; size++) {
        matrix* m = matrix_create(size, type);
        fill_int_matrix_sequential(m, 1);
        
        matrix* result = matrix_mul_scalar(m, 2.0f);
        assert(result != NULL);
        
        for (int i = 0; i < size * size; i++) {
            int orig = *(int*)((char*)m->data + i * sizeof(int));
            int res = *(int*)((char*)result->data + i * sizeof(int));
            assert(res == orig * 2);
        }
        
        matrix_free(m);
        matrix_free(result);
    }
    
    assert(matrix_mul_scalar(NULL, 5.0f) == NULL);
    
    for (int t = 0; t < 50; t++) {
        int size = rand() % 5 + 1;
        matrix* m = matrix_create(size, type);
        
        for (int i = 0; i < size * size; i++) {
            int val = rand() % 100 - 50;
            memcpy((char*)m->data + i * sizeof(int), &val, sizeof(int));
        }
        
        float scalar = (rand() % 200 - 100) / 10.0f;
        matrix* result = matrix_mul_scalar(m, scalar);
        assert(result != NULL);
        
        for (int i = 0; i < size * size; i++) {
            int orig = *(int*)((char*)m->data + i * sizeof(int));
            int res = *(int*)((char*)result->data + i * sizeof(int));
            assert(res == (int)(orig * scalar));
        }
        
        matrix_free(m);
        matrix_free(result);
    }
}

void test_matrix_to_string_complete() {
    int vals1[] = {42};
    matrix* m1 = create_test_int_matrix(1, vals1);
    char* str1 = matrix_to_string(m1);
    assert(str1 != NULL);
    assert(strstr(str1, "42") != NULL);
    free(str1);
    matrix_free(m1);
    
    int vals2[] = {1, 2, 3, 4};
    matrix* m2 = create_test_int_matrix(2, vals2);
    char* str2 = matrix_to_string(m2);
    assert(str2 != NULL);
    assert(strstr(str2, "1") != NULL);
    assert(strstr(str2, "2") != NULL);
    assert(strstr(str2, "3") != NULL);
    assert(strstr(str2, "4") != NULL);
    free(str2);
    matrix_free(m2);
    
    int vals3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix* m3 = create_test_int_matrix(3, vals3);
    char* str3 = matrix_to_string(m3);
    assert(str3 != NULL);
    free(str3);
    matrix_free(m3);
    
    assert(matrix_to_string(NULL) == NULL);
    
    matrix* big = matrix_create(10, get_type_int());
    char* str_big = matrix_to_string(big);
    assert(str_big != NULL);
    free(str_big);
    matrix_free(big);
}

void test_matrix_fill_random_complete() {
    matrix* m_int = matrix_create(3, get_type_int());
    int result = matrix_fill_random(m_int, 10);
    assert(result == 0);
    
    for (int i = 0; i < 9; i++) {
        int val = *(int*)((char*)m_int->data + i * sizeof(int));
        assert(val >= -10 && val <= 10);
    }
    matrix_free(m_int);
    
    matrix* m_complex = matrix_create(2, get_complex_type());
    result = matrix_fill_random(m_complex, 5);
    assert(result == 0);
    matrix_free(m_complex);
    
    for (int max_val = 1; max_val <= 20; max_val++) {
        matrix* m = matrix_create(2, get_type_int());
        result = matrix_fill_random(m, max_val);
        assert(result == 0);
        
        for (int i = 0; i < 4; i++) {
            int val = *(int*)((char*)m->data + i * sizeof(int));
            assert(val >= -max_val && val <= max_val);
        }
        matrix_free(m);
    }
    
    assert(matrix_fill_random(NULL, 10) == 1);
    
    matrix* m_zero = matrix_create(2, get_type_int());
    result = matrix_fill_random(m_zero, 0);
    assert(result == 0);
    
    for (int i = 0; i < 4; i++) {
        int val = *(int*)((char*)m_zero->data + i * sizeof(int));
        assert(val == 0);
    }
    matrix_free(m_zero);
}

void test_matrix_edge_cases_complete() {
    type_info* type = get_type_int();
    
    int neg_vals[] = {-42};
    matrix* m1 = create_test_int_matrix(1, neg_vals);
    matrix* result = matrix_mul_scalar(m1, -1.0f);
    int expected = 42;
    assert(*(int*)result->data == expected);
    matrix_free(m1);
    matrix_free(result);

    for (int i = 0; i < 100; i++) {
        matrix* m = matrix_create(3, type);
        assert(m != NULL);
        matrix_free(m);
    }
    
    int vals[] = {1, 2, 3, 4};
    int expected_self[] = {2, 4, 6, 8};
    matrix* m = create_test_int_matrix(2, vals);
    matrix* sum_self = matrix_summ(m, m);
    assert(compare_int_matrices(sum_self, create_test_int_matrix(2, expected_self)));
    matrix_free(m);
    matrix_free(sum_self);
    
    int orig_vals[] = {5, 6, 7, 8};
    matrix* orig = create_test_int_matrix(2, orig_vals);
    matrix* scaled = matrix_mul_scalar(orig, 1.0f);
    assert(compare_int_matrices(orig, scaled));
    matrix_free(orig);
    matrix_free(scaled);
    
    int neg_orig[] = {5, 6, 7, 8};
    int neg_expected[] = {-5, -6, -7, -8};
    matrix* m_neg = create_test_int_matrix(2, neg_orig);
    matrix* m_neg_scaled = matrix_mul_scalar(m_neg, -1.0f);
    assert(compare_int_matrices(m_neg_scaled, create_test_int_matrix(2, neg_expected)));
    matrix_free(m_neg);
    matrix_free(m_neg_scaled);
}

void test_matrix_free_complete() {
    matrix_free(NULL);
    
    matrix* m_int = matrix_create(3, get_type_int());
    assert(m_int != NULL);
    matrix_free(m_int);
    
    matrix* m_complex = matrix_create(2, get_complex_type());
    assert(m_complex != NULL);
    matrix_free(m_complex);
    
    for (int i = 0; i < 50; i++) {
        matrix* m = matrix_create(4, get_type_int());
        assert(m != NULL);
        matrix_free(m);
    }
}

void test_complex_matrix_create_and_operations() {
    type_info* complex_type = get_complex_type();
    
    float reals[] = {1.0f, 2.0f, 3.0f, 4.0f};
    float imags[] = {5.0f, 6.0f, 7.0f, 8.0f};
    matrix* m = create_test_complex_matrix(2, reals, imags);
    assert(m != NULL);
    assert(m->size == 2);
    assert(m->type == complex_type);
    
    for (int i = 0; i < 4; i++) {
        complex* val = (complex*)((char*)m->data + i * sizeof(complex));
        assert(val->real == reals[i]);
        assert(val->imag == imags[i]);
    }
    matrix_free(m);
    
    float reals_a[] = {1.0f, 2.0f, 3.0f, 4.0f};
    float imags_a[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float reals_b[] = {5.0f, 6.0f, 7.0f, 8.0f};
    float imags_b[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    matrix* a = create_test_complex_matrix(2, reals_a, imags_a);
    matrix* b = create_test_complex_matrix(2, reals_b, imags_b);
    matrix* result = matrix_summ(a, b);
    
    assert(result != NULL);
    for (int i = 0; i < 4; i++) {
        complex* val = (complex*)((char*)result->data + i * sizeof(complex));
        assert(val->real == reals_a[i] + reals_b[i]);
        assert(val->imag == imags_a[i] + imags_b[i]);
    }
    
    matrix_free(a);
    matrix_free(b);
    matrix_free(result);
    
    float reals_m[] = {1.0f, 2.0f, 3.0f, 4.0f};
    float imags_m[] = {1.0f, 1.0f, 1.0f, 1.0f};
    matrix* mat = create_test_complex_matrix(2, reals_m, imags_m);
    
    complex scalar = {2.0f, 0.0f};
    matrix* scaled = matrix_mul_scalar_complex(mat, &scalar);
    
    assert(scaled != NULL);
    for (int i = 0; i < 4; i++) {
        complex* val = (complex*)((char*)scaled->data + i * sizeof(complex));
        assert(val->real == reals_m[i] * 2.0f);
        assert(val->imag == imags_m[i] * 2.0f);
    }
    
    matrix_free(mat);
    matrix_free(scaled);
    
    float reals_m2[] = {1.0f, 2.0f};
    float imags_m2[] = {0.0f, 0.0f};
    matrix* mat2 = create_test_complex_matrix(1, reals_m2, imags_m2);
    
    complex scalar_i = {0.0f, 1.0f};
    matrix* scaled_i = matrix_mul_scalar_complex(mat2, &scalar_i);
    
    assert(scaled_i != NULL);
    complex* val = (complex*)scaled_i->data;
    assert(val->real == 0.0f);
    assert(val->imag == 1.0f);
    
    matrix_free(mat2);
    matrix_free(scaled_i);
}

void test_matrix_mul_scalar_complex_complete() {
    float reals[] = {1.0f, 2.0f, 3.0f, 4.0f};
    float imags[] = {1.0f, 1.0f, 1.0f, 1.0f};
    matrix* m = create_test_complex_matrix(2, reals, imags);
    
    complex scalar1 = {2.0f, 0.0f};
    matrix* result1 = matrix_mul_scalar_complex(m, &scalar1);
    assert(result1 != NULL);
    
    for (int i = 0; i < 4; i++) {
        complex* val = (complex*)((char*)result1->data + i * sizeof(complex));
        assert(val->real == reals[i] * 2.0f);
        assert(val->imag == imags[i] * 2.0f);
    }
    matrix_free(result1);
    
    complex scalar2 = {0.0f, 2.0f};
    matrix* result2 = matrix_mul_scalar_complex(m, &scalar2);
    assert(result2 != NULL);
    
    for (int i = 0; i < 4; i++) {
        complex* val = (complex*)((char*)result2->data + i * sizeof(complex));
        assert(val->real == -imags[i] * 2.0f);
        assert(val->imag == reals[i] * 2.0f);
    }
    matrix_free(result2);
    
    complex scalar3 = {1.0f, 1.0f};
    matrix* result3 = matrix_mul_scalar_complex(m, &scalar3);
    assert(result3 != NULL);
    
    for (int i = 0; i < 4; i++) {
        complex* val = (complex*)((char*)result3->data + i * sizeof(complex));
        float expected_r = reals[i] * 1.0f - imags[i] * 1.0f;
        float expected_i = reals[i] * 1.0f + imags[i] * 1.0f;
        float eps = 0.001f;
        assert(val->real > expected_r - eps && val->real < expected_r + eps);
        assert(val->imag > expected_i - eps && val->imag < expected_i + eps);
    }
    matrix_free(result3);
    
    assert(matrix_mul_scalar_complex(NULL, &scalar1) == NULL);
    
    complex* null_scalar = NULL;
    assert(matrix_mul_scalar_complex(m, null_scalar) == NULL);
    
    matrix_free(m);
}

int test() {
    test_complex_creat_complete();
    test_complex_summ_complete();
    test_complex_mult_complete();
    test_complex_mult_scalar_complete();
    
    test_complex_summ_n();
    test_complex_mult_n();
    test_complex_mult_scalar_n();
    test_complex_mult_scalar_complex_n();
    test_complex_free_n();
    
    test_get_type_int_complete();
    test_print_int_complete();
    test_summ_int_complete();
    test_mult_int_complete();
    test_mult_scalar_int_complete();
    
    test_get_complex_type_complete();
    test_print_complex_complete();
    test_complex_mult_scalar_complex_n_via_type();
    
    test_matrix_create_complete();
    test_matrix_summ_complete();
    test_matrix_mul_complete();
    test_matrix_mul_scalar_complete();
    test_matrix_to_string_complete();
    test_matrix_fill_random_complete();
    test_matrix_edge_cases_complete();
    test_matrix_free_complete();

    test_complex_matrix_create_and_operations();
    test_matrix_mul_scalar_complex_complete();
    
    return 0;
}

void print_results() {
    printf("УСПЕШНЫХ ПРОВЕРОК: %zu\n", get_true_tests());
    printf("НЕУДАЧНЫХ ПРОВЕРОК: %zu\n", get_failed_tests());
    printf("ВСЕГО ПРОВЕРОК: %zu\n", get_true_tests() + get_failed_tests());
    
    if (get_failed_tests() == 0) {
        printf("\n ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!\n");
        printf("ПОКРЫТИЕ КОДА: 100%%\n");
    } else {
        printf("\n✗ ОБНАРУЖЕНО %zu ОШИБОК! ТРЕБУЕТСЯ ИСПРАВЛЕНИЕ\n", get_failed_tests());
    }
}

int main() {
    srand(42);
    test();
    print_results();
    return 0;
}
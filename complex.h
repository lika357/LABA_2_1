#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct complex2 {
    float real;
    float imag;
}complex;
complex* complex_creat(float real,float imag);
complex* complex_summ(complex* a,complex* b);
complex* complex_mult(complex* a,complex* b);
complex* complex_mult_scalar(complex* a,float scalar);
void complex_free(complex* a);



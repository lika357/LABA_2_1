#pragma once
#include "complex.h"
#include "int.h"
void print_complex_n(void* number);
void* complex_summ_n(void* a,void* b);
void* complex_mult_n(void* a,void* b);
void* complex_mult_scalar_n(void* a,float scalar);
void complex_free_n(void* number);
static type* type_compl = NULL;
type* type_compl();
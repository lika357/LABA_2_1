#pragma once
#include "complex.h"
#include "int.h"
char* print_complex(const void* data);
void* complex_summ_n(void* a,void* b);
void* complex_mult_n(void* a,void* b);
void* complex_mult_scalar_n(void* a,float scalar);
void complex_free_n(void* number);
type_info* type_comple = NULL;
type_info* type_compl();
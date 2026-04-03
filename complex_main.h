#pragma once

#include "type_info.h"
#include "complex.h"

extern type_info* type_compl;

char* print_complex(const void* data);
void* complex_summ_n(void* a, void* b);
void* complex_mult_n(void* a, void* b);
void* complex_mult_scalar_n(void* a, float scalar);
void* complex_mult_scalar_complex_n(void* a, void* b);
void complex_free_n(void* data);
type_info* get_complex_type();
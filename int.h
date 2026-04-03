#pragma once

#include "type_info.h"

extern type_info* type_int;

void* summ_int(void* a, void* b);
void* mult_int(void* a, void* b);
void* mult_scalar_int(void* a, float scalar);
void* mult_scalar_complex_int(void* a, void* scalar);
char* print_int(const void* data);
void free_int(void* data);
type_info* get_type_int();
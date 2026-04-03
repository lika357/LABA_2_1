#pragma once
#include <stdio.h>
#include <stdlib.h>
char* print_int(const void* number);
void* summ_int(void* a,void* b);
void* mult_int(void* a,void* b);
void* mult_scalar_int(void* a,int scalar);
void* mult_scalar_complex_int(void* a,void* b);
void free_int(void* num);
typedef struct{
    size_t size; 
    char* (*print)(const void* number);
    void* (*summ)(void* a,void* b);
    void* (*mult)(void* a,void* b);
    void* (*mult_scalar)(void* a,int scalar);
    void* (*mult_scalar_complex)(void* a,int scalar);
    void (*free)(void* num);
}type_info;
type_info* type_int = NULL;
type_info* type_int();
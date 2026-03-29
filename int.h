#pragma once
#include <stdio.h>
#include <stdlib.h>
void print_int(void* number);
void* summ_int(void* a,void* b);
void* summ_mult(void* a,void* b);
void* summ_mult_scalar(void* a,int scalar);
void free_int(void* num);
typedef struct{
    void (*print)(void* number);
    void* (*summ)(void* a,void* b);
    void* (*mult)(void* a,void* b);
    void* (*mult_scalar)(void* a,int scalar);
    void (*free)(void* num);
}type_info;
type_info* type_int = NULL;
type_info* type_int();
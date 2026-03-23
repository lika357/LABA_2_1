#pragma once
#include <stdio.h>
#include <stdlib.h>
void print_int(void* number);
void* summ_int(void* a,void* b);
void* summ_mult(void* a,void* b);
void* summ_mult_scalar(void* a,int scalar);
void free_int(void* num);
struct{
    void (*print)(void* number);
    void* (*summ)(void* a,void* b);
    void* (*mult)(void* a,void* b);
    void* (*mult_scalar)(void* a,int scalar);
    void (*free)(void* num);
}type;
static type* type_int = NULL;
type* type_int();
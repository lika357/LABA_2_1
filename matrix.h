#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int real;
    int imag;
}complex;
int** creat_matrix_int(int size);
void fill_matrix_random(int** matrix,int size);
int fill_matrix(int** matrix,int size);
void print_matrix(int** matrix,int size);
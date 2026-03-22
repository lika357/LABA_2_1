#pragma once
#include <stdio.h>
#include <stdlib.h>
int** creat_matrix_int(int size);
void fill_matrix_random(int** matrix,int size);
int fill_matrix(int** matrix,int size);
void print_matrix(int** matrix,int size);
int** summ_matrix(int** a,int** b,int size);
int** mult_matrix(int** a,int** b,int size);
int** mult_matrix_scalar(int** matrix,int size,int scalar);
void free_matrix(int** matrix,int size);

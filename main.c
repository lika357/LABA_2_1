#include "matrix.h"
#define rand 0
#define man 1
#define scalar 3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int c;
    int size;
    int** a = NULL;
    int** b = NULL;
    int** result = NULL;
    char v;
    srand(time(NULL));
    printf("0 рандомно , 1 с клавиатуры\n");
    if (scanf("%d%c", &c,&v) == 2 && v=='\n') {
        printf("введите размер матрицы ");
        if (scanf("%d%c", &size,&v) != 2 || size <= 0 || v!='\n') {
            printf("неверный размер матрицы\n");
            return 1;
        }
        a = creat_matrix_int(size);
        b = creat_matrix_int(size);
        if (a == NULL || b == NULL) {
            printf("ошибка создания матрицы\n");
            return 1;
        }
        printf("первая матрица\n");
        if (c == rand) {
            fill_matrix_random(a, size);
            printf("случайные числа\n");
        } 
        else if (c == man) {
            if (fill_matrix(a, size) != 0 ) {
                printf("ошибка ввода матрицы\n");
                return 1;
            }
            printf("матрица введена:\n");
        }
        else {
            printf("не то введено\n");
            free(a);
            return 1;
        }
        printf("вторая матрица\n");
        if (c == rand) {
            fill_matrix_random(b, size);
            printf("случайные числа\n");
        } 
        else if (c == man) {
            if (fill_matrix(b, size) != 0 ) {
                printf("ошибка ввода матрицы\n");
                return 1;
            }
            printf("матрица введена:\n");
        }
        else {
            printf("не то введено\n");
            free(a);
            return 1;
        }
        printf("матрица 1\n");
        print_matrix(a, size);
         printf("матрица 2\n");
        print_matrix(b, size);

        result=summ_matrix(a,b,size);
        printf("сложение матриц\n");
        print_matrix(result, size);
        free_matrix(result,size);

        result=mult_matrix(a,b,size);
        printf("умножение матриц\n");
        print_matrix(result, size);
        free_matrix(result,size);

        result=mult_matrix_scalar(a,size,scalar);
        printf("умножение матрицы на скаляр\n");
        print_matrix(result, size);
        free_matrix(result,size);

        
    }
    else {
        printf("ошибка ввода\n");
        return 1;
    }
    
    return 0;
}

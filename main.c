#include "matrix.h"
#define rand 0
#define man 1
#include <stdio.h>
#include <stdlib.h>

int main() {
    int c;
    int size;
    int** matrix = NULL;
    char v;
    
    if (scanf("%d%c", &c,&v) == 2 && v=='\n') {
        printf("введите размер матрицы ");
        if (scanf("%d", &size) != 1 || size <= 0) {
            printf("неверный размер матрицы\n");
            return 1;
        }
        matrix = creat_matrix_int(size);
        if (matrix == NULL) {
            printf("ошибка создания матрицы\n");
            return 1;
        }
        if (c == rand) {
            fill_matrix_random(matrix, size);
            printf("случайные числа\n");
        } 
        else if (c == man) {
            if (fill_matrix(matrix, size) != 0) {
                printf("ошибка ввода матрицы\n");
                return 1;
            }
            printf("матрица введена:\n");
        }
        else {
            printf("не то введено\n");
            free(matrix);
            return 1;
        }
        
        print_matrix(matrix, size);
    
        for (int i = 0; i < size; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
    else {
        printf("ошибка ввода\n");
        return 1;
    }
    
    return 0;
}
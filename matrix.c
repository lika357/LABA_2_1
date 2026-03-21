#include "matrix.h"
#include <time.h>
#define max_number 100
int** creat_matrix_int(int size){
    int** matrix=(int**)calloc(size,sizeof(int*));
    if(matrix==NULL){
        printf("память не выделилась\n");
        return NULL;
    }
    for(size_t i=0;i<size;i++){
         matrix[i]=(int*)calloc(size,sizeof(int));
        if(matrix[i]==NULL){
            for(size_t j=0;j<i;j++){
                free(matrix[j]);
            }
            printf("память не выделилась\n");
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}
void fill_matrix_random(int** matrix,int size){
    srand(time(NULL));
    for(size_t i=0;i<size;i++){
        for(size_t j=0;j<size;j++){
            matrix[i][j]=rand()%(2*(max_number+1))-max_number;
        }
    }
}
int fill_matrix(int** matrix,int size){
    char c;
    printf("введите значения матрицы %dx%d не больше %d и не меньше -%d\n",size,size,max_number,max_number);
    for(size_t i=0;i<size;i++){
        for(size_t j=0;j<size;j++){
            printf("элемент %zu строка %zu место в строке\n",i+1,j+1);
            if(scanf("%d%c",&matrix[i][j],&c)!=2 || c!='\n' || matrix[i][j]> max_number || matrix[i][j]<(-max_number) ){
                printf("введено неправильное значение\n");
                return 1;
            }
        }
    }
    return 0;
}
void print_matrix(int** matrix,int size){
    for(size_t i=0;i<size;i++){
        for(size_t j=0;j<size;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}


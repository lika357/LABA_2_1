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
int** summ_matrix(int** a,int** b,int size){
    int** result =  creat_matrix_int(size);
    for(size_t i=0;i<size;i++){
        for(size_t j=0;j<size;j++){
            result[i][j]=a[i][j]+b[i][j];
        }
    }
    return result;
}
int** mult_matrix(int** a,int** b,int size){
    int** result =  creat_matrix_int(size);
    for(size_t i=0;i<size;i++){
        for(size_t j=0;j<size;j++){
            int summ=0;
            for(size_t k=0;k<size;k++){
                summ+=a[i][k]*b[k][j];
            }
            result[i][j]=summ;
        }
    }
    return result;
}
int** mult_matrix_scalar(int** matrix,int size,int scalar){
     int** result =  creat_matrix_int(size);
      for(size_t i=0;i<size;i++){
        for(size_t j=0;j<size;j++){
            result[i][j]=scalar*matrix[i][j];
        }
      }
      return result;
}
void free_matrix(int** matrix,int size){
    if(matrix==NULL){
        return;
    }
    for(size_t i;i<size;i++){
        free(matrix[i]);
    }
    free(matrix);
}
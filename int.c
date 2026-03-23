#include <stdio.h>
#include <stdlib.h>
#include "int.h"
void print_int(void* number){
    int* c = (int*)number;
    printf("%d",*number);
}
void* summ_int(void* a,void* b){
    int* num1 = (int*)a;
    int* num2 = (int*)b;
    int* result = (int*)calloc(1,sizeof(int));
    if(result!=NULL){
        *result = *num1 + *num2;
        return result;
    }
    else{
        return NULL;
    }

}
void* summ_mult(void* a,void* b){
    int* num1 = (int*)a;
    int* num2 = (int*)b;
    int* result = (int*)calloc(1,sizeof(int));
    if(result!=NULL){
        *result = *num1 * *num2;
        return result;
    }
    else{
        return NULL;
    }
}
void* summ_mult_scalar(void* a,float scalar){
    int* num = (int*)a;
    int* result = (int*)calloc(1,sizeof(int));
    if(result!=NULL){
        *result = (int)(scalar * *num);
        return result;
    }
    else{
        return NULL;
    }

}
void free_int(void* num){
    free(num);
}
type* type_int(){
    if(type_int==NULL){
        type* type_int = (type*)malloc(sizeof(type));
    }
    type_int -> print = print_int;
    type_int -> summ = summ_int;
    type_int -> mult = mult_int;
    type_int -> mult_scalar = mult_scalar_int;
    type_int -> free = free_int;
    return type_int;
}

#include <stdio.h>
#include <stdlib.h>
#include "complex.h"
#include "complex_main.h"
#include "int.h"
type_info* type_int = NULL;
char* print_int(const void* number){
    if (number==NULL){
        return NULL;
    }
    int val = *(const int*)number;
    char* str = calloc(32, sizeof(char)); 
    if (str==NULL){
         return NULL;
    }
    
    if (val < 0) {
        snprintf(str, 32, "%d", val);
    } else {
        snprintf(str, 32, " %d", val);  
    }
    return str;
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
void* mult_int(void* a,void* b){
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
void* mult_scalar_int(void* a,float scalar){
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
void* mult_scalar_complex_int(void* a,void* b){
    if(a==NULL || b==NULL){
        return NULL;
    }
    complex* res=calloc(1,sizeof(complex));
    if(res==NULL){
        return NULL;
    }
    int val = *(const int*)a;
    complex* num=(complex*)b;
    res->real=val*num->real;
    res->imag=val*num->imag;
    return res;
}
void free_int(void* num){
    free(num);
}
type_info* get_type_int(){
    if(type_int==NULL){
        type_info* type_int = (type_info*)malloc(sizeof(type_info));
    }
    type_int -> size = sizeof(int);
    type_int -> mult_scalar_complex = mult_scalar_complex_int;
    type_int -> print = print_int;
    type_int -> summ = summ_int;
    type_int -> mult = mult_int;
    type_int -> mult_scalar = mult_scalar_int;
    type_int -> free = free_int;
    return type_int;
}

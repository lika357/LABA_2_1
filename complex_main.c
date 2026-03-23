#include "complex_main.h"
#include "complex.h"
void print_complex_n(void* number){
    complex* a=(complex*)number;
    complex_print(a);
}
void* complex_summ_n(void* a,void* b){
    complex* num1=(complex*)a;
    complex* num2=(complex*)b;
    return complex_summ(num1,num2);
}
void* complex_mult_n(void* a,void* b){
    complex* num1=(complex*)a;
    complex* num2=(complex*)b;
    return complex_mult(num1,num2);
}
void* complex_mult_scalar_n(void* a,float scalar){
    complex* num=(complex*)a;
    return complex_mult_scalar(num,scalar);
}
void complex_free_n(void* number){
    free(number);
}
type* type_compl(){
    if(type_compl==NULL){
        type* type_compl = (type*)malloc(sizeof(type));
    }
    type_compl -> print = print_complex_n;
    type_compl -> summ = complex_summ_n;
    type_compl -> mult = complex_mult_n;
    type_compl -> mult_scalar = complex_mult_scalar_n;
    type_compl -> free = complex_free_n;
    return type_compl;
}


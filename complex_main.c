#include "complex_main.h"
#include "complex.h"
#include "type_info.h"
type_info* type_compl = NULL;
char* print_complex(const void* data){
    if (data==NULL) {
        return NULL;
    }
    const complex* number = (const complex*)data;
    char* str = calloc(64, sizeof(char));
    if (str==NULL) {
        return NULL;
    }
    int len = 0;
    
    if (number->real < 0) {
        len += snprintf(str + len, 64 - len, "%.2f", number->real);
    } else {
        len += snprintf(str + len, 64 - len, " %.2f", number->real);
    }
    
    if (number->imag < 0) {
        len += snprintf(str + len, 64 - len, "%.2fi", number->imag);
    } else {
        len += snprintf(str + len, 64 - len, "+%.2fi", number->imag);
    }
    
    return str;
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
void* complex_mult_scalar_complex_n(void* a,void* b){
    if(a==NULL || b==NULL){
        return NULL;
    }
    complex* res=calloc(1,sizeof(complex));
    if(res==NULL){
        return NULL;
    }
    complex* num1=(complex*)a;
    complex* num2=(complex*)b;
    res->real = num1->real * num2->real - num1->imag * num2->imag;
    res->imag = num1->real * num2->imag + num1->imag * num2->real; 
    return res;
}
void complex_free_n(void* number){
    free(number);
}
type_info* get_complex_type(){
    if(type_compl==NULL){
        type_compl = (type_info*)malloc(sizeof(type_info));
    }
    if(type_compl!=NULL){
    type_compl -> size = sizeof(complex);
    type_compl -> print = print_complex;
    type_compl -> summ = complex_summ_n;
    type_compl -> mult = complex_mult_n;
    type_compl -> mult_scalar_complex = complex_mult_scalar_complex_n;
    type_compl -> mult_scalar = complex_mult_scalar_n;
    type_compl -> free = complex_free_n;
    }
    return type_compl;
}


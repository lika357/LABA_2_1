#include "complex.h"
complex* complex_creat(float real,float imag){
    complex* c=(complex*)calloc(1,sizeof(complex));
    if(c!=NULL){
    c -> real = real;
    c -> imag = imag;
    }
    else{
        printf("память не выделилась\n");
        return NULL;
    }
    return c;
}
complex* complex_summ(complex* a,complex* b){
    if(a!=NULL && b!=NULL){
        complex* result = complex_creat(a-> real + b-> real,a->imag + b->imag);
        return result;
    }
    else{
        return 1;
    }
}
complex* complex_mult(complex* a,complex* b){
    if(a!=NULL && b!=NULL){
        float new_r = a->real * b->real - a->imag * b->imag;
        float new_i = a->real * b->imag + a->imag * b->real;
        complex* result = complex_creat(new_r,new_i);
        return result;
    }
    else{
        return NULL;
    }

}
complex* complex_mult_scalar(complex* a,float scalar){
        if(a!=NULL){
        complex* result = complex_creat((a->real)*scalar,(a->imag)*scalar);
        return result;
    }
    else{
        return NULL;
    }
}
void complex_free(complex* a){
    if(a!=NULL){
    free(a);
    }
}



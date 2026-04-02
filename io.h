#pragma once 
#include "complex.h"
#include "complex_main.h"
#include "int.h"
#include "matrix1.h"
type_info* get_int_type();
type_info* get_complex_type();
int size(int max_size){
    int size;
    char c;
    if(scanf("%d%c",&size,&c)==2 && c=='\n'){
        return size;
    }

}


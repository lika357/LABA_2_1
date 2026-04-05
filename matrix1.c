#include "matrix1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void* element_pointer(void* data, int j, int k, int size, size_t elem_size) {
    int index = j * size + k;
    return (char*)data + index * elem_size;
}

matrix* matrix_create(int size, type_info* type) {
    if (size <= 0 || !type) {
        return NULL;
    }
    
    matrix* m = (matrix*)calloc(1, sizeof(matrix));
    if (!m) {
        return NULL;
    }
    
    int all_elements = size * size;
    m->data = calloc(all_elements, type->size);
    if (!m->data) {
        free(m);
        return NULL;
    }
    
    m->size = size;
    m->type = type; 
    
    return m;
}

void matrix_free(matrix* m) {
    if (!m) {
        return;
    } 
    if (m->data) {
        free(m->data);
    }
    free(m);
}

char* matrix_to_string(const matrix* m) {
    if (!m || !m->type || !m->type->print){ 
        return NULL;
    }
    int buf_size = 256 + m->size * m->size * 32;
    char* result = calloc(buf_size, sizeof(char));
    if (!result) {
        return NULL;
    }
    result[0] = '\0';
    
    char temp[64];
    snprintf(temp, sizeof(temp), "матрица %dx%d:\n", m->size, m->size);
    strcat(result, temp);
    
    for (int i = 0; i < m->size; i++) {
        strcat(result, "| ");
        for (int j = 0; j < m->size; j++) {
            void* elem = element_pointer(m->data, i, j, m->size, m->type->size);
            
            char* str = m->type->print(elem);
            if (str!=NULL) {
                strcat(result, str);
                strcat(result, " ");
                free(str);
            }
        }
        strcat(result, "|\n");
    }
    
    return result;
}

matrix* matrix_summ(matrix* a, matrix* b) {
    if (!a || !b || a->size != b->size || a->type != b->type) {
        return NULL;
    }
    
    int size = a->size;
    int all = size * size;

    matrix* result = matrix_create(size, a->type);
    if (!result) {
        return NULL;
    }

    for (int i = 0; i < all; i++) {
        void* elem_a = (char*)a->data + i * a->type->size;
        void* elem_b = (char*)b->data + i * b->type->size;
        void* res = (char*)result->data + i * result->type->size;
        
        void* summ = a->type->summ(elem_a, elem_b);  
        if (!summ) {
            matrix_free(result);
            return NULL;
        }
        
        memcpy(res, summ, result->type->size);
        a->type->free(summ); 
    }
    
    return result;
}

matrix* matrix_mul(matrix* a, matrix* b) {
    if (!a || !b || a->size != b->size || a->type != b->type) {
        return NULL;
    }
    
    int size = a->size;
    matrix* result = matrix_create(size, a->type);
    if (!result) {
        return NULL;
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            void* sum = NULL; 
            
            for (int k = 0; k < size; k++) {
                void* elem_a = element_pointer(a->data, i, k, size, a->type->size);
                void* elem_b = element_pointer(b->data, k, j, size, b->type->size);
                
                void* mul = a->type->mult(elem_a, elem_b); 
                if (!mul) {
                    if (sum!=NULL) {
                        a->type->free(sum);
                    }
                    matrix_free(result);  
                    return NULL;
                }

                if (k == 0) {
                    sum = mul;
                } else {
                    void* new_sum = a->type->summ(sum, mul);  
                    a->type->free(sum);
                    a->type->free(mul);
                    if (!new_sum) {
                        matrix_free(result);
                        return NULL;
                    }
                    sum = new_sum;
                }
            }
            
            void* res = element_pointer(result->data, i, j, size, result->type->size); 
            memcpy(res, sum, result->type->size);
            a->type->free(sum);
        }
    }
    
    return result;
}

matrix* matrix_mul_scalar(matrix* m, float scalar_val) { 
    if (!m) {
        return NULL;
    }
    
    int all = m->size * m->size;
    matrix* result = matrix_create(m->size, m->type);
    if (!result) {
        return NULL;
    }
    
    for (int i = 0; i < all; i++) {
        void* elem = (char*)m->data + i * m->type->size;
        void* res = (char*)result->data + i * result->type->size;
        
        void* scaled = m->type->mult_scalar(elem, scalar_val);  
        if (!scaled) {
            matrix_free(result);
            return NULL;
        }
        
        memcpy(res, scaled, result->type->size); 
        m->type->free(scaled);
    }
    
    return result;
}
matrix* matrix_mul_scalar_complex(matrix* m, void* scalar) {
    if (!m || !scalar || !m->type->mult_scalar_complex) {
        return NULL;
    }
    int all = m->size * m->size;
    matrix* result = matrix_create(m->size, m->type);
    if (!result) {
        return NULL;
    }
    for (int i = 0; i < all; i++) {
        void* elem = (char*)m->data + i * m->type->size;
        void* res = (char*)result->data + i * result->type->size;
        void* summ = m->type->mult_scalar_complex(elem, scalar);
        if (!summ) { 
            matrix_free(result);
            return NULL;
        }
        memcpy(res, summ, result->type->size);
        m->type->free(summ);
    }
    return result;
}
int matrix_fill_random(matrix* m, int max_val) {
    if (!m) {
        return 1;
    } 
    
    srand(time(NULL));
    int all = m->size * m->size;
    
    for (int i = 0; i < all; i++) {
        void* elem = (char*)m->data + i * m->type->size;  
        
        if (m->type == get_type_int()) {
            int val = rand() % (2 * max_val + 1) - max_val;
            memcpy(elem, &val, sizeof(int));
        }
        else if (m->type == get_complex_type()) {
            complex* comp = (complex*)malloc(sizeof(complex));
            comp->real = (float)(rand() % (2 * max_val + 1) - max_val);
            comp->imag = (float)(rand() % (2 * max_val + 1) - max_val);
            memcpy(elem, &comp, sizeof(complex));
            free(comp);
        }
    }
    
    return 0;
}

int matrix_fill_manual(matrix* m, int max_val) {
    if (!m) {
        return 1;
    }
    
    printf("введите значения матрицы %dx%d от -%d до %d:\n", m->size, m->size, max_val, max_val); 
    
    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            void* elem = element_pointer(m->data, i, j, m->size, m->type->size);
            
            if (m->type == get_type_int()) {
                int val;
                printf("[%d][%d] ",(int)i + 1,(int)j + 1);
                if (scanf("%d", &val) != 1 || val > max_val || val < -max_val) {
                    return 1;
                }
                memcpy(elem, &val, sizeof(int));
            }
            else if (m->type == get_complex_type()) {
                complex* comp = (complex*)malloc(sizeof(complex));
                printf("[%d][%d] действительная часть:",(int)i + 1,(int)j + 1);
                if (scanf("%f", &comp->real) != 1 || comp->real > max_val || comp->real < -max_val) {
                    return 1;
                }
                printf("[%d][%d] мнимая часть:",(int)i + 1,(int)j + 1);
                if (scanf("%f", &comp->imag) != 1 || comp->imag > max_val || comp->imag < -max_val) {
                    return 1;
                }
                memcpy(elem, &comp, sizeof(complex));
            }
        }
    }
    
    return 0;
}
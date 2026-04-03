#pragma once

#include <stddef.h>

typedef struct {
    size_t size;
    void* (*summ)(void* a, void* b);
    void* (*mult)(void* a, void* b);
    void* (*mult_scalar)(void* a, float scalar);
    void* (*mult_scalar_complex)(void* a, void* scalar);
    char* (*print)(const void* data);
    void (*free)(void* data);
} type_info;


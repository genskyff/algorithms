#ifndef ARRAY_H
#define ARRAY_H

#include "type.h"
#include <stddef.h>

typedef struct {
    elem_t *data;
    size_t  len;
} Array;

#define ARRAY(...)                                                             \
    ((Array){.data = (elem_t[]){__VA_ARGS__},                                  \
             .len  = sizeof((elem_t[]){__VA_ARGS__}) / sizeof(elem_t)})

#define INIT_ARRAY(_LEN) ((Array){.data = (elem_t[(_LEN)]){}, .len = (_LEN)})

void swap(Array *arr, size_t i, size_t j);

// [begin, end)
void show(Array arr);
void show_slice(Array arr, size_t begin, size_t end);

void copy(Array *dst, Array *src);
void copy_slice(Array *dst, size_t d_begin, size_t d_end, Array *src,
                size_t s_begin, size_t s_end);

void rotate_left(Array *arr, size_t n);
void rotate_left_slice(Array *arr, size_t begin, size_t end, size_t n);

void rotate_right(Array *arr, size_t n);
void rotate_right_slice(Array *arr, size_t begin, size_t end, size_t n);

#endif

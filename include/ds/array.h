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

void array_swap(Array *arr, size_t i, size_t j);

// [start, end)
void array_show(Array arr);
void array_show_slice(Array arr, size_t start, size_t end);

void array_copy(Array *dst, Array *src);
void array_copy_slice(Array *dst, size_t d_start, size_t d_end, Array *src,
                      size_t s_start, size_t s_end);

void array_rotate_left(Array *arr, size_t n);
void array_rotate_left_slice(Array *arr, size_t start, size_t end, size_t n);

void array_rotate_right(Array *arr, size_t n);
void array_rotate_right_slice(Array *arr, size_t start, size_t end, size_t n);

#endif

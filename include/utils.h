#ifndef UTILS_H
#define UTILS_H

#include "type.h"
#include <stdbool.h>
#include <stddef.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void swap(Array *arr, size_t i, size_t j);

// [begin, end)
void show(Array *arr);
void show_slice(Array *arr, size_t begin, size_t end);

void copy(Array *dst, Array *src);
void copy_slice(Array *dst, size_t d_begin, size_t d_end, Array *src,
                size_t s_begin, size_t s_end);

void rotate_left(Array *arr, size_t n);
void rotate_left_slice(Array *arr, size_t begin, size_t end, size_t n);

void rotate_right(Array *arr, size_t n);
void rotate_right_slice(Array *arr, size_t begin, size_t end, size_t n);

bool assert_eq(Array *left, Array *right);

#endif

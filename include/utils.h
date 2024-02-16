#ifndef UTILS_H
#define UTILS_H

#include "type.h"
#include <stdbool.h>
#include <stddef.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void swap(Array *arr, const size_t i, const size_t j);

// [begin, end)
void show(const Array *arr);
void show_slice(const Array *arr, const size_t begin, const size_t end);

void copy(Array *dst, const Array *src);
void copy_slice(Array *dst, const size_t d_begin, const size_t d_end,
                const Array *src, const size_t s_begin, const size_t s_end);

void rotate_left(Array *arr, const size_t n);
void rotate_left_slice(Array *arr, const size_t begin, const size_t end,
                       const size_t n);

void rotate_right(Array *arr, const size_t n);
void rotate_right_slice(Array *arr, const size_t begin, const size_t end,
                        const size_t n);

bool assert_eq(const Array *left, const Array *right);

#endif

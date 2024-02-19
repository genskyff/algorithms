#ifndef UTILS_H
#define UTILS_H

#include "type.h"
#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void swap(elem_t *arr, size_t i, size_t j);

// [start, end)
void show(FILE *stream, elem_t *arr, size_t len);
void show_slice(FILE *stream, elem_t *arr, size_t len, size_t start,
                size_t end);

void copy(elem_t *dst, size_t d_len, elem_t *src, size_t s_len);
void copy_slice(elem_t *dst, size_t d_len, size_t d_start, size_t d_end,
                elem_t *src, size_t s_len, size_t s_start, size_t s_end);

void move_left(elem_t *arr, size_t len, size_t n);
void move_left_slice(elem_t *arr, size_t len, size_t start, size_t end,
                     size_t n);

void move_right(elem_t *arr, size_t len, size_t n);
void move_right_slice(elem_t *arr, size_t len, size_t start, size_t end,
                      size_t n);

void rotate_left(elem_t *arr, size_t len, size_t n);
void rotate_left_slice(elem_t *arr, size_t len, size_t start, size_t end,
                       size_t n);

void rotate_right(elem_t *arr, size_t len, size_t n);
void rotate_right_slice(elem_t *arr, size_t len, size_t start, size_t end,
                        size_t n);

#endif

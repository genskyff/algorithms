#ifndef UTILS_H
#define UTILS_H

#include "type.h"
#include <stdbool.h>
#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void _swap(elem_t *arr, size_t i, size_t j);

// [start, end)
void _show(FILE *stream, elem_t *arr, size_t len);
void _show_slice(FILE *stream, elem_t *arr, size_t len, size_t start,
                 size_t end);

void _reverse(elem_t *arr, size_t len);
void _reverse_slice(elem_t *arr, size_t len, size_t start, size_t end);

bool _find(elem_t *arr, size_t len, elem_t e, size_t *i);
bool _find_slice(elem_t *arr, size_t len, size_t start, size_t end, elem_t e,
                size_t *i);

void _copy(elem_t *dst, size_t d_len, elem_t *src, size_t s_len);
void _copy_slice(elem_t *dst, size_t d_len, size_t d_start, size_t d_end,
                elem_t *src, size_t s_len, size_t s_start, size_t s_end);

void _move_left(elem_t *arr, size_t len, size_t n);
void _move_left_slice(elem_t *arr, size_t len, size_t start, size_t end,
                     size_t n);

void _move_right(elem_t *arr, size_t len, size_t n);
void _move_right_slice(elem_t *arr, size_t len, size_t start, size_t end,
                      size_t n);

void _rotate_left(elem_t *arr, size_t len, size_t n);
void _rotate_left_slice(elem_t *arr, size_t len, size_t start, size_t end,
                       size_t n);

void _rotate_right(elem_t *arr, size_t len, size_t n);
void _rotate_right_slice(elem_t *arr, size_t len, size_t start, size_t end,
                        size_t n);

#endif

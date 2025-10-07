#ifndef UTIL_H
#define UTIL_H

#include "type.h"
#include <stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SWAP(a, b)                                                             \
    do {                                                                       \
        elem_t _tmp = (a);                                                     \
        (a)         = (b);                                                     \
        (b)         = _tmp;                                                    \
    } while (0)

elem_t _min(elem_t *arr, size_t len);
elem_t _max(elem_t *arr, size_t len);
void   _swap(elem_t *arr, size_t i, size_t j);
void   _shuffle(elem_t *arr, size_t len);
void   _clear(elem_t *arr, size_t len);
void   _has_alloc_err(void *data, const char *location);
int    _cmp(const void *v1, const void *v2);
int    _cmp_str(const void *s1, const void *s2);

// [start, end)
void _show(FILE *stream, elem_t *arr, size_t len, const char *sep);
void _show_slice(FILE *stream, elem_t *arr, size_t len, size_t start,
                 size_t end, const char *sep);
void _show_list(FILE *stream, Node *node, Direction dir, const char *sep);

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

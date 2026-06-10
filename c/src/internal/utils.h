#ifndef ALG_INTERNAL_UTILS_H
#define ALG_INTERNAL_UTILS_H

#include "alg/ds/node.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define ALG_INTERNAL_MIN(a, b) ((a) < (b) ? (a) : (b))
#define ALG_INTERNAL_MAX(a, b) ((a) > (b) ? (a) : (b))
#define ALG_INTERNAL_SWAP(a, b)                                                \
    do {                                                                       \
        alg_elem_t alg_swap_tmp = (a);                                         \
        (a)                     = (b);                                         \
        (b)                     = alg_swap_tmp;                                \
    } while (0)

alg_elem_t alg_internal_min(alg_elem_t *arr, size_t len);
alg_elem_t alg_internal_max(alg_elem_t *arr, size_t len);
void       alg_internal_swap(alg_elem_t *arr, size_t i, size_t j);
void       alg_internal_shuffle(alg_elem_t *arr, size_t len);
void       alg_internal_clear(alg_elem_t *arr, size_t len);
void       alg_internal_has_alloc_err(void *data, const char *location);
int        alg_internal_cmp(const void *v1, const void *v2);
int        alg_internal_cmp_str(const void *s1, const void *s2);

// [start, end)
void alg_internal_show(FILE *stream, alg_elem_t *arr, size_t len,
                       const char *sep);
void alg_internal_show_slice(FILE *stream, alg_elem_t *arr, size_t len,
                             size_t start, size_t end, const char *sep);
void alg_internal_show_list(FILE *stream, AlgNode *node, AlgDirection dir,
                            const char *sep);

void alg_internal_reverse(alg_elem_t *arr, size_t len);
void alg_internal_reverse_slice(alg_elem_t *arr, size_t len, size_t start,
                                size_t end);

bool alg_internal_find(alg_elem_t *arr, size_t len, alg_elem_t e, size_t *i);
bool alg_internal_find_slice(alg_elem_t *arr, size_t len, size_t start,
                             size_t end, alg_elem_t e, size_t *i);

void alg_internal_copy(alg_elem_t *dst, size_t d_len, alg_elem_t *src,
                       size_t s_len);
void alg_internal_copy_slice(alg_elem_t *dst, size_t d_len, size_t d_start,
                             size_t d_end, alg_elem_t *src, size_t s_len,
                             size_t s_start, size_t s_end);

void alg_internal_move_left(alg_elem_t *arr, size_t len, size_t n);
void alg_internal_move_left_slice(alg_elem_t *arr, size_t len, size_t start,
                                  size_t end, size_t n);

void alg_internal_move_right(alg_elem_t *arr, size_t len, size_t n);
void alg_internal_move_right_slice(alg_elem_t *arr, size_t len, size_t start,
                                   size_t end, size_t n);

void alg_internal_rotate_left(alg_elem_t *arr, size_t len, size_t n);
void alg_internal_rotate_left_slice(alg_elem_t *arr, size_t len, size_t start,
                                    size_t end, size_t n);

void alg_internal_rotate_right(alg_elem_t *arr, size_t len, size_t n);
void alg_internal_rotate_right_slice(alg_elem_t *arr, size_t len, size_t start,
                                     size_t end, size_t n);

#endif

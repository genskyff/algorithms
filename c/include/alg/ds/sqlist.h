#ifndef ALG_SQLIST_H
#define ALG_SQLIST_H

#include "alg/core.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// data[0] is the first
// data[len - 1] is the last
typedef struct {
    alg_elem_t data[ALG_MAX_LEN];
    size_t     len;
} AlgSqList;

AlgSqList alg_sqlist_create(void);
AlgSqList alg_sqlist_init(size_t n, ...);
void      alg_sqlist_swap(AlgSqList *list, size_t i, size_t j);
void      alg_sqlist_reverse(AlgSqList *list);
void      alg_sqlist_show(FILE *stream, const AlgSqList *list);
void      alg_sqlist_clear(AlgSqList *list);
bool      alg_sqlist_is_empty(const AlgSqList *list);
bool      alg_sqlist_get(const AlgSqList *list, size_t i, alg_elem_t *e);
bool      alg_sqlist_first(const AlgSqList *list, alg_elem_t *e);
bool      alg_sqlist_last(const AlgSqList *list, alg_elem_t *e);
bool      alg_sqlist_set(AlgSqList *list, size_t i, alg_elem_t e);
bool      alg_sqlist_find(const AlgSqList *list, alg_elem_t e, size_t *i);
bool      alg_sqlist_insert(AlgSqList *list, size_t i, alg_elem_t e);
bool      alg_sqlist_push_front(AlgSqList *list, alg_elem_t e);
bool      alg_sqlist_push_back(AlgSqList *list, alg_elem_t e);
bool      alg_sqlist_del(AlgSqList *list, size_t i, alg_elem_t *e);
bool      alg_sqlist_pop_front(AlgSqList *list, alg_elem_t *e);
bool      alg_sqlist_pop_back(AlgSqList *list, alg_elem_t *e);

#endif

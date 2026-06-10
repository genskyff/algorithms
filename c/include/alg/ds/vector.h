#ifndef ALG_VECTOR_H
#define ALG_VECTOR_H

#include "alg/core.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define ALG_VEC_INIT_CAP      100
#define ALG_VEC_SHRINK_CAP    1000
#define ALG_VEC_LOW_FACTOR    0.25
#define ALG_VEC_GROWTH_FACTOR 2

// data[0] is the first
// data[len - 1] is the last
typedef struct {
    alg_elem_t *data;
    size_t      len;
    size_t      cap;
} AlgVec;

AlgVec alg_vec_create(void);
AlgVec alg_vec_create_with(size_t cap);
AlgVec alg_vec_init(size_t n, ...);
void   alg_vec_swap(AlgVec *v, size_t i, size_t j);
void   alg_vec_reverse(AlgVec *v);
void   alg_vec_show(FILE *stream, AlgVec *v);
void   alg_vec_clear(AlgVec *v);
bool   alg_vec_is_empty(AlgVec *v);
bool   alg_vec_get(AlgVec *v, size_t i, alg_elem_t *e);
bool   alg_vec_first(AlgVec *v, alg_elem_t *e);
bool   alg_vec_last(AlgVec *v, alg_elem_t *e);
bool   alg_vec_set(AlgVec *v, size_t i, alg_elem_t e);
bool   alg_vec_find(AlgVec *v, alg_elem_t e, size_t *i);
bool   alg_vec_insert(AlgVec *v, size_t i, alg_elem_t e);
bool   alg_vec_push_front(AlgVec *v, alg_elem_t e);
bool   alg_vec_push_back(AlgVec *v, alg_elem_t e);
bool   alg_vec_del(AlgVec *v, size_t i, alg_elem_t *e);
bool   alg_vec_pop_front(AlgVec *v, alg_elem_t *e);
bool   alg_vec_pop_back(AlgVec *v, alg_elem_t *e);
void   alg_vec_drop(AlgVec *v);

#endif

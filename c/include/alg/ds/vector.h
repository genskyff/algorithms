#ifndef ALG_VECTOR_H
#define ALG_VECTOR_H

#include "alg/type.h"
#include <stdbool.h>

#define INIT_CAP      100
#define SHRINK_CAP    1000
#define LOW_FACTOR    0.25
#define GROWTH_FACTOR 2

// data[0] is the first
// data[len - 1] is the last
typedef struct {
    elem_t *data;
    size_t  len;
    size_t  cap;
} Vec;

Vec  create(void);
Vec  create_with(size_t cap);
Vec  init(size_t n, ...);
void swap(Vec *v, size_t i, size_t j);
void reverse(Vec *v);
void show(FILE *stream, Vec *v);
void clear(Vec *v);
bool is_empty(Vec *v);
bool get(Vec *v, size_t i, elem_t *e);
bool first(Vec *v, elem_t *e);
bool last(Vec *v, elem_t *e);
bool set(Vec *v, size_t i, elem_t e);
bool find(Vec *v, elem_t e, size_t *i);
bool insert(Vec *v, size_t i, elem_t e);
bool push_front(Vec *v, elem_t e);
bool push_back(Vec *v, elem_t e);
bool del(Vec *v, size_t i, elem_t *e);
bool pop_front(Vec *v, elem_t *e);
bool pop_back(Vec *v, elem_t *e);
void drop(Vec *v);

#endif

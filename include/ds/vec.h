#ifndef VEC_H
#define VEC_H
#include "type.h"
#include <stdbool.h>
#include <stdio.h>

#define INIT_CAP     20
#define EXTEND_RATIO 2

typedef struct {
    elem_t *data;
    size_t  len;
    size_t  cap;
} Vec;

Vec *vec(void);
Vec *vec_init(size_t n, ...);
void show(FILE *stream, Vec *v);
void clear(Vec *v);
bool is_empty(Vec *v);
bool get(Vec *v, size_t i, elem_t *e);
bool set(Vec *v, size_t i, elem_t e);
bool find(Vec *v, elem_t e, size_t *i);
bool insert(Vec *v, size_t i, elem_t e);
bool push(Vec *v, elem_t e);
bool del(Vec *v, size_t i, elem_t *e);
bool pop(Vec *v, elem_t *e);
void defer(Vec **v);

#endif

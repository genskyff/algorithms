#ifndef ALG_SQLIST_H
#define ALG_SQLIST_H

#include "alg/type.h"
#include <stdbool.h>

// data[0] is the first
// data[len - 1] is the last
typedef struct {
    elem_t data[MAXLEN];
    size_t len;
} SqList;

SqList create(void);
SqList init(size_t n, ...);
void   swap(SqList *list, size_t i, size_t j);
void   reverse(SqList *list);
void   show(FILE *stream, SqList *list);
void   clear(SqList *list);
bool   is_empty(SqList *list);
bool   get(SqList *list, size_t i, elem_t *e);
bool   first(SqList *list, elem_t *e);
bool   last(SqList *list, elem_t *e);
bool   set(SqList *list, size_t i, elem_t e);
bool   find(SqList *list, elem_t e, size_t *i);
bool   insert(SqList *list, size_t i, elem_t e);
bool   push_front(SqList *list, elem_t e);
bool   push_back(SqList *list, elem_t e);
bool   del(SqList *list, size_t i, elem_t *e);
bool   pop_front(SqList *list, elem_t *e);
bool   pop_back(SqList *list, elem_t *e);

#endif

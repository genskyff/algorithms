#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "type.h"
#include <stdbool.h>

typedef struct {
    elem_t data[MAXLEN];
    size_t len;
} ArrayList;

ArrayList create(void);
ArrayList init(size_t n, ...);
void   swap(ArrayList *list, size_t i, size_t j);
void   reverse(ArrayList *list);
void   show(FILE *stream, ArrayList *list);
void   clear(ArrayList *list);
bool   is_empty(ArrayList *list);
bool   get(ArrayList *list, size_t i, elem_t *e);
bool   set(ArrayList *list, size_t i, elem_t e);
bool   find(ArrayList *list, elem_t e, size_t *i);
bool   insert(ArrayList *list, size_t i, elem_t e);
bool   push(ArrayList *list, elem_t e);
bool   del(ArrayList *list, size_t i, elem_t *e);
bool   pop(ArrayList *list, elem_t *e);

#endif

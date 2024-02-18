
#ifndef LIST_H
#define LIST_H
#include "type.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    elem_t *data;
    size_t  len;
} List;

void new();
void clear(List *);
void show(List);
bool is_empty(List);
bool get(List, size_t, elem_t *);
bool find(List, elem_t, size_t *);
bool insert(List *, size_t, elem_t);
bool remove(List *, size_t, elem_t *);
bool update(List *, size_t, elem_t);

#endif

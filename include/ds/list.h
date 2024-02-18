
#ifndef LIST_H
#define LIST_H
#include "type.h"
#include <stdbool.h>

void new();
void clear(List *);
void show(List);
bool is_empty(List);
bool get(List, size_t, elem_t *);
bool insert(List *, size_t, elem_t);
bool remove(List *, size_t, elem_t *);
bool update(List *, size_t, elem_t);

#endif

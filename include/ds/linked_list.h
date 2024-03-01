#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "type.h"
#include <stdbool.h>

typedef struct {
    Node  *head;
    Node  *tail;
    size_t len;
} LinkedList;

LinkedList create(void);
LinkedList init(size_t n, ...);
void       swap(LinkedList *list, size_t i, size_t j);
void       reverse(LinkedList *list);
void       show(FILE *stream, LinkedList *list);
void       clear(LinkedList *list);
bool       is_empty(LinkedList *list);
bool       get(LinkedList *list, size_t i, elem_t *e);
bool       first(LinkedList *list, elem_t *e);
bool       last(LinkedList *list, elem_t *e);
bool       set(LinkedList *list, size_t i, elem_t e);
bool       find(LinkedList *list, elem_t e, size_t *i);
bool       insert(LinkedList *list, size_t i, elem_t e);
bool       push_front(LinkedList *list, elem_t e);
bool       push_back(LinkedList *list, elem_t e);
bool       del(LinkedList *list, size_t i, elem_t *e);
bool       pop_front(LinkedList *list, elem_t *e);
bool       pop_back(LinkedList *list, elem_t *e);

#endif

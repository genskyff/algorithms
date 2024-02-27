#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "type.h"
#include <stdbool.h>

typedef struct {
    Node *head;
} LinkedList;

LinkedList create(void);
LinkedList init(size_t n, ...);
LinkedList from_array(elem_t *arr, size_t len);
elem_t    *to_array(LinkedList *list);
size_t     length(LinkedList *list);
void       swap(LinkedList *list, size_t i, size_t j);
void       reverse(LinkedList *list);
void       show(FILE *stream, LinkedList *list);
void       clear(LinkedList *list);
bool       is_empty(LinkedList *list);
bool       get(LinkedList *list, size_t i, elem_t *e);
bool       set(LinkedList *list, size_t i, elem_t e);
bool       find(LinkedList *list, elem_t e, size_t *i);
bool       insert(LinkedList *list, size_t i, elem_t e);
bool       push(LinkedList *list, elem_t e);
bool       del(LinkedList *list, size_t i, elem_t *e);
bool       pop(LinkedList *list, elem_t *e);

#endif

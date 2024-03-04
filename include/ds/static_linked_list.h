#ifndef STATIC_LINKED_LIST_H
#define STATIC_LINKED_LIST_H

#include "type.h"
#include <stdbool.h>

typedef struct {
    elem_t data;
    size_t prev;
    size_t next;
} SNode;

// node[0] is the head
// node[len - 1] is the tail
typedef struct {
    SNode  node[MAXLEN];
    size_t space;
    size_t head;
    size_t tail;
    size_t len;
} SLinkedList;

SLinkedList create(void);
SLinkedList init(size_t n, ...);
elem_t     *to_array(SLinkedList *list);
void        swap(SLinkedList *list, size_t i, size_t j);
void        reverse(SLinkedList *list);
void        show(FILE *stream, SLinkedList *list);
void        clear(SLinkedList *list);
bool        is_empty(SLinkedList *list);
bool        get(SLinkedList *list, size_t i, elem_t *e);
bool        first(SLinkedList *list, elem_t *e);
bool        last(SLinkedList *list, elem_t *e);
bool        set(SLinkedList *list, size_t i, elem_t e);
bool        find(SLinkedList *list, elem_t e, size_t *i);
bool        insert(SLinkedList *list, size_t i, elem_t e);
bool        push_front(SLinkedList *list, elem_t e);
bool        push_back(SLinkedList *list, elem_t e);
bool        del(SLinkedList *list, size_t i, elem_t *e);
bool        pop_front(SLinkedList *list, elem_t *e);
bool        pop_back(SLinkedList *list, elem_t *e);

#endif

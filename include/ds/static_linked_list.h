#ifndef STATIC_LINKED_LIST_H
#define STATIC_LINKED_LIST_H

#include "type.h"
#include <stdbool.h>

typedef struct {
    elem_t data;
    size_t prev;
    size_t next;
} SNode;

typedef struct {
    SNode  node[MAXLEN];
    size_t space;
    size_t head;
    size_t tail;
    size_t len;
} SLinkedList;

SLinkedList create(void);
SLinkedList init(size_t n, ...);
void        show(FILE *stream, SLinkedList *list);
void        clear(SLinkedList *list);
bool        is_empty(SLinkedList *list);

#endif

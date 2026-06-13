#ifndef ALG_STATIC_LINKED_LIST_H
#define ALG_STATIC_LINKED_LIST_H

#include "alg/core.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    alg_elem_t data;
    size_t     prev;
    size_t     next;
} SNode;

// node[0] is the head
// node[len - 1] is the tail
typedef struct {
    SNode  nodes[ALG_MAX_LEN];
    size_t space;
    size_t head;
    size_t tail;
    size_t len;
} AlgStaticLinkedList;

AlgStaticLinkedList alg_static_linked_list_create(void);
AlgStaticLinkedList alg_static_linked_list_init(size_t n, ...);
alg_elem_t *alg_static_linked_list_to_array(const AlgStaticLinkedList *list);
void alg_static_linked_list_swap(AlgStaticLinkedList *list, size_t i, size_t j);
void alg_static_linked_list_reverse(AlgStaticLinkedList *list);
void alg_static_linked_list_show(FILE *stream, const AlgStaticLinkedList *list);
void alg_static_linked_list_clear(AlgStaticLinkedList *list);
bool alg_static_linked_list_is_empty(const AlgStaticLinkedList *list);
bool alg_static_linked_list_get(const AlgStaticLinkedList *list, size_t i,
                                alg_elem_t *e);
bool alg_static_linked_list_first(const AlgStaticLinkedList *list,
                                  alg_elem_t                *e);
bool alg_static_linked_list_last(const AlgStaticLinkedList *list,
                                 alg_elem_t                *e);
bool alg_static_linked_list_set(AlgStaticLinkedList *list, size_t i,
                                alg_elem_t e);
bool alg_static_linked_list_find(const AlgStaticLinkedList *list, alg_elem_t e,
                                 size_t *i);
bool alg_static_linked_list_insert(AlgStaticLinkedList *list, size_t i,
                                   alg_elem_t e);
bool alg_static_linked_list_push_front(AlgStaticLinkedList *list, alg_elem_t e);
bool alg_static_linked_list_push_back(AlgStaticLinkedList *list, alg_elem_t e);
bool alg_static_linked_list_del(AlgStaticLinkedList *list, size_t i,
                                alg_elem_t *e);
bool alg_static_linked_list_pop_front(AlgStaticLinkedList *list, alg_elem_t *e);
bool alg_static_linked_list_pop_back(AlgStaticLinkedList *list, alg_elem_t *e);

#endif

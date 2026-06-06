#ifndef ALG_LINKED_LIST_H
#define ALG_LINKED_LIST_H

#include "alg/ds/node.h"
#include <stdbool.h>

// index [0] is the head
// index [len - 1] is the tail
typedef struct {
    AlgNode *head;
    AlgNode *tail;
    size_t   len;
} AlgLinkedList;

AlgLinkedList alg_linked_list_create(void);
AlgLinkedList alg_linked_list_init(size_t n, ...);
void          alg_linked_list_swap(AlgLinkedList *list, size_t i, size_t j);
void          alg_linked_list_reverse(AlgLinkedList *list);
void          alg_linked_list_show(FILE *stream, AlgLinkedList *list);
void          alg_linked_list_clear(AlgLinkedList *list);
bool          alg_linked_list_is_empty(AlgLinkedList *list);
bool          alg_linked_list_get(AlgLinkedList *list, size_t i, alg_elem_t *e);
bool          alg_linked_list_first(AlgLinkedList *list, alg_elem_t *e);
bool          alg_linked_list_last(AlgLinkedList *list, alg_elem_t *e);
bool          alg_linked_list_set(AlgLinkedList *list, size_t i, alg_elem_t e);
bool alg_linked_list_find(AlgLinkedList *list, alg_elem_t e, size_t *i);
bool alg_linked_list_insert(AlgLinkedList *list, size_t i, alg_elem_t e);
bool alg_linked_list_push_front(AlgLinkedList *list, alg_elem_t e);
bool alg_linked_list_push_back(AlgLinkedList *list, alg_elem_t e);
bool alg_linked_list_del(AlgLinkedList *list, size_t i, alg_elem_t *e);
bool alg_linked_list_pop_front(AlgLinkedList *list, alg_elem_t *e);
bool alg_linked_list_pop_back(AlgLinkedList *list, alg_elem_t *e);

#endif

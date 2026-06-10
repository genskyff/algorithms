#ifndef ALG_LINKED_QUEUE_H
#define ALG_LINKED_QUEUE_H

#include "alg/ds/node.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// index [0] is the front
// index [len - 1] is the rear
typedef struct {
    AlgNode *front;
    AlgNode *rear;
    size_t   len;
} AlgLinkedQueue;

AlgLinkedQueue alg_linked_queue_create(void);
AlgLinkedQueue alg_linked_queue_init(size_t n, ...);
void           alg_linked_queue_show(FILE *stream, AlgLinkedQueue *queue);
void           alg_linked_queue_clear(AlgLinkedQueue *queue);
bool           alg_linked_queue_is_empty(AlgLinkedQueue *queue);
bool           alg_linked_queue_front(AlgLinkedQueue *queue, alg_elem_t *e);
bool           alg_linked_queue_back(AlgLinkedQueue *queue, alg_elem_t *e);
bool           alg_linked_queue_push_front(AlgLinkedQueue *queue, alg_elem_t e);
bool           alg_linked_queue_push_back(AlgLinkedQueue *queue, alg_elem_t e);
bool           alg_linked_queue_pop_front(AlgLinkedQueue *queue, alg_elem_t *e);
bool           alg_linked_queue_pop_back(AlgLinkedQueue *queue, alg_elem_t *e);

#endif

#ifndef ALG_LINKED_QUEUE_H
#define ALG_LINKED_QUEUE_H

#include "alg/type.h"
#include <stdbool.h>

// index [0] is the front
// index [len - 1] is the rear
typedef struct {
    Node  *front;
    Node  *rear;
    size_t len;
} LinkedQueue;

LinkedQueue create(void);
LinkedQueue init(size_t n, ...);
void        show(FILE *stream, LinkedQueue *queue);
void        clear(LinkedQueue *queue);
bool        is_empty(LinkedQueue *queue);
bool        front(LinkedQueue *queue, elem_t *e);
bool        back(LinkedQueue *queue, elem_t *e);
bool        push_front(LinkedQueue *queue, elem_t e);
bool        push_back(LinkedQueue *queue, elem_t e);
bool        pop_front(LinkedQueue *queue, elem_t *e);
bool        pop_back(LinkedQueue *queue, elem_t *e);

#endif

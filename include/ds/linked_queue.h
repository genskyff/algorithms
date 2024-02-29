#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "type.h"
#include <stdbool.h>

typedef struct {
    Node  *front;
    Node  *rear;
    size_t len;
} LinkedQueue;

LinkedQueue create(void);
LinkedQueue init(size_t n, ...);
LinkedQueue from_array(elem_t *arr, size_t len);
elem_t     *to_array(LinkedQueue *queue);
void        show(FILE *stream, LinkedQueue *queue);
void        clear(LinkedQueue *queue);
bool        is_empty(LinkedQueue *queue);
bool        front(LinkedQueue *queue, elem_t *e);
bool        enque(LinkedQueue *queue, elem_t e);
bool        deque(LinkedQueue *queue, elem_t *e);

#endif

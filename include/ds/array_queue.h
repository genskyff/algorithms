#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "type.h"
#include <stdbool.h>

typedef struct {
    elem_t data[MAXLEN];
    size_t front;
    size_t len;
} ArrayQueue;

ArrayQueue create(void);
ArrayQueue init(size_t n, ...);
void       show(FILE *stream, ArrayQueue *queue);
void       clear(ArrayQueue *queue);
bool       is_empty(ArrayQueue *queue);
bool       front(ArrayQueue *queue, elem_t *e);
bool       enque(ArrayQueue *queue, elem_t e);
bool       deque(ArrayQueue *queue, elem_t *e);

#endif

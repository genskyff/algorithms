#include "linked_queue.h"
#include <stdarg.h>
#include <stdlib.h>

LinkedQueue create(void);

LinkedQueue init(size_t n, ...);

LinkedQueue from_array(elem_t *arr, size_t len);

elem_t *to_array(LinkedQueue *queue);

void show(FILE *stream, LinkedQueue *queue);

void clear(LinkedQueue *queue);

bool is_empty(LinkedQueue *queue);

bool front(LinkedQueue *queue, elem_t *e);

bool enque(LinkedQueue *queue, elem_t e);

bool deque(LinkedQueue *queue, elem_t *e);

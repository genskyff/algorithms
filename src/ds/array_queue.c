#include "array_queue.h"
#include "utils.h"
#include <stdarg.h>

ArrayQueue create(void);
ArrayQueue init(size_t n, ...);
void       show(FILE *stream, ArrayQueue *queue);
void       clear(ArrayQueue *queue);
bool       is_empty(ArrayQueue *queue);
bool       front(ArrayQueue *queue, elem_t *e);
bool       enque(ArrayQueue *queue, elem_t e);
bool       deque(ArrayQueue *queue, elem_t *e);

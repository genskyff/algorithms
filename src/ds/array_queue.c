#include "array_queue.h"
#include "utils.h"
#include <stdarg.h>

ArrayQueue create(void) {
    ArrayQueue queue = {.front = 0, .len = 0};

    return queue;
}

ArrayQueue init(size_t n, ...) {
    ArrayQueue queue = create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        queue.data[queue.len++] = va_arg(ap, elem_t);
    }

    va_end(ap);

    return queue;
}

void show(FILE *stream, ArrayQueue *queue) {
    if (queue != NULL) {
        _show(stream, queue->data, queue->len);
    } else {
        fprintf(stream == NULL ? stdout : stream, "[]\n");
    }
}

void clear(ArrayQueue *queue) {
    if (queue != NULL) {
        queue->front = 0;
        queue->len   = 0;
    }
}

bool is_empty(ArrayQueue *queue) {
    return queue == NULL || queue->len == 0;
}

bool front(ArrayQueue *queue, elem_t *e) {
    if (queue == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->data[queue->front];
    }

    return true;
}

bool enque(ArrayQueue *queue, elem_t e) {
    if (queue == NULL || queue->len == MAXLEN) {
        return false;
    }

    size_t rear = (queue->front + queue->len) % MAXLEN;
    queue->data[rear] = e;
    queue->len++;

    return true;
}

bool deque(ArrayQueue *queue, elem_t *e) {
    if (queue == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->data[queue->front];
    }

    queue->front = (queue->front + 1) % MAXLEN;
    queue->len--;

    return true;
}

#include "alg/ds/array_queue.h"
#include "internal/utils.h"
#include <stdarg.h>

AlgArrayQueue alg_array_queue_create(void) {
    AlgArrayQueue queue = {.front = 0, .len = 0};

    return queue;
}

AlgArrayQueue alg_array_queue_init(size_t n, ...) {
    AlgArrayQueue queue = alg_array_queue_create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < ALG_INTERNAL_MIN(n, ALG_MAX_LEN); i++) {
        queue.data[queue.len++] = va_arg(ap, alg_elem_t);
    }

    va_end(ap);

    return queue;
}

void alg_array_queue_show(FILE *stream, AlgArrayQueue *queue) {
    if (queue != NULL) {
        alg_internal_show(stream, queue->data, queue->len, " <-> ");
    } else {
        alg_internal_show(stream, NULL, 0, NULL);
    }
}

void alg_array_queue_clear(AlgArrayQueue *queue) {
    if (queue != NULL) {
        queue->front = 0;
        queue->len   = 0;
    }
}

bool alg_array_queue_is_empty(AlgArrayQueue *queue) {
    return queue == NULL || queue->len == 0;
}

bool alg_array_queue_front(AlgArrayQueue *queue, alg_elem_t *e) {
    if (alg_array_queue_is_empty(queue)) {
        return false;
    }

    if (e != NULL) {
        *e = queue->data[queue->front];
    }

    return true;
}

bool alg_array_queue_back(AlgArrayQueue *queue, alg_elem_t *e) {
    if (alg_array_queue_is_empty(queue)) {
        return false;
    }

    if (e != NULL) {
        *e = queue->data[(queue->front + queue->len - 1) % ALG_MAX_LEN];
    }

    return true;
}

bool alg_array_queue_push_front(AlgArrayQueue *queue, alg_elem_t e) {
    if (queue == NULL || queue->len == ALG_MAX_LEN) {
        return false;
    }

    queue->front              = (queue->front - 1 + ALG_MAX_LEN) % ALG_MAX_LEN;
    queue->data[queue->front] = e;
    queue->len++;

    return true;
}

bool alg_array_queue_push_back(AlgArrayQueue *queue, alg_elem_t e) {
    if (queue == NULL || queue->len == ALG_MAX_LEN) {
        return false;
    }

    size_t rear       = (queue->front + queue->len) % ALG_MAX_LEN;
    queue->data[rear] = e;
    queue->len++;

    return true;
}

bool alg_array_queue_pop_front(AlgArrayQueue *queue, alg_elem_t *e) {
    if (alg_array_queue_is_empty(queue)) {
        return false;
    }

    if (e != NULL) {
        *e = queue->data[queue->front];
    }

    queue->front = (queue->front + 1) % ALG_MAX_LEN;
    queue->len--;

    return true;
}

bool alg_array_queue_pop_back(AlgArrayQueue *queue, alg_elem_t *e) {
    if (alg_array_queue_is_empty(queue)) {
        return false;
    }

    if (e != NULL) {
        *e = queue->data[(queue->front + queue->len - 1) % ALG_MAX_LEN];
    }

    queue->len--;

    return true;
}

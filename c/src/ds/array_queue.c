#include "alg/ds/array_queue.h"
#include "internal/utils.h"

AlgArrayQueue alg_array_queue_create(void) {
    AlgArrayQueue queue = {.front = 0, .len = 0};

    return queue;
}

AlgArrayQueue alg_array_queue_from_array(const alg_elem_t *arr, size_t len) {
    AlgArrayQueue queue = alg_array_queue_create();

    if (arr != NULL) {
        queue.len = ALG_INTERNAL_MIN(len, ALG_MAX_LEN);
        alg_internal_copy(queue.data, queue.len, arr, queue.len);
    }

    return queue;
}

void alg_array_queue_show(FILE *stream, const AlgArrayQueue *queue) {
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

bool alg_array_queue_is_empty(const AlgArrayQueue *queue) {
    return queue == NULL || queue->len == 0;
}

bool alg_array_queue_front(const AlgArrayQueue *queue, alg_elem_t *e) {
    if (alg_array_queue_is_empty(queue)) {
        return false;
    }

    if (e != NULL) {
        *e = queue->data[queue->front];
    }

    return true;
}

bool alg_array_queue_back(const AlgArrayQueue *queue, alg_elem_t *e) {
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

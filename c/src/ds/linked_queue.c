#include "alg/ds/linked_queue.h"
#include "internal/utils.h"
#include <stdarg.h>
#include <stdlib.h>

AlgLinkedQueue alg_linked_queue_create(void) {
    AlgLinkedQueue queue = {.front = NULL, .rear = NULL, .len = 0};

    return queue;
}

AlgLinkedQueue alg_linked_queue_init(size_t n, ...) {
    AlgLinkedQueue queue = alg_linked_queue_create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        AlgNode *node = (AlgNode *)malloc(sizeof(AlgNode));
        alg_internal_has_alloc_err(node, __func__);

        node->data = va_arg(ap, alg_elem_t);
        node->next = NULL;

        if (queue.front == NULL) {
            node->prev  = NULL;
            queue.front = node;
        } else {
            node->prev       = queue.rear;
            queue.rear->next = node;
        }

        queue.rear = node;
        queue.len++;
    }

    va_end(ap);

    return queue;
}

void alg_linked_queue_show(FILE *stream, AlgLinkedQueue *queue) {
    if (queue != NULL) {
        alg_internal_show_list(stream, queue->front, ALG_FORWARD, NULL);
    } else {
        alg_internal_show_list(stream, NULL, ALG_FORWARD, NULL);
    }
}

void alg_linked_queue_clear(AlgLinkedQueue *queue) {
    if (queue != NULL) {
        AlgNode *node = queue->front;
        while (node != NULL) {
            AlgNode *tmp = node;
            node         = node->next;
            free(tmp);
        }

        queue->front = NULL;
        queue->rear  = NULL;
        queue->len   = 0;
    }
}

bool alg_linked_queue_is_empty(AlgLinkedQueue *queue) {
    return queue == NULL || queue->front == NULL || queue->len == 0;
}

bool alg_linked_queue_front(AlgLinkedQueue *queue, alg_elem_t *e) {
    if (queue == NULL || queue->front == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->front->data;
    }

    return true;
}

bool alg_linked_queue_back(AlgLinkedQueue *queue, alg_elem_t *e) {
    if (queue == NULL || queue->rear == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->rear->data;
    }

    return true;
}

bool alg_linked_queue_push_front(AlgLinkedQueue *queue, alg_elem_t e) {
    if (queue == NULL) {
        return false;
    }

    AlgNode *node = (AlgNode *)malloc(sizeof(AlgNode));
    if (node == NULL) {
        return false;
    }

    node->data = e;
    node->prev = NULL;

    if (queue->front == NULL) {
        node->next  = NULL;
        queue->rear = node;
    } else {
        node->next         = queue->front;
        queue->front->prev = node;
    }

    queue->front = node;
    queue->len++;

    return true;
}

bool alg_linked_queue_push_back(AlgLinkedQueue *queue, alg_elem_t e) {
    if (queue == NULL) {
        return false;
    }

    AlgNode *node = (AlgNode *)malloc(sizeof(AlgNode));
    if (node == NULL) {
        return false;
    }

    node->data = e;
    node->next = NULL;

    if (queue->front == NULL) {
        node->prev   = NULL;
        queue->front = node;
    } else {
        node->prev        = queue->rear;
        queue->rear->next = node;
    }

    queue->rear = node;
    queue->len++;

    return true;
}

bool alg_linked_queue_pop_front(AlgLinkedQueue *queue, alg_elem_t *e) {
    if (queue == NULL || queue->front == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->front->data;
    }

    AlgNode *node = queue->front;
    if (queue->front == queue->rear) {
        queue->front = NULL;
        queue->rear  = NULL;
    } else {
        queue->front       = queue->front->next;
        queue->front->prev = NULL;
    }

    queue->len--;
    free(node);

    return true;
}

bool alg_linked_queue_pop_back(AlgLinkedQueue *queue, alg_elem_t *e) {
    if (queue == NULL || queue->front == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->rear->data;
    }

    AlgNode *node = queue->rear;
    if (queue->front == queue->rear) {
        queue->front = NULL;
        queue->rear  = NULL;
    } else {
        queue->rear       = queue->rear->prev;
        queue->rear->next = NULL;
    }

    queue->len--;
    free(node);

    return true;
}

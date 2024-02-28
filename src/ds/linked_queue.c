#include "linked_queue.h"
#include <stdarg.h>
#include <stdlib.h>

LinkedQueue create(void) {
    LinkedQueue queue = {NULL, NULL, 0};

    return queue;
}

LinkedQueue init(size_t n, ...) {
    elem_t *arr = (elem_t *)malloc(n * sizeof(elem_t));

    if (arr == NULL) {
        fprintf(stderr, "init: failed to allocate memory\n");
        abort();
    }

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        arr[i] = va_arg(ap, elem_t);
    }

    va_end(ap);

    LinkedQueue queue = from_array(arr, n);
    free(arr);

    return queue;
}

LinkedQueue from_array(elem_t *arr, size_t len) {
    LinkedQueue queue = create();

    if (arr == NULL || len == 0) {
        return queue;
    }

    Node *tail = NULL;
    for (size_t i = 0; i < len; i++) {
        Node *node = (Node *)malloc(sizeof(Node));
        if (node == NULL) {
            return queue;
        }

        node->data = arr[i];
        node->next = NULL;

        if (queue.front == NULL) {
            queue.front = node;
            tail        = node;
        } else {
            tail->next = node;
            tail       = node;
        }

        queue.len++;
    }

    queue.rear = tail;

    return queue;
}

elem_t *to_array(LinkedQueue *queue) {
    if (queue == NULL || queue->len == 0) {
        return NULL;
    }

    elem_t *arr = (elem_t *)malloc(queue->len * sizeof(elem_t));
    if (arr == NULL) {
        return NULL;
    }

    Node *node = queue->front;
    for (size_t i = 0; i < queue->len; i++) {
        arr[i] = node->data;
        node   = node->next;
    }

    return arr;
}

void show(FILE *stream, LinkedQueue *queue) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (queue == NULL || queue->len == 0) {
        fprintf(stream, "[]\n");
        return;
    }

    fprintf(stream, "[");
    Node *node = queue->front;
    for (size_t i = 0; i < queue->len; i++) {
        fprintf(stream, "%d", node->data);
        if (i < queue->len - 1) {
            fprintf(stream, " <- ");
        }
        node = node->next;
    }
    fprintf(stream, "]\n");
}

void clear(LinkedQueue *queue) {
    if (queue == NULL || queue->len == 0) {
        return;
    }

    Node *node = queue->front;
    while (node != NULL) {
        Node *tmp = node;
        node      = node->next;
        free(tmp);
    }

    queue->front = NULL;
    queue->rear  = NULL;
    queue->len   = 0;
}

bool is_empty(LinkedQueue *queue) {
    return queue == NULL || queue->len == 0;
}

bool head(LinkedQueue *queue, elem_t *e) {
    if (queue == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->front->data;
    }

    return true;
}

bool enque(LinkedQueue *queue, elem_t e) {
    if (queue == NULL) {
        return false;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }

    node->data = e;
    node->next = NULL;

    if (queue->front == NULL) {
        queue->front = node;
        queue->rear  = node;
    } else {
        queue->rear->next = node;
        queue->rear       = node;
    }

    queue->len++;

    return true;
}

bool deque(LinkedQueue *queue, elem_t *e) {
    if (queue == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->front->data;
    }

    Node *node   = queue->front;
    queue->front = queue->front->next;
    free(node);

    queue->len--;

    return true;
}

#include "linked_queue.h"
#include "util.h"
#include <stdarg.h>
#include <stdlib.h>

LinkedQueue create(void) {
    LinkedQueue queue = {.front = NULL, .rear = NULL, .len = 0};

    return queue;
}

LinkedQueue init(size_t n, ...) {
    LinkedQueue queue = create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        Node *node = (Node *)malloc(sizeof(Node));
        if (node == NULL) {
            fprintf(stderr,
                    "\x1b[1;31merror: \x1b[0mfailed to allocate memory (exec "
                    "\x1b[33minit\x1b[0m)\n\n");
            exit(EXIT_FAILURE);
        }

        node->data = va_arg(ap, elem_t);
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

void show(FILE *stream, LinkedQueue *queue) {
    if (queue != NULL) {
        _show_list(stream, queue->front, FORWARD, NULL);
    } else {
        _show_list(stream, NULL, FORWARD, NULL);
    }
}

void clear(LinkedQueue *queue) {
    if (queue == NULL) {
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
    return queue == NULL || queue->front == NULL || queue->len == 0;
}

bool front(LinkedQueue *queue, elem_t *e) {
    if (queue == NULL || queue->front == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->front->data;
    }

    return true;
}

bool back(LinkedQueue *queue, elem_t *e) {
    if (queue == NULL || queue->rear == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->rear->data;
    }

    return true;
}

bool push_front(LinkedQueue *queue, elem_t e) {
    if (queue == NULL) {
        return false;
    }

    Node *node = (Node *)malloc(sizeof(Node));
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

bool push_back(LinkedQueue *queue, elem_t e) {
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

bool pop_front(LinkedQueue *queue, elem_t *e) {
    if (queue == NULL || queue->front == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->front->data;
    }

    Node *node = queue->front;
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

bool pop_back(LinkedQueue *queue, elem_t *e) {
    if (queue == NULL || queue->front == NULL || queue->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = queue->rear->data;
    }

    Node *node = queue->rear;
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

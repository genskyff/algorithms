#include "linked_stack.h"
#include "utils.h"
#include <stdarg.h>
#include <stdlib.h>

LinkedStack create(void) {
    LinkedStack stack = {.top = NULL, .len = 0};

    return stack;
}

LinkedStack init(size_t n, ...) {
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

    LinkedStack stack = from_array(arr, n);
    free(arr);

    return stack;
}

LinkedStack from_array(elem_t *arr, size_t len) {
    LinkedStack stack = create();

    if (arr == NULL || len == 0) {
        return stack;
    }

    Node *tail = NULL;

    for (size_t i = 0; i < len; i++) {
        Node *node = (Node *)malloc(sizeof(Node));
        if (node == NULL) {
            return stack;
        }

        node->data = arr[i];
        node->next = NULL;

        if (stack.top == NULL) {
            stack.top = node;
            tail      = node;
        } else {
            tail->next = node;
            tail       = node;
        }

        stack.len++;
    }

    return stack;
}

elem_t *to_array(LinkedStack *stack) {
    if (stack == NULL || stack->top == NULL) {
        return NULL;
    }

    elem_t *arr = (elem_t *)malloc(stack->len * sizeof(elem_t));
    if (arr == NULL) {
        return NULL;
    }

    Node *node = stack->top;
    for (size_t i = 0; node != NULL; i++) {
        arr[i] = node->data;
        node   = node->next;
    }

    return arr;
}

void show(FILE *stream, LinkedStack *stack) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (stack == NULL || stack->top == NULL) {
        fprintf(stream, "[]\n");
        return;
    }

    fprintf(stream, "[");
    Node *node = stack->top;
    for (size_t i = 0; node != NULL; i++) {
        fprintf(stream, "%d", node->data);
        if (node->next != NULL) {
            fprintf(stream, " -> ");
        }
        node = node->next;
    }

    fprintf(stream, "]\n");
}

void clear(LinkedStack *stack) {
    if (stack == NULL) {
        return;
    }

    Node *node = stack->top;
    while (node != NULL) {
        Node *temp = node;
        node       = node->next;
        free(temp);
    }

    stack->top = NULL;
    stack->len = 0;
}

bool is_empty(LinkedStack *stack) {
    return stack == NULL || stack->top == NULL || stack->len == 0;
}

bool peek(LinkedStack *stack, elem_t *e) {
    if (stack == NULL || stack->top == NULL) {
        return false;
    }

    if (e != NULL) {
        *e = stack->top->data;
    }

    return true;
}

bool push(LinkedStack *stack, elem_t e) {
    if (stack == NULL) {
        return false;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }

    node->data = e;
    node->next = stack->top;
    stack->top = node;
    stack->len++;

    return true;
}

bool pop(LinkedStack *stack, elem_t *e) {
    if (stack == NULL || stack->top == NULL) {
        return false;
    }

    if (e != NULL) {
        *e = stack->top->data;
    }

    Node *node = stack->top;
    stack->top = stack->top->next;
    free(node);
    stack->len--;

    return true;
}

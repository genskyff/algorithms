#include "linked_stack.h"
#include "util.h"
#include <stdarg.h>
#include <stdlib.h>

LinkedStack create(void) {
    LinkedStack stack = {.top = NULL, .len = 0};

    return stack;
}

LinkedStack init(size_t n, ...) {
    LinkedStack stack = create();

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

        if (stack.top == NULL) {
            node->prev = NULL;
        } else {
            node->prev      = stack.top;
            stack.top->next = node;
        }

        stack.top = node;
        stack.len++;
    }

    va_end(ap);

    return stack;
}

void show(FILE *stream, LinkedStack *stack) {
    if (stack != NULL) {
        _show_list(stream, stack->top, BACKWARD, " -> ");
    } else {
        _show_list(stream, NULL, BACKWARD, NULL);
    }
}

void clear(LinkedStack *stack) {
    if (stack == NULL) {
        return;
    }

    Node *node = stack->top;
    while (node != NULL) {
        Node *tmp = node;
        node      = node->prev;
        free(tmp);
    }

    stack->top = NULL;
    stack->len = 0;
}

bool is_empty(LinkedStack *stack) {
    return stack == NULL || stack->top == NULL || stack->len == 0;
}

bool peek(LinkedStack *stack, elem_t *e) {
    if (stack == NULL || stack->top == NULL || stack->len == 0) {
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
    node->next = NULL;

    if (stack->top == NULL) {
        node->prev = NULL;
    } else {
        node->prev       = stack->top;
        stack->top->next = node;
    }

    stack->top = node;
    stack->len++;

    return true;
}

bool pop(LinkedStack *stack, elem_t *e) {
    if (stack == NULL || stack->top == NULL || stack->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = stack->top->data;
    }

    Node *node = stack->top;
    stack->top = node->prev;
    if (stack->top != NULL) {
        stack->top->next = NULL;
    }

    stack->len--;
    free(node);

    return true;
}

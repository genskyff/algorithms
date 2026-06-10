#include "alg/ds/linked_stack.h"
#include "internal/utils.h"
#include <stdarg.h>
#include <stdlib.h>

AlgLinkedStack alg_linked_stack_create(void) {
    AlgLinkedStack stack = {.top = NULL, .len = 0};

    return stack;
}

AlgLinkedStack alg_linked_stack_init(size_t n, ...) {
    AlgLinkedStack stack = alg_linked_stack_create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        AlgNode *node = (AlgNode *)malloc(sizeof(AlgNode));
        alg_internal_has_alloc_err(node, __func__);

        node->data = va_arg(ap, alg_elem_t);
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

void alg_linked_stack_show(FILE *stream, AlgLinkedStack *stack) {
    if (stack != NULL) {
        alg_internal_show_list(stream, stack->top, ALG_BACKWARD, " -> ");
    } else {
        alg_internal_show_list(stream, NULL, ALG_BACKWARD, NULL);
    }
}

void alg_linked_stack_clear(AlgLinkedStack *stack) {
    if (stack != NULL) {
        AlgNode *node = stack->top;
        while (node != NULL) {
            AlgNode *tmp = node;
            node         = node->prev;
            free(tmp);
        }

        stack->top = NULL;
        stack->len = 0;
    }
}

bool alg_linked_stack_is_empty(AlgLinkedStack *stack) {
    return stack == NULL || stack->top == NULL || stack->len == 0;
}

bool alg_linked_stack_peek(AlgLinkedStack *stack, alg_elem_t *e) {
    if (stack == NULL || stack->top == NULL || stack->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = stack->top->data;
    }

    return true;
}

bool alg_linked_stack_push(AlgLinkedStack *stack, alg_elem_t e) {
    if (stack == NULL) {
        return false;
    }

    AlgNode *node = (AlgNode *)malloc(sizeof(AlgNode));
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

bool alg_linked_stack_pop(AlgLinkedStack *stack, alg_elem_t *e) {
    if (stack == NULL || stack->top == NULL || stack->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = stack->top->data;
    }

    AlgNode *node = stack->top;
    stack->top    = node->prev;
    if (stack->top != NULL) {
        stack->top->next = NULL;
    }

    stack->len--;
    free(node);

    return true;
}

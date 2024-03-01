#include "array_stack.h"
#include "utils.h"
#include <stdarg.h>

ArrayStack create(void) {
    ArrayStack stack = {.len = 0};

    return stack;
}

ArrayStack init(size_t n, ...) {
    ArrayStack stack = create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < MIN(n, MAXLEN); i++) {
        stack.data[stack.len++] = va_arg(ap, elem_t);
    }

    va_end(ap);

    return stack;
}

void show(FILE *stream, ArrayStack *stack) {
    if (stack != NULL) {
        _show(stream, stack->data, stack->len, NULL);
    } else {
        _show(stream, NULL, 0, NULL);
    }
}

void clear(ArrayStack *stack) {
    if (stack != NULL) {
        stack->len = 0;
    }
}

bool is_empty(ArrayStack *stack) {
    return stack == NULL || stack->len == 0;
}

bool peek(ArrayStack *stack, elem_t *e) {
    if (stack == NULL || stack->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = stack->data[stack->len - 1];
    }

    return true;
}

bool push(ArrayStack *stack, elem_t e) {
    if (stack == NULL || stack->len == MAXLEN) {
        return false;
    }

    stack->data[stack->len++] = e;

    return true;
}

bool pop(ArrayStack *stack, elem_t *e) {
    if (stack == NULL || stack->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = stack->data[--stack->len];
    }

    return true;
}

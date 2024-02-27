#include "array_stack.h"
#include "utils.h"
#include <stdarg.h>
#include <stdlib.h>

ArrayStack create(void) {
    ArrayStack stack = {.len = 0};

    return stack;
}

ArrayStack init(size_t n, ...) {
    ArrayStack stack = create();
    va_list    ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        stack.data[stack.len++] = va_arg(ap, elem_t);
    }

    va_end(ap);

    return stack;
}

void show(FILE *stream, ArrayStack *stack) {
    if (stack != NULL) {
        _show(stream, stack->data, stack->len);
    } else {
        fprintf(stream == NULL ? stdout : stream, "[]\n");
    }
}

void clear(ArrayStack *stack) {
    if (stack != NULL) {
        stack->len = 0;
    }
}

bool is_empty(ArrayStack *stack) {
    return stack == NULL || stack->len == 0 ? true : false;
}

bool peek(ArrayStack *stack, elem_t *e) {
    if (stack != NULL && stack->len > 0) {
        *e = stack->data[stack->len - 1];
        return true;
    }

    return false;
}

bool push(ArrayStack *stack, elem_t e) {
    if (stack != NULL && stack->len < MAXLEN) {
        stack->data[stack->len++] = e;
        return true;
    }

    return false;
}

bool pop(ArrayStack *stack, elem_t *e) {
    if (stack != NULL && stack->len > 0) {
        *e = stack->data[--stack->len];
        return true;
    }

    return false;
}

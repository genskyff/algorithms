#include "alg/ds/array_stack.h"
#include "utils.h"
#include <stdarg.h>

AlgArrayStack alg_array_stack_create(void) {
    AlgArrayStack stack = {.len = 0};

    return stack;
}

AlgArrayStack alg_array_stack_init(size_t n, ...) {
    AlgArrayStack stack = alg_array_stack_create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < ALG_INTERNAL_MIN(n, ALG_MAX_LEN); i++) {
        stack.data[stack.len++] = va_arg(ap, alg_elem_t);
    }

    va_end(ap);

    return stack;
}

void alg_array_stack_show(FILE *stream, AlgArrayStack *stack) {
    if (stack != NULL) {
        alg_internal_show(stream, stack->data, stack->len, NULL);
    } else {
        alg_internal_show(stream, NULL, 0, NULL);
    }
}

void alg_array_stack_clear(AlgArrayStack *stack) {
    if (stack != NULL) {
        stack->len = 0;
    }
}

bool alg_array_stack_is_empty(AlgArrayStack *stack) {
    return stack == NULL || stack->len == 0;
}

bool alg_array_stack_peek(AlgArrayStack *stack, alg_elem_t *e) {
    if (alg_array_stack_is_empty(stack)) {
        return false;
    }

    if (e != NULL) {
        *e = stack->data[stack->len - 1];
    }

    return true;
}

bool alg_array_stack_push(AlgArrayStack *stack, alg_elem_t e) {
    if (stack == NULL || stack->len == ALG_MAX_LEN) {
        return false;
    }

    stack->data[stack->len++] = e;

    return true;
}

bool alg_array_stack_pop(AlgArrayStack *stack, alg_elem_t *e) {
    if (alg_array_stack_is_empty(stack)) {
        return false;
    }

    if (e != NULL) {
        *e = stack->data[--stack->len];
    }

    return true;
}

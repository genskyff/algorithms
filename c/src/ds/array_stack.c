#include "alg/ds/array_stack.h"
#include "internal/utils.h"

AlgArrayStack alg_array_stack_create(void) {
    AlgArrayStack stack = {.len = 0};

    return stack;
}

AlgArrayStack alg_array_stack_from_array(const alg_elem_t *arr, size_t len) {
    AlgArrayStack stack = alg_array_stack_create();

    if (arr != NULL) {
        stack.len = ALG_INTERNAL_MIN(len, ALG_MAX_LEN);
        alg_internal_copy(stack.data, stack.len, arr, stack.len);
    }

    return stack;
}

void alg_array_stack_show(FILE *stream, const AlgArrayStack *stack) {
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

bool alg_array_stack_is_empty(const AlgArrayStack *stack) {
    return stack == NULL || stack->len == 0;
}

bool alg_array_stack_peek(const AlgArrayStack *stack, alg_elem_t *e) {
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

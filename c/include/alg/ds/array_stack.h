#ifndef ALG_ARRAY_STACK_H
#define ALG_ARRAY_STACK_H

#include "alg/type.h"
#include <stdbool.h>

// index [len - 1] is the top
typedef struct {
    elem_t data[MAXLEN];
    size_t len;
} ArrayStack;

ArrayStack create(void);
ArrayStack init(size_t n, ...);
void       show(FILE *stream, ArrayStack *stack);
void       clear(ArrayStack *stack);
bool       is_empty(ArrayStack *stack);
bool       peek(ArrayStack *stack, elem_t *e);
bool       push(ArrayStack *stack, elem_t e);
bool       pop(ArrayStack *stack, elem_t *e);

#endif

#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "type.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef SqList ArrayStack;

ArrayStack create(void);
ArrayStack init(size_t n, ...);
void       show(FILE *stream, ArrayStack *stack);
void       clear(ArrayStack *stack);
bool       is_empty(ArrayStack *stack);
bool       peek(ArrayStack *stack, elem_t *e);
bool       push(ArrayStack *stack, elem_t e);
bool       pop(ArrayStack *stack, elem_t *e);

#endif

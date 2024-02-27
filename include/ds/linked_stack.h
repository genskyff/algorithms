#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "type.h"
#include <stdbool.h>

typedef struct {
    Node  *top;
    size_t len;
} LinkedStack;

LinkedStack create(void);
LinkedStack init(size_t n, ...);
LinkedStack from_array(elem_t *arr, size_t len);
elem_t     *to_array(LinkedStack *stack);
void        show(FILE *stream, LinkedStack *stack);
void        clear(LinkedStack *stack);
bool        is_empty(LinkedStack *stack);
bool        peek(LinkedStack *stack, elem_t *e);
bool        push(LinkedStack *stack, elem_t e);
bool        pop(LinkedStack *stack, elem_t *e);

#endif

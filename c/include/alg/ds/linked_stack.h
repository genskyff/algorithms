#ifndef ALG_LINKED_STACK_H
#define ALG_LINKED_STACK_H

#include "alg/type.h"
#include <stdbool.h>

// index [len - 1] is the top
typedef struct {
    Node  *top;
    size_t len;
} LinkedStack;

LinkedStack create(void);
LinkedStack init(size_t n, ...);
void        show(FILE *stream, LinkedStack *stack);
void        clear(LinkedStack *stack);
bool        is_empty(LinkedStack *stack);
bool        peek(LinkedStack *stack, elem_t *e);
bool        push(LinkedStack *stack, elem_t e);
bool        pop(LinkedStack *stack, elem_t *e);

#endif

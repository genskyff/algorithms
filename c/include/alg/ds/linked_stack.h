#ifndef ALG_LINKED_STACK_H
#define ALG_LINKED_STACK_H

#include "alg/ds/node.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// index [len - 1] is the top
typedef struct {
    AlgNode *top;
    size_t   len;
} AlgLinkedStack;

AlgLinkedStack alg_linked_stack_create(void);
AlgLinkedStack alg_linked_stack_init(size_t n, ...);
void           alg_linked_stack_show(FILE *stream, AlgLinkedStack *stack);
void           alg_linked_stack_clear(AlgLinkedStack *stack);
bool           alg_linked_stack_is_empty(AlgLinkedStack *stack);
bool           alg_linked_stack_peek(AlgLinkedStack *stack, alg_elem_t *e);
bool           alg_linked_stack_push(AlgLinkedStack *stack, alg_elem_t e);
bool           alg_linked_stack_pop(AlgLinkedStack *stack, alg_elem_t *e);

#endif

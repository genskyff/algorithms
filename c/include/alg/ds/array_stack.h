#ifndef ALG_ARRAY_STACK_H
#define ALG_ARRAY_STACK_H

#include "alg/core.h"
#include <stdbool.h>

// index [len - 1] is the top
typedef struct {
    alg_elem_t data[ALG_MAX_LEN];
    size_t     len;
} AlgArrayStack;

AlgArrayStack alg_array_stack_create(void);
AlgArrayStack alg_array_stack_init(size_t n, ...);
void          alg_array_stack_show(FILE *stream, AlgArrayStack *stack);
void          alg_array_stack_clear(AlgArrayStack *stack);
bool          alg_array_stack_is_empty(AlgArrayStack *stack);
bool          alg_array_stack_peek(AlgArrayStack *stack, alg_elem_t *e);
bool          alg_array_stack_push(AlgArrayStack *stack, alg_elem_t e);
bool          alg_array_stack_pop(AlgArrayStack *stack, alg_elem_t *e);

#endif

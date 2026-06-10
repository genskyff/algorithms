#ifndef ALG_ARRAY_QUEUE_H
#define ALG_ARRAY_QUEUE_H

#include "alg/core.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// index [front] is the front
// index [front + len - 1] is the rear
typedef struct {
    alg_elem_t data[ALG_MAX_LEN];
    size_t     front;
    size_t     len;
} AlgArrayQueue;

AlgArrayQueue alg_array_queue_create(void);
AlgArrayQueue alg_array_queue_init(size_t n, ...);
void          alg_array_queue_show(FILE *stream, AlgArrayQueue *queue);
void          alg_array_queue_clear(AlgArrayQueue *queue);
bool          alg_array_queue_is_empty(AlgArrayQueue *queue);
bool          alg_array_queue_front(AlgArrayQueue *queue, alg_elem_t *e);
bool          alg_array_queue_back(AlgArrayQueue *queue, alg_elem_t *e);
bool          alg_array_queue_push_front(AlgArrayQueue *queue, alg_elem_t e);
bool          alg_array_queue_push_back(AlgArrayQueue *queue, alg_elem_t e);
bool          alg_array_queue_pop_front(AlgArrayQueue *queue, alg_elem_t *e);
bool          alg_array_queue_pop_back(AlgArrayQueue *queue, alg_elem_t *e);

#endif

#ifndef ALG_DS_NODE_H
#define ALG_DS_NODE_H

#include "alg/core.h"

typedef struct AlgNode {
    alg_elem_t      data;
    struct AlgNode *prev;
    struct AlgNode *next;
} AlgNode;

typedef enum { ALG_FORWARD, ALG_BACKWARD } AlgDirection;

#endif

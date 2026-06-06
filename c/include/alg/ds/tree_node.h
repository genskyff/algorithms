#ifndef ALG_DS_TREE_NODE_H
#define ALG_DS_TREE_NODE_H

#include "alg/core.h"

typedef struct AlgTreeNode {
    alg_elem_t          data;
    size_t              level;
    struct AlgTreeNode *left;
    struct AlgTreeNode *right;
} AlgTreeNode;

typedef enum {
    ALG_LEVEL_ORDER,
    ALG_PRE_ORDER,
    ALG_IN_ORDER,
    ALG_POST_ORDER,
} AlgOrder;

#endif

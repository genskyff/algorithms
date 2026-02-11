#ifndef ALG_BINARY_TREE_H
#define ALG_BINARY_TREE_H

#include "alg/type.h"
#include <stdbool.h>

typedef struct {
    TreeNode *root;
    size_t    height;
    size_t    vertex_count;
    size_t    edge_count;
} BinaryTree;

BinaryTree create(void);
BinaryTree create_root(elem_t e);
BinaryTree init(size_t n, ...);
void       show(FILE *stream, BinaryTree *list);
void       clear(BinaryTree *tree);
bool       is_empty(BinaryTree *tree);

#endif

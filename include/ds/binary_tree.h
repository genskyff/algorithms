#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "type.h"
#include <stdbool.h>

typedef struct {
    TreeNode *root;
    size_t    vertex_count;
    size_t    edge_count;
} BinaryTree;

BinaryTree create(void);
BinaryTree create_root(elem_t data);
BinaryTree init(size_t n, ...);
void       clear(BinaryTree *tree);
bool       is_empty(BinaryTree *tree);

#endif

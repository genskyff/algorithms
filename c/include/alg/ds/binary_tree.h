#ifndef ALG_BINARY_TREE_H
#define ALG_BINARY_TREE_H

#include "alg/ds/tree_node.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    AlgTreeNode *root;
    size_t       height;
    size_t       vertex_count;
    size_t       edge_count;
} AlgBinaryTree;

AlgBinaryTree alg_binary_tree_create(void);
AlgBinaryTree alg_binary_tree_create_root(alg_elem_t e);
AlgBinaryTree alg_binary_tree_from_array(const alg_elem_t *arr, size_t len);
void          alg_binary_tree_show(FILE *stream, const AlgBinaryTree *tree);
void          alg_binary_tree_clear(AlgBinaryTree *tree);
bool          alg_binary_tree_is_empty(const AlgBinaryTree *tree);

#endif

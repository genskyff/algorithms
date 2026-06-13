#include "alg/ds/binary_tree.h"
#include <stdarg.h>
#include <stdlib.h>

static AlgTreeNode *binary_tree_create_node(alg_elem_t e, AlgTreeNode *left,
                                            AlgTreeNode *right);

static AlgTreeNode *binary_tree_create_node(alg_elem_t e, AlgTreeNode *left,
                                            AlgTreeNode *right) {
    AlgTreeNode *node = (AlgTreeNode *)malloc(sizeof(AlgTreeNode));

    node->data  = e;
    node->left  = left;
    node->right = right;

    return node;
}

AlgBinaryTree alg_binary_tree_create(void) {
    AlgBinaryTree tree = {
        .root = NULL, .height = 0, .vertex_count = 0, .edge_count = 0};

    return tree;
}

AlgBinaryTree alg_binary_tree_create_root(alg_elem_t e) {
    AlgTreeNode  *root = binary_tree_create_node(e, NULL, NULL);
    AlgBinaryTree tree = {
        .root = root, .height = 0, .vertex_count = 1, .edge_count = 0};

    return tree;
}

AlgBinaryTree alg_binary_tree_init(size_t n, ...);
void          alg_binary_tree_show(FILE *stream, const AlgBinaryTree *tree);
void          alg_binary_tree_clear(AlgBinaryTree *tree);

bool alg_binary_tree_is_empty(const AlgBinaryTree *tree) {
    return tree == NULL || tree->root == NULL || tree->height == 0 ||
           tree->vertex_count == 0;
}

#include "binary_tree.h"
#include "type.h"
#include "utils.h"
#include <stdarg.h>
#include <stdlib.h>

TreeNode *_create_node(elem_t e, TreeNode *left, TreeNode *right,
                       const char *location);

TreeNode *_create_node(elem_t e, TreeNode *left, TreeNode *right,
                       const char *location) {
    const char *_location =
        (location == NULL || *location == '\0') ? __func__ : location;

    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    _has_alloc_err(node, _location);

    node->data  = e;
    node->left  = left;
    node->right = right;

    return node;
}

BinaryTree create(void) {
    BinaryTree tree = {
        .root = NULL, .height = 0, .vertex_count = 0, .edge_count = 0};

    return tree;
}

BinaryTree create_root(elem_t e) {
    TreeNode  *root = _create_node(e, NULL, NULL, __func__);
    BinaryTree tree = {
        .root = root, .height = 0, .vertex_count = 1, .edge_count = 0};

    return tree;
}

BinaryTree init(size_t n, ...);
void       show(FILE *stream, BinaryTree *list);
void       clear(BinaryTree *tree);

bool is_empty(BinaryTree *tree) {
    return tree == NULL || tree->root == NULL || tree->height == 0 ||
           tree->vertex_count == 0;
}

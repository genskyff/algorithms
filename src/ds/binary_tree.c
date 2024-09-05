#include "binary_tree.h"
#include "type.h"
#include "util.h"
#include <stdarg.h>
#include <stdlib.h>

BinaryTree create(void) {
    BinaryTree tree = {.root = NULL, .vertex_count = 0, .edge_count = 0};

    return tree;
}

BinaryTree create_root(elem_t e) {
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    if (root == NULL) {
        fprintf(stderr,
                "\x1b[1;31merror: \x1b[0mfailed to allocate memory (exec "
                "\x1b[33mcreate_root\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    root->data      = e;
    root->left      = NULL;
    root->right     = NULL;
    BinaryTree tree = {.root = root, .vertex_count = 1, .edge_count = 0};

    return tree;
}

BinaryTree init(size_t n, ...);
void       clear(BinaryTree *tree);

bool is_empty(BinaryTree *tree) {
    return tree == NULL || tree->root == NULL || tree->vertex_count == 0;
}

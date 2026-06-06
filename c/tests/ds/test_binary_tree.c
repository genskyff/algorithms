#include "alg/ds/binary_tree.h"
#include "helper.h"

void test_create(void) {
    AlgBinaryTree tree = alg_binary_tree_create();
    char         *msg;

    msg = "should get a empty binary tree";
    assert_null(tree.root, msg);
    assert_eq(tree.height, 0, msg);
    assert_eq(tree.vertex_count, 0, msg);
    assert_eq(tree.edge_count, 0, msg);
}

void test_create_root(void) {
    AlgBinaryTree tree = alg_binary_tree_create_root(10);
    char         *msg;

    msg = "should get a binary tree with only one root node";
    assert_not_null(tree.root, msg);
    assert_eq(tree.root->data, 10, msg);
    assert_null(tree.root->left, msg);
    assert_null(tree.root->right, msg);
    assert_eq(tree.height, 0, msg);
    assert_eq(tree.vertex_count, 1, msg);
    assert_eq(tree.edge_count, 0, msg);
}

// void test_is_empty(void) {
//     AlgBinaryTree tree = test_data();
//     char      *msg;

//     msg = "should be empty when NULL";
//     assert(alg_binary_tree_is_empty(NULL), msg);

//     msg = "should not be empty";
//     assert_not(alg_binary_tree_is_empty(&tree), msg);

//     msg = "should be empty when len == 0";
//     alg_binary_tree_clear(&tree);
//     assert(alg_binary_tree_is_empty(&tree), msg);
// }

int main(void) {
    char *mod    = "ds";
    char *target = "binary_tree";

    run_test(test_create, mod, target, "create");
    run_test(test_create_root, mod, target, "create_root");
    // run_test(test_is_empty, mod, target, "is_empty");

    return 0;
}

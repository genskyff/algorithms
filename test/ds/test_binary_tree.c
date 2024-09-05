#include "binary_tree.h"
#include "helper.h"

void test_create(void) {
    BinaryTree tree = create();
    char      *msg;

    msg = "should get a empty binary tree";
    assert_null(tree.root, msg);
    assert_eq(tree.vertex_count, 0, msg);
    assert_eq(tree.edge_count, 0, msg);
}

void test_create_root(void) {
    BinaryTree tree = create_root(0);
    char      *msg;

    msg = "should get a binary tree with only one root node";
    assert_not_null(tree.root, msg);
    assert_eq(tree.root->data, 0, msg);
    assert_null(tree.root->left, msg);
    assert_null(tree.root->right, msg);
    assert_eq(tree.vertex_count, 1, msg);
    assert_eq(tree.edge_count, 0, msg);
}

// void test_is_empty(void) {
//     BinaryTree tree = test_data();
//     char      *msg;

//     msg = "should be empty when NULL";
//     assert(is_empty(NULL), msg);

//     msg = "should not be empty";
//     assert_not(is_empty(&tree), msg);

//     msg = "should be empty when len == 0";
//     clear(&tree);
//     assert(is_empty(&tree), msg);
// }

int main(void) {
    char *mod    = "ds";
    char *target = "binary_tree";

    run_test(test_create, mod, target, "create");
    run_test(test_create_root, mod, target, "create_root");
    // run_test(test_is_empty, mod, target, "is_empty");

    return 0;
}

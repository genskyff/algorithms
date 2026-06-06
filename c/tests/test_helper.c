#include "helper.h"

char *MSG = "should pass";

void test_assert(void) {
    assert(true, MSG);
}

void test_assert_not(void) {
    assert_not(false, MSG);
}

void test_assert_null(void) {
    assert_null(NULL, MSG);
}

void test_assert_not_null(void) {
    assert_not_null(&MSG, MSG);
}

void test_assert_eq(void) {
    assert_eq(1, 1, MSG);
}

void test_assert_ne(void) {
    assert_ne(1, 2, MSG);
}

void test_assert_str_eq(void) {
    assert_str_eq("abc", "abc", MSG);
}

void test_assert_str_ne(void) {
    assert_str_ne("abc", "abcd", MSG);
}

void test_assert_arr_eq(void) {
    alg_elem_t a[] = {0, 1, 2};
    alg_elem_t b[] = {0, 1, 2};

    assert_arr_eq(NULL, 0, NULL, 0, MSG);
    assert_arr_eq(a, 3, b, 3, MSG);
    assert_arr_eq(a, 0, b, 0, MSG);
}

void test_assert_arr_ne(void) {
    alg_elem_t a[] = {0, 1, 2};
    alg_elem_t b[] = {0, 1, 3};

    assert_arr_ne(NULL, 0, b, 3, MSG);
    assert_arr_ne(a, 3, NULL, 0, MSG);
    assert_arr_ne(a, 3, b, 2, MSG);
}

void test_assert_list_eq(void) {
    AlgNode head1 = {.data = 1, .prev = NULL, .next = NULL};
    AlgNode tail1 = {.data = 2, .prev = &head1, .next = NULL};
    head1.next    = &tail1;

    AlgNode head2 = {.data = 1, .prev = NULL, .next = NULL};
    AlgNode tail2 = {.data = 2, .prev = &head2, .next = NULL};
    head2.next    = &tail2;

    assert_list_eq(NULL, NULL, ALG_FORWARD, NULL);
    assert_list_eq(&head1, &head2, ALG_FORWARD, MSG);
}

void test_assert_list_ne(void) {
    AlgNode head1 = {.data = 1, .prev = NULL, .next = NULL};
    AlgNode tail1 = {.data = 2, .prev = &head1, .next = NULL};
    head1.next    = &tail1;

    AlgNode head2 = {.data = 1, .prev = NULL, .next = NULL};
    AlgNode tail2 = {.data = 3, .prev = &head2, .next = NULL};
    head2.next    = &tail2;

    AlgNode head3 = {.data = 1, .prev = NULL, .next = NULL};
    AlgNode n     = {.data = 2, .prev = &head3, .next = NULL};
    head3.next    = &n;
    AlgNode tail3 = {.data = 3, .prev = &n, .next = NULL};
    n.next        = &tail3;

    assert_list_ne(NULL, &head2, ALG_FORWARD, MSG);
    assert_list_ne(&head1, NULL, ALG_FORWARD, MSG);
    assert_list_ne(&head1, &head2, ALG_FORWARD, MSG);
    assert_list_ne(&head1, &head3, ALG_FORWARD, MSG);
}

void test_assert_list_arr_eq(void) {
    AlgNode head = {.data = 1, .prev = NULL, .next = NULL};
    AlgNode n    = {.data = 2, .prev = &head, .next = NULL};
    head.next    = &n;
    AlgNode tail = {.data = 3, .prev = &n, .next = NULL};
    n.next       = &tail;

    alg_elem_t arr[] = {1, 2, 3};

    assert_list_arr_eq(NULL, ALG_FORWARD, NULL, 0, MSG);
    assert_list_arr_eq(&head, ALG_FORWARD, arr, 3, MSG);
}

void test_assert_list_arr_ne(void) {
    AlgNode head = {.data = 1, .prev = NULL, .next = NULL};
    AlgNode n    = {.data = 2, .prev = &head, .next = NULL};
    head.next    = &n;
    AlgNode tail = {.data = 3, .prev = &n, .next = NULL};
    n.next       = &tail;

    alg_elem_t arr[]  = {1, 2, 4};
    alg_elem_t arr2[] = {1, 2, 3, 4};

    assert_list_arr_ne(NULL, ALG_FORWARD, arr, 3, MSG);
    assert_list_arr_ne(&head, ALG_FORWARD, NULL, 0, MSG);
    assert_list_arr_ne(&head, ALG_FORWARD, arr, 3, MSG);
    assert_list_arr_ne(&head, ALG_FORWARD, arr2, 4, MSG);
}

int main(void) {
    char *mod    = NULL;
    char *target = "helper";

    run_test(test_assert, mod, target, "assert");
    run_test(test_assert_not, mod, target, "assert_not");
    run_test(test_assert_null, mod, target, "assert_null");
    run_test(test_assert_not_null, mod, target, "assert_not_null");
    run_test(test_assert_eq, mod, target, "assert_eq");
    run_test(test_assert_ne, mod, target, "assert_ne");
    run_test(test_assert_str_eq, mod, target, "assert_str_eq");
    run_test(test_assert_str_ne, mod, target, "assert_str_ne");
    run_test(test_assert_arr_eq, mod, target, "assert_arr_eq");
    run_test(test_assert_arr_ne, mod, target, "assert_arr_ne");
    run_test(test_assert_list_eq, mod, target, "assert_list_eq");
    run_test(test_assert_list_ne, mod, target, "assert_list_ne");
    run_test(test_assert_list_arr_eq, mod, target, "assert_list_arr_eq");
    run_test(test_assert_list_arr_ne, mod, target, "assert_list_arr_ne");

    return 0;
}

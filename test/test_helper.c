#include "helper.h"

char *MSG = "should pass";

void test_assert(void) {
    assert(true, MSG);
}

void test_assert_not(void) {
    assert_not(false, MSG);
}

void test_assert_eq(void) {
    assert_eq(1, 1, MSG);
}

void test_assert_ne(void) {
    assert_ne(1, 2, MSG);
}

void test_assert_arr_eq(void) {
    elem_t a[] = {0, 1, 2};
    elem_t b[] = {0, 1, 2};

    assert_arr_eq(NULL, 0, NULL, 0, MSG);
    assert_arr_eq(a, 3, b, 3, MSG);
    assert_arr_eq(a, 0, b, 0, MSG);
}

void test_assert_arr_ne(void) {
    elem_t a[] = {0, 1, 2};
    elem_t b[] = {0, 1, 3};

    assert_arr_ne(NULL, 0, b, 3, MSG);
    assert_arr_ne(a, 3, NULL, 0, MSG);
    assert_arr_ne(a, 3, b, 2, MSG);
}

void test_assert_list_eq(void) {
    Node head1 = {.data = 1, .prev = NULL, .next = NULL};
    Node tail1 = {.data = 2, .prev = &head1, .next = NULL};
    head1.next = &tail1;

    Node head2 = {.data = 1, .prev = NULL, .next = NULL};
    Node tail2 = {.data = 2, .prev = &head2, .next = NULL};
    head2.next = &tail2;

    assert_list_eq(NULL, NULL, NULL);
    assert_list_eq(&head1, &head2, MSG);
}

void test_assert_list_ne(void) {
    Node head1 = {.data = 1, .prev = NULL, .next = NULL};
    Node tail1 = {.data = 2, .prev = &head1, .next = NULL};
    head1.next = &tail1;

    Node head2 = {.data = 1, .prev = NULL, .next = NULL};
    Node tail2 = {.data = 3, .prev = &head2, .next = NULL};
    head2.next = &tail2;

    Node head3 = {.data = 1, .prev = NULL, .next = NULL};
    Node n     = {.data = 2, .prev = &head3, .next = NULL};
    head3.next = &n;
    Node tail3 = {.data = 3, .prev = &n, .next = NULL};
    n.next     = &tail3;

    assert_list_ne(NULL, &head2, MSG);
    assert_list_ne(&head1, NULL, MSG);
    assert_list_ne(&head1, &head2, MSG);
    assert_list_ne(&head1, &head3, MSG);
}

void test_assert_list_arr_eq(void) {
    Node head = {.data = 1, .prev = NULL, .next = NULL};
    Node n    = {.data = 2, .prev = &head, .next = NULL};
    head.next = &n;
    Node tail = {.data = 3, .prev = &n, .next = NULL};
    n.next    = &tail;

    elem_t arr[] = {1, 2, 3};

    assert_list_arr_eq(NULL, NULL, 0, MSG);
    assert_list_arr_eq(&head, arr, 3, MSG);
}

void test_assert_list_arr_ne(void) {
    Node head = {.data = 1, .prev = NULL, .next = NULL};
    Node n    = {.data = 2, .prev = &head, .next = NULL};
    head.next = &n;
    Node tail = {.data = 3, .prev = &n, .next = NULL};
    n.next    = &tail;

    elem_t arr[]  = {1, 2, 4};
    elem_t arr2[] = {1, 2, 3, 4};

    assert_list_arr_ne(NULL, arr, 3, MSG);
    assert_list_arr_ne(&head, NULL, 0, MSG);
    assert_list_arr_ne(&head, arr, 3, MSG);
    assert_list_arr_ne(&head, arr2, 4, MSG);
}

int main(void) {
    char *prefix = "helper";
    run_test(test_assert, prefix, "test_assert");
    run_test(test_assert_not, prefix, "test_assert_not");
    run_test(test_assert_eq, prefix, "test_assert_eq");
    run_test(test_assert_ne, prefix, "test_assert_ne");
    run_test(test_assert_arr_eq, prefix, "test_assert_arr_eq");
    run_test(test_assert_arr_ne, prefix, "test_assert_arr_ne");
    run_test(test_assert_list_eq, prefix, "test_assert_list_eq");
    run_test(test_assert_list_ne, prefix, "test_assert_list_ne");
    run_test(test_assert_list_arr_eq, prefix, "test_assert_list_arr_eq");
    run_test(test_assert_list_arr_ne, prefix, "test_assert_list_arr_ne");

    return 0;
}

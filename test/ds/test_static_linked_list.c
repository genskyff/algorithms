#include "helper.h"
#include "static_linked_list.h"
#include <stdint.h>

#define LEN 6
#define TEST_DATA(...)                                                         \
    SLinkedList test_data() {                                                  \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    SLinkedList list = create();
    char       *msg;

    msg = "should get a empty static linked list";
    assert_eq(list.space, 0, msg);
    assert_eq(list.head, SIZE_MAX, msg);
    assert_eq(list.tail, SIZE_MAX, msg);
    assert_eq(list.len, 0, msg);

    msg = "all nodes should be linked together";
    for (size_t i = 0, cur = list.space; cur != SIZE_MAX; i++) {
        assert_eq(cur, i, msg);
        assert_eq(list.node[list.space].prev, SIZE_MAX, msg);
        cur = list.node[cur].next;
    }
}

void test_init(void) {
    SLinkedList list     = init(LEN, 0, 1, 2, 3, 4, 5);
    elem_t      tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char       *msg;

    msg = "should get a initialized static linked list";
    assert_eq(list.space, LEN, msg);
    assert_eq(list.head, 0, msg);
    assert_eq(list.tail, LEN - 1, msg);
    assert_eq(list.len, LEN, msg);
    assert_arr_eq(tmp, LEN, to_array(&list), LEN, msg);

    msg = "all nodes should be linked together";
    for (size_t i = 0, cur = list.head; cur != SIZE_MAX; i++) {
        assert_eq(list.node[cur].data, i, msg);
        assert_eq(list.node[cur].prev, cur == list.head ? SIZE_MAX : cur - 1,
                  msg);
        assert_eq(list.node[cur].next, cur == list.tail ? SIZE_MAX : cur + 1,
                  msg);
        cur = list.node[cur].next;
    }
}

void test_to_array(void) {
    SLinkedList list = test_data();
    char       *msg;

    msg             = "should get an array";
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_arr_eq(to_array(&list), LEN, tmp, LEN, msg);

    msg = "should get NULL when empty";
    clear(&list);
    assert(to_array(&list) == NULL, msg);
}

void test_swap(void) {
    SLinkedList list     = test_data();
    elem_t      tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char       *msg;

    msg = "should not swap when i == j";
    swap(&list, 1, 1);
    assert_arr_eq(tmp, LEN, to_array(&list), LEN, msg);

    msg = "should not swap when out of range";
    swap(&list, 0, LEN);
    assert_arr_eq(tmp, LEN, to_array(&list), LEN, msg);

    msg = "should swap";
    swap(&list, 0, list.len - 1);
    elem_t swap_endpoint[LEN] = {5, 1, 2, 3, 4, 0};
    assert_arr_eq(swap_endpoint, LEN, to_array(&list), LEN, msg);
}

void test_reverse(void) {
    SLinkedList list = test_data();
    char       *msg;

    msg = "should reverse";
    reverse(&list);
    elem_t rev[LEN] = {5, 4, 3, 2, 1, 0};
    assert_arr_eq(rev, LEN, to_array(&list), LEN, msg);
}

void test_clear(void) {
    SLinkedList list = test_data();

    char *msg = "should clear";
    clear(&list);
    assert_eq(list.space, 0, msg);
    assert_eq(list.head, SIZE_MAX, msg);
    assert_eq(list.tail, SIZE_MAX, msg);
    assert_eq(list.len, 0, msg);

    msg = "all nodes should be linked together";
    for (size_t i = 0, cur = list.space; cur != SIZE_MAX; i++) {
        assert_eq(cur, i, msg);
        assert_eq(list.node[list.space].prev, SIZE_MAX, msg);
        cur = list.node[cur].next;
    }
}

void test_is_empty(void) {
    SLinkedList list = test_data();
    char       *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(is_empty(&list), msg);

    msg = "should be empty when len == 0";
    clear(&list);
    assert(is_empty(&list), msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "static_linked_list";

    run_test(test_create, mod, target, "test_create");
    run_test(test_init, mod, target, "test_init");
    run_test(test_to_array, mod, target, "test_to_array");
    run_test(test_swap, mod, target, "test_swap");
    run_test(test_reverse, mod, target, "test_reverse");
    run_test(test_clear, mod, target, "test_clear");
    run_test(test_is_empty, mod, target, "test_is_empty");

    return 0;
}

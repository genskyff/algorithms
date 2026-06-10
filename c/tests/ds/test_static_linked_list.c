#include "alg/ds/static_linked_list.h"
#include "support/helper.h"
#include <stdint.h>

#define LEN 6
#define TEST_DATA(...)                                                         \
    AlgStaticLinkedList test_data() {                                          \
        return alg_static_linked_list_init(LEN, __VA_ARGS__);                  \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    AlgStaticLinkedList list = alg_static_linked_list_create();
    char               *msg;

    msg = "should get a empty static linked list";
    assert_eq(list.space, 0, msg);
    assert(list.head == SIZE_MAX, msg);
    assert(list.tail == SIZE_MAX, msg);
    assert_eq(list.len, 0, msg);

    msg = "all nodes should be linked together";
    for (size_t i = 0, cur = list.space; cur != SIZE_MAX; i++) {
        assert_eq(cur, i, msg);
        assert(list.nodes[list.space].prev == SIZE_MAX, msg);
        cur = list.nodes[cur].next;
    }
}

void test_init(void) {
    AlgStaticLinkedList list =
        alg_static_linked_list_init(LEN, 0, 1, 2, 3, 4, 5);
    alg_elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char      *msg;

    msg = "should get a initialized static linked list";
    assert_eq(list.space, LEN, msg);
    assert_eq(list.head, 0, msg);
    assert_eq(list.tail, LEN - 1, msg);
    assert_eq(list.len, LEN, msg);
    assert_arr_eq(tmp, LEN, alg_static_linked_list_to_array(&list), LEN, msg);

    msg = "all nodes should be linked together";
    for (size_t i = 0, cur = list.head; cur != SIZE_MAX; i++) {
        assert_eq(list.nodes[cur].data, i, msg);
        assert(list.nodes[cur].prev == (cur == list.head ? SIZE_MAX : cur - 1),
               msg);
        assert(list.nodes[cur].next == (cur == list.tail ? SIZE_MAX : cur + 1),
               msg);
        cur = list.nodes[cur].next;
    }
}

void test_to_array(void) {
    AlgStaticLinkedList list = test_data();
    char               *msg;

    msg                 = "should get an array";
    alg_elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_arr_eq(alg_static_linked_list_to_array(&list), LEN, tmp, LEN, msg);

    msg = "should get NULL when empty";
    alg_static_linked_list_clear(&list);
    assert_null(alg_static_linked_list_to_array(&list), msg);
}

void test_swap(void) {
    AlgStaticLinkedList list     = test_data();
    alg_elem_t          tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char               *msg;

    msg = "should not swap when i == j";
    alg_static_linked_list_swap(&list, 1, 1);
    assert_arr_eq(tmp, LEN, alg_static_linked_list_to_array(&list), LEN, msg);

    msg = "should not swap when out of range";
    alg_static_linked_list_swap(&list, 0, LEN);
    assert_arr_eq(tmp, LEN, alg_static_linked_list_to_array(&list), LEN, msg);

    msg = "should swap head and tail";
    alg_static_linked_list_swap(&list, 0, list.len - 1);
    alg_elem_t swap_either_end[LEN] = {5, 1, 2, 3, 4, 0};
    assert_arr_eq(swap_either_end, LEN, alg_static_linked_list_to_array(&list),
                  LEN, msg);

    msg = "should swap when |i - j| == 1";
    alg_static_linked_list_swap(&list, 0, 1);
    alg_elem_t swap_adjacent[LEN] = {1, 5, 2, 3, 4, 0};
    assert_arr_eq(swap_adjacent, LEN, alg_static_linked_list_to_array(&list),
                  LEN, msg);
    assert_eq(list.nodes[list.tail].data, 0, msg);

    msg = "should swap when i == 0, j > 1";
    alg_static_linked_list_swap(&list, 0, 3);
    alg_elem_t swap_head[LEN] = {3, 5, 2, 1, 4, 0};
    assert_arr_eq(swap_head, LEN, alg_static_linked_list_to_array(&list), LEN,
                  msg);
    assert_eq(list.nodes[list.tail].data, 0, msg);

    msg = "should swap when i > 0, j == len - 1";
    alg_static_linked_list_swap(&list, 1, list.len - 1);
    alg_elem_t swap_tail[LEN] = {3, 0, 2, 1, 4, 5};
    assert_arr_eq(swap_tail, LEN, alg_static_linked_list_to_array(&list), LEN,
                  msg);
    assert_eq(list.nodes[list.tail].data, 5, msg);
}

void test_reverse(void) {
    AlgStaticLinkedList list = test_data();
    char               *msg;

    msg = "should reverse";
    alg_static_linked_list_reverse(&list);
    alg_elem_t rev[LEN] = {5, 4, 3, 2, 1, 0};
    assert_arr_eq(rev, LEN, alg_static_linked_list_to_array(&list), LEN, msg);
}

void test_clear(void) {
    AlgStaticLinkedList list = test_data();
    char               *msg;

    msg = "should clear";
    alg_static_linked_list_clear(&list);
    assert_eq(list.space, 0, msg);
    assert(list.head == SIZE_MAX, msg);
    assert(list.tail == SIZE_MAX, msg);
    assert_eq(list.len, 0, msg);

    msg = "all nodes should be linked together";
    for (size_t i = 0, cur = list.space; cur != SIZE_MAX; i++) {
        assert_eq(cur, i, msg);
        assert(list.nodes[list.space].prev == SIZE_MAX, msg);
        cur = list.nodes[cur].next;
    }
}

void test_is_empty(void) {
    AlgStaticLinkedList list = test_data();
    char               *msg;

    msg = "should be empty when NULL";
    assert(alg_static_linked_list_is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(alg_static_linked_list_is_empty(&list), msg);

    msg = "should be empty when len == 0";
    alg_static_linked_list_clear(&list);
    assert(alg_static_linked_list_is_empty(&list), msg);
}

void test_get(void) {
    AlgStaticLinkedList list = test_data();
    alg_elem_t          e;
    char               *msg;

    msg = "should not get when out of range";
    assert_not(alg_static_linked_list_get(&list, list.len, &e), msg);

    msg = "should get";
    assert(alg_static_linked_list_get(&list, list.len - 1, &e), msg);
    assert_eq(e, list.nodes[list.tail].data, msg);

    msg = "should not get when empty";
    alg_static_linked_list_clear(&list);
    assert_not(alg_static_linked_list_get(&list, 0, &e), msg);
}

void test_first(void) {
    AlgStaticLinkedList list = test_data();
    alg_elem_t          e;
    char               *msg;

    msg = "should get first";
    assert(alg_static_linked_list_first(&list, &e), msg);
    assert_eq(e, list.nodes[list.head].data, msg);

    msg = "should not get first when empty";
    alg_static_linked_list_clear(&list);
    assert_not(alg_static_linked_list_first(&list, &e), msg);
}

void test_last(void) {
    AlgStaticLinkedList list = test_data();
    alg_elem_t          e;
    char               *msg;

    msg = "should get last";
    assert(alg_static_linked_list_last(&list, &e), msg);
    assert_eq(e, list.nodes[list.tail].data, msg);

    msg = "should not get last when empty";
    alg_static_linked_list_clear(&list);
    assert_not(alg_static_linked_list_last(&list, &e), msg);
}

void test_set(void) {
    AlgStaticLinkedList list = test_data();
    alg_elem_t          e    = 999;
    char               *msg;

    msg = "should not set when out of range";
    assert_not(alg_static_linked_list_set(&list, list.len, e), msg);
    assert_not(alg_static_linked_list_find(&list, e, NULL), msg);

    msg = "should set";
    assert(alg_static_linked_list_set(&list, list.len - 1, e), msg);
    assert_eq(list.nodes[list.tail].data, e, msg);

    msg = "should not set when empty";
    alg_static_linked_list_clear(&list);
    assert_not(alg_static_linked_list_set(&list, 0, e), msg);
}

void test_find(void) {
    AlgStaticLinkedList list = test_data();
    size_t              i;
    char               *msg;

    msg = "should find at head";
    assert(alg_static_linked_list_find(&list, 0, &i), msg);
    assert_eq(i, 0, msg);

    msg = "should find at tail";
    assert(alg_static_linked_list_find(&list, 5, &i), msg);
    assert_eq(i, 5, msg);

    msg = "should not find when no exist";
    i   = 0;
    assert_not(alg_static_linked_list_find(&list, 999, &i), msg);
    assert_eq(i, 0, msg);
}

void test_insert(void) {
    AlgStaticLinkedList list = test_data();
    alg_elem_t          e    = 999;
    char               *msg;

    msg = "should not insert when out of range";
    assert_not(alg_static_linked_list_insert(&list, list.len + 1, ++e), msg);
    assert_eq(list.len, LEN, msg);
    assert_not(alg_static_linked_list_find(&list, e, NULL), msg);

    msg = "should insert at head";
    assert(alg_static_linked_list_insert(&list, 0, ++e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.nodes[list.head].data, e, msg);

    msg = "should insert at middle";
    assert(alg_static_linked_list_insert(&list, list.len / 2, ++e), msg);
    assert_eq(list.len, LEN + 2, msg);
    alg_elem_t mid;
    assert(alg_static_linked_list_get(&list, list.len / 2, &mid), msg);
    assert_eq(mid, e, msg);

    msg = "should insert at tail";
    assert(alg_static_linked_list_insert(&list, list.len, ++e), msg);
    assert_eq(list.len, LEN + 3, msg);
    assert_eq(list.nodes[list.tail].data, e, msg);

    msg      = "should not insert when full";
    list.len = ALG_MAX_LEN;
    assert_not(alg_static_linked_list_insert(&list, 0, ++e), msg);
    assert_eq(list.len, ALG_MAX_LEN, msg);

    msg = "should insert when empty";
    alg_static_linked_list_clear(&list);
    assert(alg_static_linked_list_insert(&list, 0, ++e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.nodes[list.head].data, e, msg);
    assert_eq(list.nodes[list.tail].data, e, msg);
}

void test_push_front(void) {
    AlgStaticLinkedList list = test_data();
    alg_elem_t          e    = 999;
    char               *msg;

    msg = "should push_front";
    assert(alg_static_linked_list_push_front(&list, e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.nodes[list.head].data, e, msg);

    msg      = "should not push_front when full";
    list.len = ALG_MAX_LEN;
    assert_not(alg_static_linked_list_push_front(&list, e), msg);
    assert_eq(list.len, ALG_MAX_LEN, msg);

    msg = "should push_front when empty";
    alg_static_linked_list_clear(&list);
    assert(alg_static_linked_list_push_front(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.nodes[list.head].data, e, msg);
    assert_eq(list.nodes[list.tail].data, e, msg);
}

void test_push_back(void) {
    AlgStaticLinkedList list = test_data();
    alg_elem_t          e    = 999;
    char               *msg;

    msg = "should push_back";
    assert(alg_static_linked_list_push_back(&list, e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.nodes[list.tail].data, e, msg);

    msg      = "should not push_back when full";
    list.len = ALG_MAX_LEN;
    assert_not(alg_static_linked_list_push_back(&list, e), msg);
    assert_eq(list.len, ALG_MAX_LEN, msg);

    msg = "should push_back when empty";
    alg_static_linked_list_clear(&list);
    assert(alg_static_linked_list_push_back(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.nodes[list.head].data, e, msg);
    assert_eq(list.nodes[list.tail].data, e, msg);
}

void test_del(void) {
    AlgStaticLinkedList list = test_data();
    alg_elem_t          e;
    alg_elem_t          deleted;
    char               *msg;

    msg = "should not del when out of range";
    assert_not(alg_static_linked_list_del(&list, list.len, NULL), msg);
    assert_eq(list.len, LEN, msg);

    msg     = "should del at head";
    deleted = list.nodes[list.head].data;
    assert(alg_static_linked_list_del(&list, 0, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, deleted, msg);

    msg = "should del at middle";
    assert(alg_static_linked_list_get(&list, list.len / 2, &deleted), msg);
    assert(alg_static_linked_list_del(&list, list.len / 2, &e), msg);
    assert_eq(list.len, LEN - 2, msg);
    assert_eq(e, deleted, msg);

    msg     = "should del at tail";
    deleted = list.nodes[list.tail].data;
    assert(alg_static_linked_list_del(&list, list.len - 1, &e), msg);
    assert_eq(list.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not del when empty";
    alg_static_linked_list_clear(&list);
    assert_not(alg_static_linked_list_del(&list, 0, NULL), msg);
    assert_eq(list.len, 0, msg);

    msg = "should delete when len == 1";
    assert(alg_static_linked_list_push_back(&list, 999), msg);
    assert(alg_static_linked_list_del(&list, 0, &e), msg);
    assert_eq(list.len, 0, msg);
    assert(list.head == SIZE_MAX, msg);
    assert(list.tail == SIZE_MAX, msg);
}

void test_pop_front(void) {
    AlgStaticLinkedList list = test_data();
    alg_elem_t          e;
    alg_elem_t          popped;
    char               *msg;

    msg    = "should pop_front";
    popped = list.nodes[list.head].data;
    assert(alg_static_linked_list_pop_front(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    alg_static_linked_list_clear(&list);
    assert_not(alg_static_linked_list_pop_front(&list, NULL), msg);
    assert_eq(list.len, 0, msg);
}

void test_pop_back(void) {
    AlgStaticLinkedList list = test_data();
    alg_elem_t          e;
    alg_elem_t          popped;
    char               *msg;

    msg    = "should pop_back";
    popped = list.nodes[list.tail].data;
    assert(alg_static_linked_list_pop_back(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    alg_static_linked_list_clear(&list);
    assert_not(alg_static_linked_list_pop_back(&list, NULL), msg);
    assert_eq(list.len, 0, msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "static_linked_list";

    run_test(test_create, mod, target, "create");
    run_test(test_init, mod, target, "init");
    run_test(test_to_array, mod, target, "to_array");
    run_test(test_swap, mod, target, "swap");
    run_test(test_reverse, mod, target, "reverse");
    run_test(test_clear, mod, target, "clear");
    run_test(test_is_empty, mod, target, "is_empty");
    run_test(test_get, mod, target, "get");
    run_test(test_first, mod, target, "first");
    run_test(test_last, mod, target, "last");
    run_test(test_set, mod, target, "set");
    run_test(test_find, mod, target, "find");
    run_test(test_insert, mod, target, "insert");
    run_test(test_push_front, mod, target, "push_front");
    run_test(test_push_back, mod, target, "push_back");
    run_test(test_del, mod, target, "del");
    run_test(test_pop_front, mod, target, "pop_front");
    run_test(test_pop_back, mod, target, "pop_back");

    return 0;
}

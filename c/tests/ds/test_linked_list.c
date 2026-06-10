#include "alg/ds/linked_list.h"
#include "support/helper.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    AlgLinkedList test_data() {                                                \
        return alg_linked_list_init(LEN, __VA_ARGS__);                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    AlgLinkedList list = alg_linked_list_create();
    char         *msg;

    msg = "should get a empty linked list";
    assert_null(list.head, msg);
    assert_null(list.tail, msg);
    assert_eq(list.len, 0, msg);
}

void test_init(void) {
    AlgLinkedList list = alg_linked_list_init(LEN, 0, 1, 2, 3, 4, 5);
    char         *msg;

    msg = "should get a initialized linked list";
    assert_not_null(list.head, msg);
    assert_not_null(list.tail, msg);
    assert_eq(list.len, LEN, msg);
    alg_elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_list_arr_eq(list.head, ALG_FORWARD, tmp, LEN, msg);
    assert_eq(list.tail->data, 5, msg);
}

void test_swap(void) {
    AlgLinkedList list     = test_data();
    alg_elem_t    tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char         *msg;

    msg = "should not swap when NULL";
    alg_linked_list_swap(NULL, 0, 1);

    msg = "should not swap when i == j";
    alg_linked_list_swap(&list, 1, 1);
    assert_list_arr_eq(list.head, ALG_FORWARD, tmp, LEN, msg);

    msg = "should not swap when out of range";
    alg_linked_list_swap(&list, 0, LEN);
    assert_list_arr_eq(list.head, ALG_FORWARD, tmp, LEN, msg);

    msg = "should swap head and tail";
    alg_linked_list_swap(&list, 0, list.len - 1);
    alg_elem_t swap_either_end[LEN] = {5, 1, 2, 3, 4, 0};
    assert_list_arr_eq(list.head, ALG_FORWARD, swap_either_end, LEN, msg);
    assert_eq(list.tail->data, 0, msg);

    msg = "should swap when |i - j| == 1";
    alg_linked_list_swap(&list, 0, 1);
    alg_elem_t swap_adjacent[LEN] = {1, 5, 2, 3, 4, 0};
    assert_list_arr_eq(list.head, ALG_FORWARD, swap_adjacent, LEN, msg);
    assert_eq(list.tail->data, 0, msg);

    msg = "should swap when i == 0, j > 1";
    alg_linked_list_swap(&list, 0, 3);
    alg_elem_t swap_front[LEN] = {3, 5, 2, 1, 4, 0};
    assert_list_arr_eq(list.head, ALG_FORWARD, swap_front, LEN, msg);
    assert_eq(list.tail->data, 0, msg);

    msg = "should swap when i > 0, j == len - 1";
    alg_linked_list_swap(&list, 1, list.len - 1);
    alg_elem_t swap_tail[LEN] = {3, 0, 2, 1, 4, 5};
    assert_list_arr_eq(list.head, ALG_FORWARD, swap_tail, LEN, msg);
    assert_eq(list.tail->data, 5, msg);
}

void test_reverse(void) {
    AlgLinkedList list = test_data();
    char         *msg;

    msg = "should reverse";
    alg_linked_list_reverse(&list);
    alg_elem_t rev[LEN] = {5, 4, 3, 2, 1, 0};
    assert_list_arr_eq(list.head, ALG_FORWARD, rev, LEN, msg);
    assert_eq(list.tail->data, 0, msg);
}

void test_clear(void) {
    AlgLinkedList list = test_data();
    char         *msg;

    msg = "should clear";
    alg_linked_list_clear(&list);
    assert_null(list.head, msg);
    assert_null(list.tail, msg);
    assert_eq(list.len, 0, msg);
}

void test_is_empty(void) {
    AlgLinkedList list = test_data();
    char         *msg;

    msg = "should be empty when NULL";
    assert(alg_linked_list_is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(alg_linked_list_is_empty(&list), msg);

    msg = "should be empty when len == 0";
    alg_linked_list_clear(&list);
    assert(alg_linked_list_is_empty(&list), msg);
}

void test_get(void) {
    AlgLinkedList list = test_data();
    alg_elem_t    e;
    char         *msg;

    msg = "should not get when NULL";
    assert_not(alg_linked_list_get(NULL, 0, NULL), msg);

    msg = "should not get when out of range";
    assert_not(alg_linked_list_get(&list, list.len, &e), msg);

    msg = "should get";
    assert(alg_linked_list_get(&list, list.len - 1, &e), msg);
    assert_eq(e, list.tail->data, msg);

    msg = "should not get when empty";
    alg_linked_list_clear(&list);
    assert_not(alg_linked_list_get(&list, 0, &e), msg);
}

void test_first(void) {
    AlgLinkedList list = test_data();
    alg_elem_t    e;
    char         *msg;

    msg = "should not get first when NULL";
    assert_not(alg_linked_list_first(NULL, NULL), msg);

    msg = "should get first";
    assert(alg_linked_list_first(&list, &e), msg);
    assert_eq(e, list.head->data, msg);

    msg = "should not get first when empty";
    alg_linked_list_clear(&list);
    assert_not(alg_linked_list_first(&list, &e), msg);
}

void test_last(void) {
    AlgLinkedList list = test_data();
    alg_elem_t    e;
    char         *msg;

    msg = "should not get last when NULL";
    assert_not(alg_linked_list_last(NULL, NULL), msg);

    msg = "should get last";
    assert(alg_linked_list_last(&list, &e), msg);
    assert_eq(e, list.tail->data, msg);

    msg = "should not get last when empty";
    alg_linked_list_clear(&list);
    assert_not(alg_linked_list_last(&list, &e), msg);
}

void test_set(void) {
    AlgLinkedList list = test_data();
    alg_elem_t    e    = 999;
    char         *msg;

    msg = "should not set when NULL";
    assert_not(alg_linked_list_set(NULL, 0, e), msg);

    msg = "should not set when out of range";
    assert_not(alg_linked_list_set(&list, list.len, e), msg);
    assert_not(alg_linked_list_find(&list, e, NULL), msg);

    msg = "should set";
    assert(alg_linked_list_set(&list, list.len - 1, e), msg);
    assert_eq(list.tail->data, e, msg);

    msg = "should not set when empty";
    alg_linked_list_clear(&list);
    assert_not(alg_linked_list_set(&list, 0, e), msg);
}

void test_find(void) {
    AlgLinkedList list = test_data();
    size_t        i;
    char         *msg;

    msg = "should not find when NULL";
    assert_not(alg_linked_list_find(NULL, 0, NULL), msg);

    msg = "should find at head";
    assert(alg_linked_list_find(&list, 0, &i), msg);
    assert_eq(i, 0, msg);

    msg = "should find at tail";
    assert(alg_linked_list_find(&list, list.tail->data, &i), msg);
    assert_eq(i, list.len - 1, msg);

    msg = "should not find when no exist";
    i   = 0;
    assert_not(alg_linked_list_find(&list, 999, &i), msg);
    assert_eq(i, 0, msg);
}

void test_insert(void) {
    AlgLinkedList list = test_data();
    alg_elem_t    e    = 999;
    char         *msg;

    msg = "should not insert when NULL";
    assert_not(alg_linked_list_insert(NULL, 0, e), msg);

    msg = "should not insert when out of range";
    assert_not(alg_linked_list_insert(&list, list.len + 1, ++e), msg);
    assert_eq(list.len, LEN, msg);
    assert_not(alg_linked_list_find(&list, e, NULL), msg);

    msg = "should insert at head";
    assert(alg_linked_list_insert(&list, 0, ++e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.head->data, e, msg);

    msg = "should insert at middle";
    assert(alg_linked_list_insert(&list, list.len / 2, ++e), msg);
    assert_eq(list.len, LEN + 2, msg);
    alg_elem_t mid;
    assert(alg_linked_list_get(&list, (list.len - 1) / 2, &mid), msg);
    assert_eq(mid, e, msg);

    msg = "should insert at tail";
    assert(alg_linked_list_insert(&list, list.len, ++e), msg);
    assert_eq(list.len, LEN + 3, msg);
    assert_eq(list.tail->data, e, msg);

    msg = "should insert when empty";
    alg_linked_list_clear(&list);
    assert(alg_linked_list_insert(&list, 0, ++e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.head->data, e, msg);
    assert_eq(list.tail->data, e, msg);
}

void test_push_front(void) {
    AlgLinkedList list = test_data();
    alg_elem_t    e    = 999;
    char         *msg;

    msg = "should not push_front when NULL";
    assert_not(alg_linked_list_push_front(NULL, 0), msg);

    msg = "should push_front";
    assert(alg_linked_list_push_front(&list, e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.head->data, e, msg);

    msg = "should push_front when empty";
    alg_linked_list_clear(&list);
    assert(alg_linked_list_push_front(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.head->data, e, msg);
    assert_eq(list.tail->data, e, msg);
}

void test_push_back(void) {
    AlgLinkedList list = test_data();
    alg_elem_t    e    = 999;
    char         *msg;

    msg = "should not push_back when NULL";
    assert_not(alg_linked_list_push_back(NULL, 0), msg);

    msg = "should push_back";
    assert(alg_linked_list_push_back(&list, e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.tail->data, e, msg);

    msg = "should push_back when empty";
    alg_linked_list_clear(&list);
    assert(alg_linked_list_push_back(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.head->data, e, msg);
    assert_eq(list.tail->data, e, msg);
}

void test_del(void) {
    AlgLinkedList list = test_data();
    alg_elem_t    e;
    alg_elem_t    deleted;
    char         *msg;

    msg = "should not delete when NULL";
    assert_not(alg_linked_list_del(NULL, 0, NULL), msg);

    msg = "should not delete when out of range";
    assert_not(alg_linked_list_del(&list, list.len, &e), msg);
    assert_eq(list.len, LEN, msg);

    msg     = "should delete at head";
    deleted = list.head->data;
    assert(alg_linked_list_del(&list, 0, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, deleted, msg);

    msg = "should delete at middle";
    assert(alg_linked_list_get(&list, list.len / 2, &deleted), msg);
    assert(alg_linked_list_del(&list, list.len / 2, &e), msg);
    assert_eq(list.len, LEN - 2, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete at tail";
    deleted = list.tail->data;
    assert(alg_linked_list_del(&list, list.len - 1, &e), msg);
    assert_eq(list.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not delete when empty";
    alg_linked_list_clear(&list);
    assert_not(alg_linked_list_del(&list, 0, NULL), msg);
    assert_eq(list.len, 0, msg);

    msg = "should delete when len == 1";
    assert(alg_linked_list_push_back(&list, 999), msg);
    assert(alg_linked_list_del(&list, 0, &e), msg);
    assert_eq(list.len, 0, msg);
    assert_eq(e, 999, msg);
    assert_null(list.head, msg);
    assert_null(list.tail, msg);
}

void test_pop_front(void) {
    AlgLinkedList list = test_data();
    alg_elem_t    e;
    alg_elem_t    popped;
    char         *msg;

    msg = "should not pop_front when NULL";
    assert_not(alg_linked_list_pop_front(NULL, NULL), msg);

    msg    = "should pop_front";
    popped = list.head->data;
    assert(alg_linked_list_pop_front(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    alg_linked_list_clear(&list);
    assert_not(alg_linked_list_pop_front(&list, NULL), msg);
    assert_eq(list.len, 0, msg);
}

void test_pop_back(void) {
    AlgLinkedList list = test_data();
    alg_elem_t    e;
    alg_elem_t    popped;
    char         *msg;

    msg = "should not pop_back when NULL";
    assert_not(alg_linked_list_pop_back(NULL, NULL), msg);

    msg    = "should pop_back";
    popped = list.tail->data;
    assert(alg_linked_list_pop_back(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    alg_linked_list_clear(&list);
    assert_not(alg_linked_list_pop_back(&list, NULL), msg);
    assert_eq(list.len, 0, msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "linked_list";

    run_test(test_create, mod, target, "create");
    run_test(test_init, mod, target, "init");
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

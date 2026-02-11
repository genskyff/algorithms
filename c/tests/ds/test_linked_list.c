#include "alg/ds/linked_list.h"
#include "helper.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    LinkedList test_data() {                                                   \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    LinkedList list = create();
    char      *msg;

    msg = "should get a empty linked list";
    assert_null(list.head, msg);
    assert_null(list.tail, msg);
    assert_eq(list.len, 0, msg);
}

void test_init(void) {
    LinkedList list = init(LEN, 0, 1, 2, 3, 4, 5);
    char      *msg;

    msg = "should get a initialized linked list";
    assert_not_null(list.head, msg);
    assert_not_null(list.tail, msg);
    assert_eq(list.len, LEN, msg);
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_list_arr_eq(list.head, FORWARD, tmp, LEN, msg);
    assert_eq(list.tail->data, 5, msg);
}

void test_swap(void) {
    LinkedList list     = test_data();
    elem_t     tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char      *msg;

    msg = "should not swap when NULL";
    swap(NULL, 0, 1);

    msg = "should not swap when i == j";
    swap(&list, 1, 1);
    assert_list_arr_eq(list.head, FORWARD, tmp, LEN, msg);

    msg = "should not swap when out of range";
    swap(&list, 0, LEN);
    assert_list_arr_eq(list.head, FORWARD, tmp, LEN, msg);

    msg = "should swap head and tail";
    swap(&list, 0, list.len - 1);
    elem_t swap_either_end[LEN] = {5, 1, 2, 3, 4, 0};
    assert_list_arr_eq(list.head, FORWARD, swap_either_end, LEN, msg);
    assert_eq(list.tail->data, 0, msg);

    msg = "should swap when |i - j| == 1";
    swap(&list, 0, 1);
    elem_t swap_adjacent[LEN] = {1, 5, 2, 3, 4, 0};
    assert_list_arr_eq(list.head, FORWARD, swap_adjacent, LEN, msg);
    assert_eq(list.tail->data, 0, msg);

    msg = "should swap when i == 0, j > 1";
    swap(&list, 0, 3);
    elem_t swap_front[LEN] = {3, 5, 2, 1, 4, 0};
    assert_list_arr_eq(list.head, FORWARD, swap_front, LEN, msg);
    assert_eq(list.tail->data, 0, msg);

    msg = "should swap when i > 0, j == len - 1";
    swap(&list, 1, list.len - 1);
    elem_t swap_tail[LEN] = {3, 0, 2, 1, 4, 5};
    assert_list_arr_eq(list.head, FORWARD, swap_tail, LEN, msg);
    assert_eq(list.tail->data, 5, msg);
}

void test_reverse(void) {
    LinkedList list = test_data();
    char      *msg;

    msg = "should reverse";
    reverse(&list);
    elem_t rev[LEN] = {5, 4, 3, 2, 1, 0};
    assert_list_arr_eq(list.head, FORWARD, rev, LEN, msg);
    assert_eq(list.tail->data, 0, msg);
}

void test_clear(void) {
    LinkedList list = test_data();
    char      *msg;

    msg = "should clear";
    clear(&list);
    assert_null(list.head, msg);
    assert_null(list.tail, msg);
    assert_eq(list.len, 0, msg);
}

void test_is_empty(void) {
    LinkedList list = test_data();
    char      *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(is_empty(&list), msg);

    msg = "should be empty when len == 0";
    clear(&list);
    assert(is_empty(&list), msg);
}

void test_get(void) {
    LinkedList list = test_data();
    elem_t     e;
    char      *msg;

    msg = "should not get when NULL";
    assert_not(get(NULL, 0, NULL), msg);

    msg = "should not get when out of range";
    assert_not(get(&list, list.len, &e), msg);

    msg = "should get";
    assert(get(&list, list.len - 1, &e), msg);
    assert_eq(e, list.tail->data, msg);

    msg = "should not get when empty";
    clear(&list);
    assert_not(get(&list, 0, &e), msg);
}

void test_first(void) {
    LinkedList list = test_data();
    elem_t     e;
    char      *msg;

    msg = "should not get first when NULL";
    assert_not(first(NULL, NULL), msg);

    msg = "should get first";
    assert(first(&list, &e), msg);
    assert_eq(e, list.head->data, msg);

    msg = "should not get first when empty";
    clear(&list);
    assert_not(first(&list, &e), msg);
}

void test_last(void) {
    LinkedList list = test_data();
    elem_t     e;
    char      *msg;

    msg = "should not get last when NULL";
    assert_not(last(NULL, NULL), msg);

    msg = "should get last";
    assert(last(&list, &e), msg);
    assert_eq(e, list.tail->data, msg);

    msg = "should not get last when empty";
    clear(&list);
    assert_not(last(&list, &e), msg);
}

void test_set(void) {
    LinkedList list = test_data();
    elem_t     e    = 999;
    char      *msg;

    msg = "should not set when NULL";
    assert_not(set(NULL, 0, e), msg);

    msg = "should not set when out of range";
    assert_not(set(&list, list.len, e), msg);
    assert_not(find(&list, e, NULL), msg);

    msg = "should set";
    assert(set(&list, list.len - 1, e), msg);
    assert_eq(list.tail->data, e, msg);

    msg = "should not set when empty";
    clear(&list);
    assert_not(set(&list, 0, e), msg);
}

void test_find(void) {
    LinkedList list = test_data();
    size_t     i;
    char      *msg;

    msg = "should not find when NULL";
    assert_not(find(NULL, 0, NULL), msg);

    msg = "should find at head";
    assert(find(&list, 0, &i), msg);
    assert_eq(i, 0, msg);

    msg = "should find at tail";
    assert(find(&list, list.tail->data, &i), msg);
    assert_eq(i, list.len - 1, msg);

    msg = "should not find when no exist";
    i   = 0;
    assert_not(find(&list, 999, &i), msg);
    assert_eq(i, 0, msg);
}

void test_insert(void) {
    LinkedList list = test_data();
    elem_t     e    = 999;
    char      *msg;

    msg = "should not insert when NULL";
    assert_not(insert(NULL, 0, e), msg);

    msg = "should not insert when out of range";
    assert_not(insert(&list, list.len + 1, ++e), msg);
    assert_eq(list.len, LEN, msg);
    assert_not(find(&list, e, NULL), msg);

    msg = "should insert at head";
    assert(insert(&list, 0, ++e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.head->data, e, msg);

    msg = "should insert at middle";
    assert(insert(&list, list.len / 2, ++e), msg);
    assert_eq(list.len, LEN + 2, msg);
    elem_t mid;
    assert(get(&list, (list.len - 1) / 2, &mid), msg);
    assert_eq(mid, e, msg);

    msg = "should insert at tail";
    assert(insert(&list, list.len, ++e), msg);
    assert_eq(list.len, LEN + 3, msg);
    assert_eq(list.tail->data, e, msg);

    msg = "should insert when empty";
    clear(&list);
    assert(insert(&list, 0, ++e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.head->data, e, msg);
    assert_eq(list.tail->data, e, msg);
}

void test_push_front(void) {
    LinkedList list = test_data();
    elem_t     e    = 999;
    char      *msg;

    msg = "should not push_front when NULL";
    assert_not(push_front(NULL, 0), msg);

    msg = "should push_front";
    assert(push_front(&list, e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.head->data, e, msg);

    msg = "should push_front when empty";
    clear(&list);
    assert(push_front(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.head->data, e, msg);
    assert_eq(list.tail->data, e, msg);
}

void test_push_back(void) {
    LinkedList list = test_data();
    elem_t     e    = 999;
    char      *msg;

    msg = "should not push_back when NULL";
    assert_not(push_back(NULL, 0), msg);

    msg = "should push_back";
    assert(push_back(&list, e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.tail->data, e, msg);

    msg = "should push_back when empty";
    clear(&list);
    assert(push_back(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.head->data, e, msg);
    assert_eq(list.tail->data, e, msg);
}

void test_del(void) {
    LinkedList list = test_data();
    elem_t     e;
    elem_t     deleted;
    char      *msg;

    msg = "should not delete when NULL";
    assert_not(del(NULL, 0, NULL), msg);

    msg = "should not delete when out of range";
    assert_not(del(&list, list.len, &e), msg);
    assert_eq(list.len, LEN, msg);

    msg     = "should delete at head";
    deleted = list.head->data;
    assert(del(&list, 0, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, deleted, msg);

    msg = "should delete at middle";
    assert(get(&list, list.len / 2, &deleted), msg);
    assert(del(&list, list.len / 2, &e), msg);
    assert_eq(list.len, LEN - 2, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete at tail";
    deleted = list.tail->data;
    assert(del(&list, list.len - 1, &e), msg);
    assert_eq(list.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not delete when empty";
    clear(&list);
    assert_not(del(&list, 0, NULL), msg);
    assert_eq(list.len, 0, msg);

    msg = "should delete when len == 1";
    assert(push_back(&list, 999), msg);
    assert(del(&list, 0, &e), msg);
    assert_eq(list.len, 0, msg);
    assert_eq(e, 999, msg);
    assert_null(list.head, msg);
    assert_null(list.tail, msg);
}

void test_pop_front(void) {
    LinkedList list = test_data();
    elem_t     e;
    elem_t     popped;
    char      *msg;

    msg = "should not pop_front when NULL";
    assert_not(pop_front(NULL, NULL), msg);

    msg    = "should pop_front";
    popped = list.head->data;
    assert(pop_front(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    clear(&list);
    assert_not(pop_front(&list, NULL), msg);
    assert_eq(list.len, 0, msg);
}

void test_pop_back(void) {
    LinkedList list = test_data();
    elem_t     e;
    elem_t     popped;
    char      *msg;

    msg = "should not pop_back when NULL";
    assert_not(pop_back(NULL, NULL), msg);

    msg    = "should pop_back";
    popped = list.tail->data;
    assert(pop_back(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    clear(&list);
    assert_not(pop_back(&list, NULL), msg);
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

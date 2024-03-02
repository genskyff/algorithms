#include "helper.h"
#include "linked_list.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    LinkedList test_data() {                                                   \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    LinkedList list = create();
    char      *msg  = "should get a empty linked list";
    assert(list.head == NULL, msg);
    assert(list.tail == NULL, msg);
    assert_eq(list.len, 0, msg);
}

void test_init(void) {
    LinkedList list = init(LEN, 0, 1, 2, 3, 4, 5);
    char      *msg  = "should get a initialized linked list";
    assert(list.head != NULL, msg);
    assert(list.tail != NULL, msg);
    assert_eq(list.len, LEN, msg);
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_list_arr_eq(list.head, tmp, LEN, msg);
    assert_eq(list.tail->data, 5, msg);
}

void test_swap(void) {
    LinkedList list     = test_data();
    elem_t     tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char      *msg;

    msg = "should not swap when i == j";
    swap(&list, 1, 1);
    assert_list_arr_eq(list.head, tmp, LEN, msg);

    msg = "should not swap when out of range";
    swap(&list, 0, LEN);
    assert_list_arr_eq(list.head, tmp, LEN, msg);

    msg = "should swap head and tail";
    swap(&list, 0, list.len - 1);
    elem_t swap_side[LEN] = {5, 1, 2, 3, 4, 0};
    assert_list_arr_eq(list.head, swap_side, LEN, msg);
    assert_eq(list.tail->data, 0, msg);

    msg = "should swap when |i - j| == 1";
    swap(&list, 0, 1);
    elem_t swap_adjacent[LEN] = {1, 5, 2, 3, 4, 0};
    assert_list_arr_eq(list.head, swap_adjacent, LEN, msg);
    assert_eq(list.tail->data, 0, msg);

    msg = "should swap when i == 0, j > 1";
    swap(&list, 0, 3);
    elem_t swap_front[LEN] = {3, 5, 2, 1, 4, 0};
    assert_list_arr_eq(list.head, swap_front, LEN, msg);
    assert_eq(list.tail->data, 0, msg);

    msg = "should swap when i > 0, j == len - 1";
    swap(&list, 1, list.len - 1);
    elem_t swap_end[LEN] = {3, 0, 2, 1, 4, 5};
    assert_list_arr_eq(list.head, swap_end, LEN, msg);
    assert_eq(list.tail->data, 5, msg);
}

void test_reverse(void) {
    LinkedList list = test_data();
    char      *msg  = "should reverse";
    reverse(&list);
    elem_t rev[LEN] = {5, 4, 3, 2, 1, 0};
    assert_list_arr_eq(list.head, rev, LEN, msg);
    assert_eq(list.tail->data, 0, msg);
}

void test_clear(void) {
    LinkedList list = test_data();
    char      *msg  = "should clear";
    clear(&list);
    assert(list.head == NULL, msg);
    assert(list.tail == NULL, msg);
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

    char *msg;

    msg = "should not get when NULL";
    assert(!get(NULL, 0, &e), msg);

    msg = "should get";
    assert(get(&list, 0, &e), msg);
    assert_eq(e, 0, msg);

    msg = "should not get when out of range";
    assert(!get(&list, list.len, &e), msg);
}

void test_first(void) {
    LinkedList list = test_data();
    elem_t     e;
    char      *msg;

    msg = "should get first";
    assert(first(&list, &e), msg);
    assert_eq(e, list.head->data, msg);

    msg = "should not get first when empty";
    clear(&list);
    assert_not(first(&list, NULL), msg);
}

void test_last(void) {
    LinkedList list = test_data();
    elem_t     e;
    char      *msg;

    msg = "should get last";
    assert(last(&list, &e), msg);
    assert_eq(e, list.tail->data, msg);

    msg = "should not get last when empty";
    clear(&list);
    assert_not(last(&list, NULL), msg);
}

void test_set(void) {
    LinkedList list = test_data();
    elem_t     e    = 999;
    char      *msg;

    msg = "should not set when out of range";
    assert_not(set(&list, list.len, e), msg);
    assert_not(find(&list, e, NULL), msg);

    msg = "should set";
    assert(set(&list, list.len - 1, e), msg);
    assert_eq(list.tail->data, e, msg);
}

void test_find(void) {
    LinkedList list = test_data();
    size_t     i;
    char      *msg;

    msg = "should find at [0]";
    assert(find(&list, 0, &i), msg);
    assert_eq(i, 0, msg);

    msg = "should find at tail";
    assert(find(&list, 5, &i), msg);
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

    msg = "should insert at [0]";
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

    msg = "should not insert when out of range";
    assert_not(insert(&list, list.len + 1, ++e), msg);
    assert_eq(list.len, 1, msg);
    assert_not(find(&list, e, NULL), msg);
}

void test_push_front(void) {
    LinkedList list = test_data();
    elem_t     e    = 999;
    char      *msg;

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

    msg     = "should delete at [0]";
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

    msg = "should not delete when out of range";
    assert_not(del(&list, list.len, &e), msg);
    assert_eq(list.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should delete when len == 1";
    clear(&list);
    assert(push_back(&list, 999), msg);
    assert(del(&list, 0, &e), msg);
    assert_eq(list.len, 0, msg);
    assert_eq(e, 999, msg);
    assert(list.head == NULL, msg);
    assert(list.tail == NULL, msg);

    msg = "should not delete when empty";
    clear(&list);
    assert_not(del(&list, 0, NULL), msg);
}

void test_pop_front(void) {
    LinkedList list = test_data();
    elem_t     e;
    elem_t     popped;
    char      *msg;

    msg    = "should pop_front";
    popped = list.head->data;
    assert(pop_front(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    clear(&list);
    assert_not(pop_front(&list, NULL), msg);
}

void test_pop_back(void) {
    LinkedList list = test_data();
    elem_t     e;
    elem_t     popped;
    char      *msg;

    msg    = "should pop_back";
    popped = list.tail->data;
    assert(pop_back(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    clear(&list);
    assert_not(pop_back(&list, NULL), msg);
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "linked_list_create");
    run_test(test_init, prefix, "linked_list_init");
    run_test(test_swap, prefix, "linked_list_swap");
    run_test(test_reverse, prefix, "linked_list_reverse");
    run_test(test_clear, prefix, "linked_list_clear");
    run_test(test_is_empty, prefix, "linked_list_is_empty");
    run_test(test_get, prefix, "linked_list_get");
    run_test(test_first, prefix, "linked_list_first");
    run_test(test_last, prefix, "linked_list_last");
    run_test(test_set, prefix, "linked_list_set");
    run_test(test_find, prefix, "linked_list_find");
    run_test(test_insert, prefix, "linked_list_insert");
    run_test(test_push_front, prefix, "linked_list_push_front");
    run_test(test_push_back, prefix, "linked_list_push_back");
    run_test(test_del, prefix, "linked_list_del");
    run_test(test_pop_front, prefix, "linked_list_pop_front");
    run_test(test_pop_back, prefix, "linked_list_pop_back");

    return 0;
}

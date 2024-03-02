#include "helper.h"
#include "sqlist.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    SqList test_data() {                                                       \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    SqList list = create();
    char  *msg  = "should get a empty sqlist";
    assert_eq(list.len, 0, msg);
}

void test_init(void) {
    SqList list     = init(LEN, 0, 1, 2, 3, 4, 5);
    char  *msg      = "should get a initialized sqlist";
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_eq(list.len, LEN, msg);
    assert_arr_eq(list.data, list.len, tmp, LEN, msg);
}

void test_swap(void) {
    SqList list     = test_data();
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char  *msg;

    msg = "should not swap when i == j";
    swap(&list, 1, 1);
    assert_arr_eq(list.data, list.len, tmp, LEN, msg);

    msg = "should not swap when out of range";
    swap(&list, 0, LEN);
    assert_arr_eq(list.data, list.len, tmp, LEN, msg);

    msg = "should swap";
    swap(&list, 0, list.len - 1);
    elem_t swap_endpoint[LEN] = {5, 1, 2, 3, 4, 0};
    assert_arr_eq(list.data, list.len, swap_endpoint, LEN, msg);
}

void test_reverse(void) {
    SqList list = test_data();
    char  *msg  = "should reverse";
    reverse(&list);
    elem_t rev[LEN] = {5, 4, 3, 2, 1, 0};
    assert_arr_eq(list.data, list.len, rev, LEN, msg);
}

void test_clear(void) {
    SqList list = test_data();
    char  *msg  = "should clear";
    clear(&list);
    assert_eq(list.len, 0, msg);
}

void test_is_empty(void) {
    SqList list = test_data();
    char  *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(is_empty(&list), msg);

    msg = "should be empty when len == 0";
    clear(&list);
    assert(is_empty(&list), msg);
}

void test_get(void) {
    SqList list = test_data();
    elem_t e;
    char  *msg;

    msg = "should not get when out of range";
    e   = 0;
    assert_not(get(&list, list.len, &e), msg);
    assert_eq(e, 0, msg);

    msg = "should get";
    assert(get(&list, list.len - 1, &e), msg);
    assert_eq(e, list.data[list.len - 1], msg);
}

void test_first(void) {
    SqList list = test_data();
    elem_t e;
    char  *msg;

    msg = "should get first";
    assert(first(&list, &e), msg);
    assert_eq(e, list.data[0], msg);

    msg = "should not get first when empty";
    clear(&list);
    assert_not(first(&list, NULL), msg);
}

void test_last(void) {
    SqList list = test_data();
    elem_t e;
    char  *msg;

    msg = "should get last";
    assert(last(&list, &e), msg);
    assert_eq(e, list.data[list.len - 1], msg);

    msg = "should not get last when empty";
    clear(&list);
    assert_not(last(&list, NULL), msg);
}

void test_set(void) {
    SqList list = test_data();
    elem_t e    = 999;
    char  *msg;

    msg = "should not set when out of range";
    assert_not(set(&list, list.len, e), msg);
    assert_not(find(&list, e, NULL), msg);

    msg = "should set";
    assert(set(&list, list.len - 1, e), msg);
    assert_eq(list.data[list.len - 1], e, msg);
}

void test_find(void) {
    SqList list = test_data();
    size_t i;
    char  *msg;

    msg = "should find at [0]";
    assert(find(&list, 0, &i), msg);
    assert_eq(i, 0, msg);

    msg = "should find at tail";
    assert(find(&list, list.data[list.len - 1], &i), msg);
    assert_eq(i, list.len - 1, msg);

    msg = "should not find when no exist";
    i   = 0;
    assert_not(find(&list, 999, &i), msg);
    assert_eq(i, 0, msg);
}

void test_insert(void) {
    SqList list = test_data();
    elem_t e    = 999;
    char  *msg;

    msg = "should insert at [0]";
    assert(insert(&list, 0, ++e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.data[0], e, msg);

    msg = "should insert at middle";
    assert(insert(&list, list.len / 2, ++e), msg);
    assert_eq(list.len, LEN + 2, msg);
    assert_eq(list.data[(list.len - 1) / 2], e, msg);

    msg = "should insert at tail";
    assert(insert(&list, list.len, ++e), msg);
    assert_eq(list.len, LEN + 3, msg);
    assert_eq(list.data[list.len - 1], e, msg);

    msg = "should not insert when out of range";
    assert_not(insert(&list, list.len + 1, ++e), msg);
    assert_eq(list.len, LEN + 3, msg);
    assert_not(find(&list, e, NULL), msg);

    msg      = "should not insert when full";
    list.len = MAXLEN;
    assert_not(insert(&list, 0, 0), msg);
    assert_eq(list.len, MAXLEN, msg);
}

void test_push_front(void) {
    SqList list = create();
    elem_t e    = 999;
    char  *msg;

    msg = "should push_front";
    assert(push_front(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert(push_front(&list, e), msg);
    assert_eq(list.len, 2, msg);

    msg      = "should not push_front when full";
    list.len = MAXLEN;
    assert_not(push_front(&list, 0), msg);
    assert_eq(list.len, MAXLEN, msg);
}

void test_push_back(void) {
    SqList list = create();
    elem_t e    = 999;
    char  *msg;

    msg = "should push_back";
    assert(push_back(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert(push_back(&list, e), msg);
    assert_eq(list.len, 2, msg);

    msg      = "should not push_back when full";
    list.len = MAXLEN;
    assert_not(push_back(&list, 0), msg);
    assert_eq(list.len, MAXLEN, msg);
}

void test_del(void) {
    SqList list = test_data();
    elem_t e;
    elem_t deleted;
    char  *msg;

    msg     = "should delete at [0]";
    deleted = list.data[0];
    assert(del(&list, 0, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete at middle";
    deleted = list.data[list.len / 2];
    assert(del(&list, list.len / 2, &e), msg);
    assert_eq(list.len, LEN - 2, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete at tail";
    deleted = list.data[list.len - 1];
    assert(del(&list, list.len - 1, &e), msg);
    assert_eq(list.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not delete when out of range";
    assert_not(del(&list, list.len, &e), msg);
    assert_eq(list.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not delete when empty";
    clear(&list);
    assert_not(del(&list, 0, NULL), msg);
}

void test_pop_front(void) {
    SqList list = test_data();
    elem_t e;
    elem_t popped;
    char  *msg;

    msg    = "should pop_front";
    popped = list.data[0];
    assert(pop_front(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    clear(&list);
    assert_not(pop_front(&list, NULL), msg);
    assert_eq(list.len, 0, msg);
}

void test_pop_back(void) {
    SqList list = test_data();
    elem_t e;
    elem_t popped;
    char  *msg;

    msg    = "should pop_back";
    popped = list.data[list.len - 1];
    assert(pop_back(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    clear(&list);
    assert_not(pop_back(&list, NULL), msg);
    assert_eq(list.len, 0, msg);
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "sqlist_create");
    run_test(test_init, prefix, "sqlist_init");
    run_test(test_swap, prefix, "sqlist_swap");
    run_test(test_reverse, prefix, "sqlist_reverse");
    run_test(test_is_empty, prefix, "sqlist_is_empty");
    run_test(test_get, prefix, "sqlist_get");
    run_test(test_first, prefix, "sqlist_first");
    run_test(test_last, prefix, "sqlist_last");
    run_test(test_set, prefix, "sqlist_set");
    run_test(test_find, prefix, "sqlist_find");
    run_test(test_insert, prefix, "sqlist_insert");
    run_test(test_push_front, prefix, "sqlist_push_front");
    run_test(test_push_back, prefix, "sqlist_push_back");
    run_test(test_del, prefix, "sqlist_del");
    run_test(test_pop_front, prefix, "sqlist_pop_front");
    run_test(test_pop_back, prefix, "sqlist_pop_back");

    return 0;
}

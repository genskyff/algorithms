#include "alg/ds/sqlist.h"
#include "support/helper.h"

#define LEN 6
static const alg_elem_t DATA[LEN] = {0, 1, 2, 3, 4, 5};

AlgSqList test_data(void) {
    return alg_sqlist_from_array(DATA, LEN);
}

void test_create(void) {
    AlgSqList list = alg_sqlist_create();
    char     *msg;

    msg = "should get a empty sqlist";
    assert_eq(list.len, 0, msg);
}

void test_from_array(void) {
    AlgSqList list = alg_sqlist_from_array(DATA, LEN);
    char     *msg;

    msg                 = "should create a sqlist from an array";
    alg_elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_eq(list.len, LEN, msg);
    assert_arr_eq(list.data, list.len, tmp, LEN, msg);

    msg  = "should get an empty sqlist when array is NULL";
    list = alg_sqlist_from_array(NULL, LEN);
    assert_eq(list.len, 0, msg);
}

void test_swap(void) {
    AlgSqList  list     = test_data();
    alg_elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char      *msg;

    msg = "should not swap when NULL";
    alg_sqlist_swap(NULL, 0, 1);

    msg = "should not swap when i == j";
    alg_sqlist_swap(&list, 1, 1);
    assert_arr_eq(list.data, list.len, tmp, LEN, msg);

    msg = "should not swap when out of range";
    alg_sqlist_swap(&list, 0, LEN);
    assert_arr_eq(list.data, list.len, tmp, LEN, msg);

    msg = "should swap head and tail";
    alg_sqlist_swap(&list, 0, list.len - 1);
    alg_elem_t swap_either_end[LEN] = {5, 1, 2, 3, 4, 0};
    assert_arr_eq(list.data, list.len, swap_either_end, LEN, msg);
}

void test_reverse(void) {
    AlgSqList list = test_data();
    char     *msg;

    msg = "should reverse";
    alg_sqlist_reverse(&list);
    alg_elem_t rev[LEN] = {5, 4, 3, 2, 1, 0};
    assert_arr_eq(list.data, list.len, rev, LEN, msg);
}

void test_clear(void) {
    AlgSqList list = test_data();
    char     *msg;

    msg = "should clear";
    alg_sqlist_clear(&list);
    assert_eq(list.len, 0, msg);
}

void test_is_empty(void) {
    AlgSqList list = test_data();
    char     *msg;

    msg = "should be empty when NULL";
    assert(alg_sqlist_is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(alg_sqlist_is_empty(&list), msg);

    msg = "should be empty when len == 0";
    alg_sqlist_clear(&list);
    assert(alg_sqlist_is_empty(&list), msg);
}

void test_get(void) {
    AlgSqList  list = test_data();
    alg_elem_t e;
    char      *msg;

    msg = "should not get when NULL";
    assert_not(alg_sqlist_get(NULL, 0, NULL), msg);

    msg = "should not get when out of range";
    e   = 0;
    assert_not(alg_sqlist_get(&list, list.len, &e), msg);
    assert_eq(e, 0, msg);

    msg = "should get";
    assert(alg_sqlist_get(&list, list.len - 1, &e), msg);
    assert_eq(e, list.data[list.len - 1], msg);

    msg = "should not get when empty";
    alg_sqlist_clear(&list);
    assert_not(alg_sqlist_get(&list, 0, NULL), msg);
}

void test_first(void) {
    AlgSqList  list = test_data();
    alg_elem_t e;
    char      *msg;

    msg = "should not get first when NULL";
    assert_not(alg_sqlist_first(NULL, NULL), msg);

    msg = "should get first";
    assert(alg_sqlist_first(&list, &e), msg);
    assert_eq(e, list.data[0], msg);

    msg = "should not get first when empty";
    alg_sqlist_clear(&list);
    assert_not(alg_sqlist_first(&list, NULL), msg);
}

void test_last(void) {
    AlgSqList  list = test_data();
    alg_elem_t e;
    char      *msg;

    msg = "should not get last when NULL";
    assert_not(alg_sqlist_last(NULL, NULL), msg);

    msg = "should get last";
    assert(alg_sqlist_last(&list, &e), msg);
    assert_eq(e, list.data[list.len - 1], msg);

    msg = "should not get last when empty";
    alg_sqlist_clear(&list);
    assert_not(alg_sqlist_last(&list, NULL), msg);
}

void test_set(void) {
    AlgSqList  list = test_data();
    alg_elem_t e    = 999;
    char      *msg;

    msg = "should not set when NULL";
    assert_not(alg_sqlist_set(NULL, 0, e), msg);

    msg = "should not set when out of range";
    assert_not(alg_sqlist_set(&list, list.len, e), msg);
    assert_not(alg_sqlist_find(&list, e, NULL), msg);

    msg = "should set";
    assert(alg_sqlist_set(&list, list.len - 1, e), msg);
    assert_eq(list.data[list.len - 1], e, msg);
}

void test_find(void) {
    AlgSqList list = test_data();
    size_t    i;
    char     *msg;

    msg = "should not find when NULL";
    assert_not(alg_sqlist_find(NULL, 0, NULL), msg);

    msg = "should find at head";
    assert(alg_sqlist_find(&list, 0, &i), msg);
    assert_eq(i, 0, msg);

    msg = "should find at tail";
    assert(alg_sqlist_find(&list, list.data[list.len - 1], &i), msg);
    assert_eq(i, list.len - 1, msg);

    msg = "should not find when no exist";
    i   = 0;
    assert_not(alg_sqlist_find(&list, 999, &i), msg);
    assert_eq(i, 0, msg);
}

void test_insert(void) {
    AlgSqList  list = test_data();
    alg_elem_t e    = 999;
    char      *msg;

    msg = "should not insert when NULL";
    assert_not(alg_sqlist_insert(NULL, 0, 0), msg);

    msg = "should insert at head";
    assert(alg_sqlist_insert(&list, 0, ++e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.data[0], e, msg);

    msg = "should insert at middle";
    assert(alg_sqlist_insert(&list, list.len / 2, ++e), msg);
    assert_eq(list.len, LEN + 2, msg);
    assert_eq(list.data[(list.len - 1) / 2], e, msg);

    msg = "should insert at tail";
    assert(alg_sqlist_insert(&list, list.len, ++e), msg);
    assert_eq(list.len, LEN + 3, msg);
    assert_eq(list.data[list.len - 1], e, msg);

    msg = "should not insert when out of range";
    assert_not(alg_sqlist_insert(&list, list.len + 1, ++e), msg);
    assert_eq(list.len, LEN + 3, msg);
    assert_not(alg_sqlist_find(&list, e, NULL), msg);

    msg      = "should not insert when full";
    list.len = ALG_MAX_LEN;
    assert_not(alg_sqlist_insert(&list, 0, 0), msg);
    assert_eq(list.len, ALG_MAX_LEN, msg);
}

void test_push_front(void) {
    AlgSqList  list = alg_sqlist_create();
    alg_elem_t e    = 999;
    char      *msg;

    msg = "should not push_front when NULL";
    assert_not(alg_sqlist_push_front(NULL, 0), msg);

    msg = "should push_front";
    assert(alg_sqlist_push_front(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert(alg_sqlist_push_front(&list, e), msg);
    assert_eq(list.len, 2, msg);

    msg      = "should not push_front when full";
    list.len = ALG_MAX_LEN;
    assert_not(alg_sqlist_push_front(&list, 0), msg);
    assert_eq(list.len, ALG_MAX_LEN, msg);
}

void test_push_back(void) {
    AlgSqList  list = alg_sqlist_create();
    alg_elem_t e    = 999;
    char      *msg;

    msg = "should not push_back when NULL";
    assert_not(alg_sqlist_push_back(NULL, 0), msg);

    msg = "should push_back";
    assert(alg_sqlist_push_back(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert(alg_sqlist_push_back(&list, e), msg);
    assert_eq(list.len, 2, msg);

    msg      = "should not push_back when full";
    list.len = ALG_MAX_LEN;
    assert_not(alg_sqlist_push_back(&list, 0), msg);
    assert_eq(list.len, ALG_MAX_LEN, msg);
}

void test_del(void) {
    AlgSqList  list = test_data();
    alg_elem_t e;
    alg_elem_t deleted;
    char      *msg;

    msg = "should not delete when NULL";
    assert_not(alg_sqlist_del(NULL, 0, NULL), msg);

    msg     = "should delete at head";
    deleted = list.data[0];
    assert(alg_sqlist_del(&list, 0, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete at middle";
    deleted = list.data[list.len / 2];
    assert(alg_sqlist_del(&list, list.len / 2, &e), msg);
    assert_eq(list.len, LEN - 2, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete at tail";
    deleted = list.data[list.len - 1];
    assert(alg_sqlist_del(&list, list.len - 1, &e), msg);
    assert_eq(list.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not delete when out of range";
    assert_not(alg_sqlist_del(&list, list.len, &e), msg);
    assert_eq(list.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not delete when empty";
    alg_sqlist_clear(&list);
    assert_not(alg_sqlist_del(&list, 0, NULL), msg);
    assert_eq(list.len, 0, msg);
}

void test_pop_front(void) {
    AlgSqList  list = test_data();
    alg_elem_t e;
    alg_elem_t popped;
    char      *msg;

    msg = "should not pop_front when NULL";
    assert_not(alg_sqlist_pop_front(NULL, NULL), msg);

    msg    = "should pop_front";
    popped = list.data[0];
    assert(alg_sqlist_pop_front(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    alg_sqlist_clear(&list);
    assert_not(alg_sqlist_pop_front(&list, NULL), msg);
    assert_eq(list.len, 0, msg);
}

void test_pop_back(void) {
    AlgSqList  list = test_data();
    alg_elem_t e;
    alg_elem_t popped;
    char      *msg;

    msg = "should not pop_back when NULL";
    assert_not(alg_sqlist_pop_back(NULL, NULL), msg);

    msg    = "should pop_back";
    popped = list.data[list.len - 1];
    assert(alg_sqlist_pop_back(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    alg_sqlist_clear(&list);
    assert_not(alg_sqlist_pop_back(&list, NULL), msg);
    assert_eq(list.len, 0, msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "sqlist";

    run_test(test_create, mod, target, "create");
    run_test(test_from_array, mod, target, "from_array");
    run_test(test_swap, mod, target, "swap");
    run_test(test_reverse, mod, target, "reverse");
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

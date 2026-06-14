#include "alg/ds/vector.h"
#include "support/helper.h"

#define LEN 6
enum {
    TEST_LARGE_CAP  = 2048,
    TEST_SHRINK_LEN = 512,
};

static const alg_elem_t DATA[LEN] = {0, 1, 2, 3, 4, 5};

AlgVec test_data(void) {
    return alg_vec_from_array(DATA, LEN);
}

void test_create(void) {
    AlgVec v = alg_vec_create();
    char  *msg;

    msg = "should get a empty vector";
    assert_not_null(v.data, msg);
    assert_eq(v.len, 0, msg);
    assert(v.cap > 0, msg);

    alg_vec_drop(&v);
}

void test_create_with(void) {
    size_t cap = 100;
    AlgVec v   = alg_vec_create_with(cap);
    char  *msg;

    msg = "should get a empty vector with capacity";
    assert_not_null(v.data, msg);
    assert_eq(v.len, 0, msg);
    assert_eq(v.cap, cap, msg);

    alg_vec_drop(&v);
}

void test_from_array(void) {
    AlgVec v = alg_vec_from_array(DATA, LEN);
    char  *msg;

    msg = "should create a vector from an array";
    assert_not_null(v.data, msg);
    assert_eq(v.len, LEN, msg);
    assert(v.cap >= v.len, msg);
    alg_elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_arr_eq(v.data, v.len, tmp, LEN, msg);

    alg_vec_drop(&v);

    msg = "should get an empty vector when array is NULL";
    v   = alg_vec_from_array(NULL, LEN);
    assert_eq(v.len, 0, msg);
    assert(v.cap > 0, msg);
    alg_vec_drop(&v);
}

void test_swap(void) {
    AlgVec     v        = test_data();
    alg_elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char      *msg;

    msg = "should not swap when NULL";
    alg_vec_swap(NULL, 0, 1);

    msg = "should not swap when i == j";
    alg_vec_swap(&v, 1, 1);
    assert_arr_eq(v.data, v.len, tmp, LEN, msg);

    msg = "should not swap when out of range";
    alg_vec_swap(&v, 0, LEN);
    assert_arr_eq(v.data, v.len, tmp, LEN, msg);

    msg = "should swap head and tail";
    alg_vec_swap(&v, 0, v.len - 1);
    alg_elem_t swap_either_end[LEN] = {5, 1, 2, 3, 4, 0};
    assert_arr_eq(v.data, v.len, swap_either_end, LEN, msg);

    alg_vec_drop(&v);
}

void test_reverse(void) {
    AlgVec v = test_data();
    char  *msg;

    msg = "should reverse";
    alg_vec_reverse(&v);
    alg_elem_t rev[LEN] = {5, 4, 3, 2, 1, 0};
    assert_arr_eq(v.data, v.len, rev, LEN, msg);

    alg_vec_drop(&v);
}

void test_clear(void) {
    AlgVec v = test_data();
    char  *msg;

    msg = "should clear";
    alg_vec_clear(&v);
    assert_eq(v.len, 0, msg);
    assert(v.cap > 0, msg);

    alg_vec_drop(&v);
}

void test_is_empty(void) {
    AlgVec v = test_data();
    char  *msg;

    msg = "should be empty when NULL";
    assert(alg_vec_is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(alg_vec_is_empty(&v), msg);

    msg = "should be empty when len == 0";
    alg_vec_clear(&v);
    assert(alg_vec_is_empty(&v), msg);

    alg_vec_drop(&v);
}

void test_get(void) {
    AlgVec     v = test_data();
    alg_elem_t e;
    char      *msg;

    msg = "should not get when NULL";
    assert_not(alg_vec_get(NULL, 0, NULL), msg);

    msg = "should not get when out of range";
    e   = 0;
    assert_not(alg_vec_get(&v, v.len, &e), msg);
    assert_eq(e, 0, msg);

    msg = "should get";
    assert(alg_vec_get(&v, v.len - 1, &e), msg);
    assert_eq(e, v.data[v.len - 1], msg);

    msg = "should not get when empty";
    alg_vec_clear(&v);
    assert_not(alg_vec_get(&v, 0, NULL), msg);

    alg_vec_drop(&v);
}

void test_first(void) {
    AlgVec     v = test_data();
    alg_elem_t e;
    char      *msg;

    msg = "should not get first when NULL";
    assert_not(alg_vec_first(NULL, NULL), msg);

    msg = "should get first";
    assert(alg_vec_first(&v, &e), msg);
    assert_eq(e, v.data[0], msg);

    msg = "should not get first when empty";
    alg_vec_clear(&v);
    assert_not(alg_vec_first(&v, NULL), msg);

    alg_vec_drop(&v);
}

void test_last(void) {
    AlgVec     v = test_data();
    alg_elem_t e;
    char      *msg;

    msg = "should not get last when NULL";
    assert_not(alg_vec_last(NULL, NULL), msg);

    msg = "should get last";
    assert(alg_vec_last(&v, &e), msg);
    assert_eq(e, v.data[v.len - 1], msg);

    msg = "should not get last when empty";
    alg_vec_clear(&v);
    assert_not(alg_vec_last(&v, NULL), msg);

    alg_vec_drop(&v);
}

void test_set(void) {
    AlgVec     v = test_data();
    alg_elem_t e = 999;
    char      *msg;

    msg = "should not set when NULL";
    assert_not(alg_vec_set(NULL, 0, e), msg);

    msg = "should not set when out of range";
    assert_not(alg_vec_set(&v, v.len, e), msg);
    assert_not(alg_vec_find(&v, e, NULL), msg);

    msg = "should set";
    assert(alg_vec_set(&v, v.len - 1, e), msg);
    assert_eq(v.data[v.len - 1], e, msg);

    alg_vec_drop(&v);
}

void test_find(void) {
    AlgVec v = test_data();
    size_t i;
    char  *msg;

    msg = "should not find when NULL";
    assert_not(alg_vec_find(NULL, 0, NULL), msg);

    msg = "should find at head";
    assert(alg_vec_find(&v, 0, &i), msg);
    assert_eq(i, 0, msg);

    msg = "should find at tail";
    assert(alg_vec_find(&v, v.data[v.len - 1], &i), msg);
    assert_eq(i, v.len - 1, msg);

    msg = "should not find when no exist";
    i   = 0;
    assert_not(alg_vec_find(&v, 999, &i), msg);
    assert_eq(i, 0, msg);

    alg_vec_drop(&v);
}

void test_insert(void) {
    AlgVec     v = test_data();
    alg_elem_t e = 999;
    char      *msg;

    msg = "should not insert when NULL";
    assert_not(alg_vec_insert(NULL, 0, e), msg);

    msg = "should insert at head";
    assert(alg_vec_insert(&v, 0, ++e), msg);
    assert_eq(v.len, LEN + 1, msg);
    assert_eq(v.data[0], e, msg);

    msg = "should insert at middle";
    assert(alg_vec_insert(&v, v.len / 2, ++e), msg);
    assert_eq(v.len, LEN + 2, msg);
    assert_eq(v.data[(v.len - 1) / 2], e, msg);

    msg = "should insert at tail";
    assert(alg_vec_insert(&v, v.len, ++e), msg);
    assert_eq(v.len, LEN + 3, msg);
    assert_eq(v.data[v.len - 1], e, msg);

    msg = "should not insert when out of range";
    assert_not(alg_vec_insert(&v, v.len + 1, ++e), msg);
    assert_eq(v.len, LEN + 3, msg);
    assert_not(alg_vec_find(&v, e, NULL), msg);

    msg            = "should extend when full";
    size_t old_cap = v.cap;
    v.len          = old_cap;
    assert(alg_vec_insert(&v, v.len, ++e), msg);
    assert_eq(v.len, old_cap + 1, msg);
    assert(v.cap > old_cap, msg);
    assert_eq(v.data[v.len - 1], e, msg);

    alg_vec_drop(&v);
}

void test_push_front(void) {
    AlgVec     v = test_data();
    alg_elem_t e = 999;
    char      *msg;

    msg = "should not push_front when NULL";
    assert_not(alg_vec_push_front(NULL, e), msg);

    msg = "should push_front";
    assert(alg_vec_push_front(&v, ++e), msg);
    assert_eq(v.len, LEN + 1, msg);
    assert_eq(v.data[0], e, msg);

    msg            = "should extend when full";
    size_t old_cap = v.cap;
    v.len          = old_cap;
    assert(alg_vec_push_front(&v, ++e), msg);
    assert_eq(v.len, old_cap + 1, msg);
    assert(v.cap > old_cap, msg);
    assert_eq(v.data[0], e, msg);

    alg_vec_drop(&v);
}

void test_push_back(void) {
    AlgVec     v = test_data();
    alg_elem_t e = 999;
    char      *msg;

    msg = "should not push_back when NULL";
    assert_not(alg_vec_push_back(NULL, e), msg);

    msg = "should push_back";
    assert(alg_vec_push_back(&v, ++e), msg);
    assert_eq(v.len, LEN + 1, msg);
    assert_eq(v.data[v.len - 1], e, msg);

    msg            = "should extend when full";
    size_t old_cap = v.cap;
    v.len          = old_cap;
    assert(alg_vec_push_back(&v, ++e), msg);
    assert_eq(v.len, old_cap + 1, msg);
    assert(v.cap > old_cap, msg);
    assert_eq(v.data[v.len - 1], e, msg);

    alg_vec_drop(&v);
}

void test_del(void) {
    AlgVec     v = test_data();
    alg_elem_t e;
    alg_elem_t deleted;
    char      *msg;

    msg = "should not delete when NULL";
    assert_not(alg_vec_del(NULL, 0, NULL), msg);

    msg     = "should delete at head";
    deleted = v.data[0];
    assert(alg_vec_del(&v, 0, &e), msg);
    assert_eq(v.len, LEN - 1, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete at middle";
    deleted = v.data[v.len / 2];
    assert(alg_vec_del(&v, v.len / 2, &e), msg);
    assert_eq(v.len, LEN - 2, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete at tail";
    deleted = v.data[v.len - 1];
    assert(alg_vec_del(&v, v.len - 1, &e), msg);
    assert_eq(v.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not delete when out of range";
    assert_not(alg_vec_del(&v, v.len, &e), msg);
    assert_eq(v.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not delete when empty";
    alg_vec_clear(&v);
    assert_not(alg_vec_del(&v, 0, NULL), msg);
    assert_eq(v.len, 0, msg);

    msg = "should shrink after removing entries";
    alg_vec_drop(&v);
    v                  = alg_vec_create_with(TEST_LARGE_CAP);
    size_t initial_cap = v.cap;
    for (size_t i = 0; i < TEST_SHRINK_LEN; ++i) {
        assert(alg_vec_push_back(&v, i), msg);
    }
    assert_eq(v.len, TEST_SHRINK_LEN, msg);
    assert_eq(v.cap, initial_cap, msg);
    for (size_t i = 0; i < TEST_SHRINK_LEN; ++i) {
        assert(alg_vec_del(&v, 0, NULL), msg);
    }
    assert_eq(v.len, 0, msg);
    assert(v.cap < initial_cap, msg);

    alg_vec_drop(&v);
}

void test_pop_front(void) {
    AlgVec     v = test_data();
    alg_elem_t e;
    alg_elem_t popped;
    char      *msg;

    msg = "should not pop_front when NULL";
    assert_not(alg_vec_pop_front(NULL, NULL), msg);

    msg    = "should pop_front";
    popped = v.data[0];
    assert(alg_vec_pop_front(&v, &e), msg);
    assert_eq(v.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    alg_vec_clear(&v);
    assert_not(alg_vec_pop_front(&v, NULL), msg);
    assert_eq(v.len, 0, msg);

    alg_vec_drop(&v);
}

void test_pop_back(void) {
    AlgVec     v = test_data();
    alg_elem_t e;
    alg_elem_t popped;
    char      *msg;

    msg = "should not pop_back when NULL";
    assert_not(alg_vec_pop_back(NULL, NULL), msg);

    msg    = "should pop_back";
    popped = v.data[v.len - 1];
    assert(alg_vec_pop_back(&v, &e), msg);
    assert_eq(v.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    alg_vec_clear(&v);
    assert_not(alg_vec_pop_back(&v, NULL), msg);
    assert_eq(v.len, 0, msg);

    alg_vec_drop(&v);
}

void test_drop(void) {
    AlgVec v = test_data();
    char  *msg;

    msg = "should drop";
    alg_vec_drop(&v);
    assert_null(v.data, msg);
    assert_eq(v.len, 0, msg);
    assert_eq(v.cap, 0, msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "vector";

    run_test(test_create, mod, target, "create");
    run_test(test_create_with, mod, target, "create_with");
    run_test(test_from_array, mod, target, "from_array");
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
    run_test(test_drop, mod, target, "drop");

    return 0;
}

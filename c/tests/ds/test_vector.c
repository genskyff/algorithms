#include "alg/ds/vector.h"
#include "helper.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    Vec test_data() {                                                          \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    Vec   v = create();
    char *msg;

    msg = "should get a empty vector";
    assert_not_null(v.data, msg);
    assert_eq(v.len, 0, msg);
    assert_eq(v.cap, INIT_CAP, msg);

    drop(&v);
}

void test_create_with(void) {
    size_t cap = 100;
    Vec    v   = create_with(cap);
    char  *msg;

    msg = "should get a empty vector with capacity";
    assert_not_null(v.data, msg);
    assert_eq(v.len, 0, msg);
    assert_eq(v.cap, cap, msg);

    drop(&v);
}

void test_init(void) {
    Vec   v = init(LEN, 0, 1, 2, 3, 4, 5);
    char *msg;

    msg = "should get a initialized vector";
    assert_not_null(v.data, msg);
    assert_eq(v.len, LEN, msg);
    assert_eq(v.cap, INIT_CAP, msg);
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_arr_eq(v.data, v.len, tmp, LEN, msg);

    drop(&v);
}

void test_swap(void) {
    Vec    v        = test_data();
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char  *msg;

    msg = "should not swap when NULL";
    swap(NULL, 0, 1);

    msg = "should not swap when i == j";
    swap(&v, 1, 1);
    assert_arr_eq(v.data, v.len, tmp, LEN, msg);

    msg = "should not swap when out of range";
    swap(&v, 0, LEN);
    assert_arr_eq(v.data, v.len, tmp, LEN, msg);

    msg = "should swap head and tail";
    swap(&v, 0, v.len - 1);
    elem_t swap_either_end[LEN] = {5, 1, 2, 3, 4, 0};
    assert_arr_eq(v.data, v.len, swap_either_end, LEN, msg);

    drop(&v);
}

void test_reverse(void) {
    Vec   v = test_data();
    char *msg;

    msg = "should reverse";
    reverse(&v);
    elem_t rev[LEN] = {5, 4, 3, 2, 1, 0};
    assert_arr_eq(v.data, v.len, rev, LEN, msg);

    drop(&v);
}

void test_clear(void) {
    Vec   v = test_data();
    char *msg;

    msg = "should clear";
    clear(&v);
    assert_eq(v.len, 0, msg);
    assert_eq(v.cap, INIT_CAP, msg);

    drop(&v);
}

void test_is_empty(void) {
    Vec   v = test_data();
    char *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(is_empty(&v), msg);

    msg = "should be empty when len == 0";
    clear(&v);
    assert(is_empty(&v), msg);

    drop(&v);
}

void test_get(void) {
    Vec    v = test_data();
    elem_t e;
    char  *msg;

    msg = "should not get when NULL";
    assert_not(get(NULL, 0, NULL), msg);

    msg = "should not get when out of range";
    e   = 0;
    assert_not(get(&v, v.len, &e), msg);
    assert_eq(e, 0, msg);

    msg = "should get";
    assert(get(&v, v.len - 1, &e), msg);
    assert_eq(e, v.data[v.len - 1], msg);

    msg = "should not get when empty";
    clear(&v);
    assert_not(get(&v, 0, NULL), msg);

    drop(&v);
}

void test_first(void) {
    Vec    v = test_data();
    elem_t e;
    char  *msg;

    msg = "should not get first when NULL";
    assert_not(first(NULL, NULL), msg);

    msg = "should get first";
    assert(first(&v, &e), msg);
    assert_eq(e, v.data[0], msg);

    msg = "should not get first when empty";
    clear(&v);
    assert_not(first(&v, NULL), msg);

    drop(&v);
}

void test_last(void) {
    Vec    v = test_data();
    elem_t e;
    char  *msg;

    msg = "should not get last when NULL";
    assert_not(last(NULL, NULL), msg);

    msg = "should get last";
    assert(last(&v, &e), msg);
    assert_eq(e, v.data[v.len - 1], msg);

    msg = "should not get last when empty";
    clear(&v);
    assert_not(last(&v, NULL), msg);

    drop(&v);
}

void test_set(void) {
    Vec    v = test_data();
    elem_t e = 999;
    char  *msg;

    msg = "should not set when NULL";
    assert_not(set(NULL, 0, e), msg);

    msg = "should not set when out of range";
    assert_not(set(&v, v.len, e), msg);
    assert_not(find(&v, e, NULL), msg);

    msg = "should set";
    assert(set(&v, v.len - 1, e), msg);
    assert_eq(v.data[v.len - 1], e, msg);

    drop(&v);
}

void test_find(void) {
    Vec    v = test_data();
    size_t i;
    char  *msg;

    msg = "should not find when NULL";
    assert_not(find(NULL, 0, NULL), msg);

    msg = "should find at head";
    assert(find(&v, 0, &i), msg);
    assert_eq(i, 0, msg);

    msg = "should find at tail";
    assert(find(&v, v.data[v.len - 1], &i), msg);
    assert_eq(i, v.len - 1, msg);

    msg = "should not find when no exist";
    i   = 0;
    assert_not(find(&v, 999, &i), msg);
    assert_eq(i, 0, msg);

    drop(&v);
}

void test_insert(void) {
    Vec    v = test_data();
    elem_t e = 999;
    char  *msg;

    msg = "should not insert when NULL";
    assert_not(insert(NULL, 0, e), msg);

    msg = "should insert at head";
    assert(insert(&v, 0, ++e), msg);
    assert_eq(v.len, LEN + 1, msg);
    assert_eq(v.data[0], e, msg);

    msg = "should insert at middle";
    assert(insert(&v, v.len / 2, ++e), msg);
    assert_eq(v.len, LEN + 2, msg);
    assert_eq(v.data[(v.len - 1) / 2], e, msg);

    msg = "should insert at tail";
    assert(insert(&v, v.len, ++e), msg);
    assert_eq(v.len, LEN + 3, msg);
    assert_eq(v.data[v.len - 1], e, msg);

    msg = "should not insert when out of range";
    assert_not(insert(&v, v.len + 1, ++e), msg);
    assert_eq(v.len, LEN + 3, msg);
    assert_not(find(&v, e, NULL), msg);

    msg   = "should extend when full";
    v.len = v.cap;
    assert(insert(&v, v.len, ++e), msg);
    assert_eq(v.len, INIT_CAP + 1, msg);
    assert_eq(v.cap, 2 * INIT_CAP, msg);
    assert_eq(v.data[v.len - 1], e, msg);

    drop(&v);
}

void test_push_front(void) {
    Vec    v = test_data();
    elem_t e = 999;
    char  *msg;

    msg = "should not push_front when NULL";
    assert_not(push_front(NULL, e), msg);

    msg = "should push_front";
    assert(push_front(&v, ++e), msg);
    assert_eq(v.len, LEN + 1, msg);
    assert_eq(v.data[0], e, msg);

    msg   = "should extend when full";
    v.len = v.cap;
    assert(push_front(&v, ++e), msg);
    assert_eq(v.len, INIT_CAP + 1, msg);
    assert_eq(v.cap, 2 * INIT_CAP, msg);
    assert_eq(v.data[0], e, msg);

    drop(&v);
}

void test_push_back(void) {
    Vec    v = test_data();
    elem_t e = 999;
    char  *msg;

    msg = "should not push_back when NULL";
    assert_not(push_back(NULL, e), msg);

    msg = "should push_back";
    assert(push_back(&v, ++e), msg);
    assert_eq(v.len, LEN + 1, msg);
    assert_eq(v.data[v.len - 1], e, msg);

    msg   = "should extend when full";
    v.len = v.cap;
    assert(push_back(&v, ++e), msg);
    assert_eq(v.len, INIT_CAP + 1, msg);
    assert_eq(v.cap, 2 * INIT_CAP, msg);
    assert_eq(v.data[v.len - 1], e, msg);

    drop(&v);
}

void test_del(void) {
    Vec    v = test_data();
    elem_t e;
    elem_t deleted;
    char  *msg;

    msg = "should not delete when NULL";
    assert_not(del(NULL, 0, NULL), msg);

    msg     = "should delete at head";
    deleted = v.data[0];
    assert(del(&v, 0, &e), msg);
    assert_eq(v.len, LEN - 1, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete at middle";
    deleted = v.data[v.len / 2];
    assert(del(&v, v.len / 2, &e), msg);
    assert_eq(v.len, LEN - 2, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete at tail";
    deleted = v.data[v.len - 1];
    assert(del(&v, v.len - 1, &e), msg);
    assert_eq(v.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not delete when out of range";
    assert_not(del(&v, v.len, &e), msg);
    assert_eq(v.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not delete when empty";
    clear(&v);
    assert_not(del(&v, 0, NULL), msg);
    assert_eq(v.len, 0, msg);

    msg = "should shrink when load factor < LOWER_FACTOR";
    for (size_t i = 0; i < SHRINK_CAP; ++i) {
        assert(push_back(&v, i), msg);
    }
    assert_eq(v.len, SHRINK_CAP, msg);
    assert_eq(v.cap % INIT_CAP, 0, msg);
    for (size_t i = 0; i < SHRINK_CAP; ++i) {
        assert(del(&v, 0, NULL), msg);
    }
    assert_eq(v.len, 0, msg);
    assert_eq(v.cap % INIT_CAP, 0, msg);

    drop(&v);
}

void test_pop_front(void) {
    Vec    v = test_data();
    elem_t e;
    elem_t popped;
    char  *msg;

    msg = "should not pop_front when NULL";
    assert_not(pop_front(NULL, NULL), msg);

    msg    = "should pop_front";
    popped = v.data[0];
    assert(pop_front(&v, &e), msg);
    assert_eq(v.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    clear(&v);
    assert_not(pop_front(&v, NULL), msg);
    assert_eq(v.len, 0, msg);

    drop(&v);
}

void test_pop_back(void) {
    Vec    v = test_data();
    elem_t e;
    elem_t popped;
    char  *msg;

    msg = "should not pop_back when NULL";
    assert_not(pop_back(NULL, NULL), msg);

    msg    = "should pop_back";
    popped = v.data[v.len - 1];
    assert(pop_back(&v, &e), msg);
    assert_eq(v.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    clear(&v);
    assert_not(pop_back(&v, NULL), msg);
    assert_eq(v.len, 0, msg);

    drop(&v);
}

void test_drop(void) {
    Vec   v = test_data();
    char *msg;

    msg = "should drop";
    drop(&v);
    assert_null(v.data, msg);
    assert_eq(v.len, 0, msg);
    assert_eq(v.cap, 0, msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "vector";

    run_test(test_create, mod, target, "create");
    run_test(test_create_with, mod, target, "create_with");
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
    run_test(test_drop, mod, target, "drop");

    return 0;
}

#include "test.h"
#include "vector.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    Vec test_data() {                                                          \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    char *msg   = "should get a empty vector";
    Vec   empty = create();
    assert(empty.data != NULL, msg);
    assert_eq(empty.len, 0, msg);
    assert_eq(empty.cap, INIT_CAP, msg);
    drop(&empty);
}

void test_init(void) {
    Vec   v   = test_data();
    char *msg = "should get a initialized vector";
    Vec   tmp = init(LEN, 0, 1, 2, 3, 4, 5);
    assert(tmp.data != NULL, msg);
    assert_eq(tmp.len, LEN, msg);
    assert_eq(tmp.cap, INIT_CAP, msg);
    assert_arr_eq(tmp.data, tmp.len, v.data, v.len, msg);
    drop(&tmp);
    drop(&v);
}

void test_swap(void) {
    Vec    v        = test_data();
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};

    char *msg;

    msg = "should not swap when i == j";
    swap(&v, 1, 1);
    assert_arr_eq(v.data, v.len, tmp, LEN, msg);

    msg = "should not swap when out of range";
    swap(&v, 0, LEN);
    assert_arr_eq(v.data, v.len, tmp, LEN, msg);

    msg = "should swap";
    swap(&v, 0, v.len - 1);
    elem_t swap_side[LEN] = {5, 1, 2, 3, 4, 0};
    assert_arr_eq(v.data, v.len, swap_side, LEN, msg);

    drop(&v);
}

void test_reverse(void) {
    Vec v = test_data();

    char *msg;

    msg = "should reverse";
    reverse(&v);
    elem_t rev[LEN] = {5, 4, 3, 2, 1, 0};
    assert_arr_eq(v.data, v.len, rev, LEN, msg);

    drop(&v);
}

void test_is_empty(void) {
    Vec v = test_data();

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

    char *msg;

    msg = "should not get when out of range";
    e   = 0;
    assert_not(get(&v, v.len, &e), msg);
    assert_eq(e, 0, msg);

    msg = "should get";
    assert(get(&v, v.len - 1, &e), msg);
    assert_eq(e, v.data[v.len - 1], msg);

    drop(&v);
}

void test_set(void) {
    Vec    v = test_data();
    elem_t e = 999;

    char *msg;

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

    char *msg;

    msg = "should find at [0]";
    assert(find(&v, 0, &i), msg);
    assert(i == 0, msg);

    msg = "should find at tail";
    assert(find(&v, 5, &i), msg);
    assert(i == 5, msg);

    msg = "should not find when no exist";
    i   = 0;
    assert_not(find(&v, 999, &i), msg);
    assert_eq(i, 0, msg);

    drop(&v);
}

void test_insert(void) {
    Vec v = test_data();

    elem_t e = 10;

    char *msg;

    msg = "should not insert when NULL";
    assert(!insert(NULL, 0, e), msg);

    msg = "should insert in head";
    assert(insert(&v, 0, ++e), msg);
    assert_eq(v.len, LEN + 1, msg);
    assert_eq(v.data[0], e, msg);

    msg = "should insert in middle";
    assert(insert(&v, 3, ++e), msg);
    assert_eq(v.len, LEN + 2, msg);
    assert_eq(v.data[3], e, msg);

    msg = "should insert in tail";
    assert(insert(&v, v.len, ++e), msg);
    assert_eq(v.len, LEN + 3, msg);
    assert_eq(v.data[LEN + 2], e, msg);

    msg = "should not insert when index is out of range";
    assert(!insert(&v, v.len + 1, ++e), msg);
    assert_eq(v.len, LEN + 3, msg);
    assert(!find(&v, e, NULL), msg);

    drop(&v);
}

void test_push(void) {
    Vec v = test_data();

    elem_t e = 10;

    char *msg;

    msg = "should not push when NULL";
    assert(!push(NULL, e), msg);

    msg = "should push";
    assert(push(&v, e), msg);
    assert_eq(v.len, LEN + 1, msg);
    assert_eq(v.data[v.len - 1], e, msg);

    msg   = "should extend when full";
    v.len = v.cap;
    assert(push(&v, e), msg);
    assert_eq(v.len, INIT_CAP + 1, msg);
    assert_eq(v.cap, 2 * INIT_CAP, msg);
    assert_eq(v.data[v.len - 1], e, msg);

    drop(&v);
}

void test_del(void) {
    Vec v = test_data();

    elem_t e;
    elem_t deleted;

    char *msg;

    msg = "should not delete when NULL";
    assert(!del(NULL, 0, NULL), msg);

    msg     = "should delete in head";
    deleted = v.data[0];
    assert(del(&v, 0, &e), msg);
    assert_eq(v.len, LEN - 1, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete in middle";
    deleted = v.data[v.len / 2];
    assert(del(&v, v.len / 2, &e), msg);
    assert_eq(v.len, LEN - 2, msg);
    assert_eq(e, deleted, msg);

    msg     = "should delete in tail";
    deleted = v.data[v.len - 1];
    assert(del(&v, v.len - 1, &e), msg);
    assert_eq(v.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not delete when index is out of range";
    assert(!del(&v, v.len, &e), msg);
    assert_eq(v.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    drop(&v);
}

void test_pop(void) {
    Vec v = test_data();

    elem_t e;
    elem_t popped;

    char *msg;

    msg = "should not pop when NULL";
    assert(!pop(NULL, NULL), msg);

    msg    = "should pop";
    popped = v.data[v.len - 1];
    assert(pop(&v, &e), msg);
    assert_eq(v.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop when empty";
    clear(&v);
    assert(!pop(&v, &e), msg);
    assert_eq(v.len, 0, msg);
    assert_eq(e, popped, msg);

    drop(&v);
}

void test_drop(void) {
    Vec v = test_data();

    char *msg;

    msg = "should drop";
    drop(&v);
    assert(v.data == NULL, msg);
    assert_eq(v.len, 0, msg);
    assert_eq(v.cap, 0, msg);
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "vector_create");
    run_test(test_init, prefix, "vector_init");
    run_test(test_swap, prefix, "vector_swap");
    run_test(test_reverse, prefix, "vector_reverse");
    run_test(test_is_empty, prefix, "vector_is_empty");
    run_test(test_get, prefix, "vector_get");
    run_test(test_set, prefix, "vector_set");
    run_test(test_find, prefix, "vector_find");
    run_test(test_insert, prefix, "vector_insert");
    run_test(test_push, prefix, "vector_push");
    run_test(test_del, prefix, "vector_del");
    run_test(test_pop, prefix, "vector_pop");
    run_test(test_drop, prefix, "vector_drop");

    return 0;
}

#include "test.h"
#include "vector.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    Vec test_data() {                                                          \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

bool test_create(void) {
    Vec   v = create();
    bool  is_all_passed;
    char *msg;

    msg           = "should get a empty vector";
    is_all_passed = assert(v.data != NULL, msg);
    is_all_passed = assert_eq(v.len, 0, msg);
    is_all_passed = assert_eq(v.cap, INIT_CAP, msg);

    drop(&v);
    return is_all_passed;
}

bool test_init(void) {
    Vec v   = init(LEN, 0, 1, 2, 3, 4, 5);
    Vec tmp = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should get a initialized vector";
    is_all_passed = assert(v.data != NULL, msg);
    is_all_passed = assert_eq(v.len, LEN, msg);
    is_all_passed = assert_eq(v.cap, INIT_CAP, msg);
    is_all_passed = assert_arr_eq(v.data, v.len, tmp.data, tmp.len, msg);

    drop(&v);
    return is_all_passed;
}

bool test_swap(void) {
    Vec v = test_data();

    // expect array's name like swap_<i>_<j>
    elem_t swap_0_5[] = {5, 1, 2, 3, 4, 0};
    elem_t swap_4_1[] = {5, 4, 2, 3, 1, 0};

    bool  is_all_passed;
    char *msg;

    msg = "should swap(0, 5)";
    swap(&v, 0, 5);
    is_all_passed = assert_arr_eq(v.data, v.len, swap_0_5, LEN, msg);

    msg = "should swap(4, 1)";
    swap(&v, 4, 1);
    is_all_passed = assert_arr_eq(v.data, v.len, swap_4_1, LEN, msg);

    msg = "should not swap(3, 3)";
    swap(&v, 3, 3);
    is_all_passed = assert_arr_eq(v.data, v.len, swap_4_1, LEN, msg);

    msg = "should not swap when out of range";
    swap(&v, 0, LEN);
    is_all_passed = assert_arr_eq(v.data, v.len, swap_4_1, LEN, msg);

    drop(&v);
    return is_all_passed;
}

bool test_reverse(void) {
    Vec    v     = test_data();
    elem_t rev[] = {5, 4, 3, 2, 1, 0};

    bool  is_all_passed;
    char *msg;

    msg = "should reverse";
    reverse(&v);
    is_all_passed = assert_arr_eq(v.data, v.len, rev, LEN, msg);

    drop(&v);
    return is_all_passed;
}

bool test_is_empty(void) {
    Vec v = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should be empty when NULL";
    is_all_passed = assert(is_empty(NULL), msg);

    msg           = "should not be empty";
    is_all_passed = assert(!is_empty(&v), msg);

    msg = "should be empty after clear";
    clear(&v);
    is_all_passed = assert(is_empty(&v), msg);

    drop(&v);
    return is_all_passed;
}

bool test_get(void) {
    Vec v = test_data();

    elem_t e;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not get when NULL";
    is_all_passed = assert(!get(NULL, 0, NULL), msg);

    msg           = "should get";
    is_all_passed = assert(get(&v, v.len - 1, &e), msg);
    is_all_passed = assert_eq(e, v.data[v.len - 1], msg);

    msg           = "should not get when out of range";
    is_all_passed = assert(!get(&v, v.len, &e), msg);
    is_all_passed = assert_eq(e, v.data[v.len - 1], msg);

    drop(&v);
    return is_all_passed;
}

bool test_set(void) {
    Vec v = test_data();

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not set when NULL";
    is_all_passed = assert(!set(NULL, 0, e), msg);

    msg           = "should set";
    is_all_passed = assert(set(&v, v.len - 1, e), msg);
    is_all_passed = assert_eq(v.data[v.len - 1], e, msg);

    msg           = "should not set when out of range";
    is_all_passed = assert(!set(&v, v.len, e), msg);

    drop(&v);
    return is_all_passed;
}

bool test_find(void) {
    Vec v = test_data();

    size_t i;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not find when NULL";
    is_all_passed = assert(!find(NULL, 0, NULL), msg);

    msg           = "should find";
    is_all_passed = assert(find(&v, 5, &i), msg);
    is_all_passed = assert(i == 5, msg);

    msg           = "should not find";
    is_all_passed = assert(!find(&v, 6, &i), msg);
    is_all_passed = assert_eq(i, 5, msg);

    drop(&v);
    return is_all_passed;
}

bool test_insert(void) {
    Vec v = test_data();

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not insert when NULL";
    is_all_passed = assert(!insert(NULL, 0, e), msg);

    msg           = "should insert in head";
    is_all_passed = assert(insert(&v, 0, ++e), msg);
    is_all_passed = assert_eq(v.len, LEN + 1, msg);
    is_all_passed = assert_eq(v.data[0], e, msg);

    msg           = "should insert in middle";
    is_all_passed = assert(insert(&v, 3, ++e), msg);
    is_all_passed = assert_eq(v.len, LEN + 2, msg);
    is_all_passed = assert_eq(v.data[3], e, msg);

    msg           = "should insert in tail";
    is_all_passed = assert(insert(&v, v.len, ++e), msg);
    is_all_passed = assert_eq(v.len, LEN + 3, msg);
    is_all_passed = assert_eq(v.data[LEN + 2], e, msg);

    msg           = "should not insert when index is out of range";
    is_all_passed = assert(!insert(&v, v.len + 1, ++e), msg);
    is_all_passed = assert_eq(v.len, LEN + 3, msg);
    is_all_passed = assert(!find(&v, e, NULL), msg);

    drop(&v);
    return is_all_passed;
}

bool test_push(void) {
    Vec v = test_data();

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not push when NULL";
    is_all_passed = assert(!push(NULL, e), msg);

    msg           = "should push";
    is_all_passed = assert(push(&v, e), msg);
    is_all_passed = assert_eq(v.len, LEN + 1, msg);
    is_all_passed = assert_eq(v.data[v.len - 1], e, msg);

    msg           = "should extend when full";
    v.len         = v.cap;
    is_all_passed = assert(push(&v, e), msg);
    is_all_passed = assert_eq(v.len, INIT_CAP + 1, msg);
    is_all_passed = assert_eq(v.cap, 2 * INIT_CAP, msg);
    is_all_passed = assert_eq(v.data[v.len - 1], e, msg);

    drop(&v);
    return is_all_passed;
}

bool test_del(void) {
    Vec v = test_data();

    elem_t e;
    elem_t deleted;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not delete when NULL";
    is_all_passed = assert(!del(NULL, 0, NULL), msg);

    msg           = "should delete in head";
    deleted       = v.data[0];
    is_all_passed = assert(del(&v, 0, &e), msg);
    is_all_passed = assert_eq(v.len, LEN - 1, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    msg           = "should delete in middle";
    deleted       = v.data[v.len / 2];
    is_all_passed = assert(del(&v, v.len / 2, &e), msg);
    is_all_passed = assert_eq(v.len, LEN - 2, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    msg           = "should delete in tail";
    deleted       = v.data[v.len - 1];
    is_all_passed = assert(del(&v, v.len - 1, &e), msg);
    is_all_passed = assert_eq(v.len, LEN - 3, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    msg           = "should not delete when index is out of range";
    is_all_passed = assert(!del(&v, v.len, &e), msg);
    is_all_passed = assert_eq(v.len, LEN - 3, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    drop(&v);
    return is_all_passed;
}

bool test_pop(void) {
    Vec v = test_data();

    elem_t e;
    elem_t popped;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not pop when NULL";
    is_all_passed = assert(!pop(NULL, NULL), msg);

    msg           = "should pop";
    popped        = v.data[v.len - 1];
    is_all_passed = assert(pop(&v, &e), msg);
    is_all_passed = assert_eq(v.len, LEN - 1, msg);
    is_all_passed = assert_eq(e, popped, msg);

    msg = "should not pop when empty";
    clear(&v);
    is_all_passed = assert(!pop(&v, &e), msg);
    is_all_passed = assert_eq(v.len, 0, msg);
    is_all_passed = assert_eq(e, popped, msg);

    drop(&v);
    return is_all_passed;
}

bool test_drop(void) {
    Vec v = test_data();

    bool  is_all_passed;
    char *msg;

    msg = "should drop";
    drop(&v);
    is_all_passed = assert(v.data == NULL, msg);
    is_all_passed = assert_eq(v.len, 0, msg);
    is_all_passed = assert_eq(v.cap, 0, msg);

    return is_all_passed;
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

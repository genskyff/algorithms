#include "array_list.h"
#include "helper.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    SqList test_data() {                                                       \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    SqList list = create();

    char *msg;

    msg = "should get a empty sqlist";
    assert_eq(list.len, 0, msg);
}

void test_init(void) {
    SqList list = init(LEN, 0, 1, 2, 3, 4, 5);
    SqList tmp  = test_data();

    char *msg;

    msg = "should get a initialized sqlist";
    assert_eq(list.len, LEN, msg);
    assert_arr_eq(list.data, list.len, tmp.data, tmp.len, msg);
}

void test_swap(void) {
    SqList list = test_data();

    // expect array's name like swap_<i>_<j>
    elem_t swap_0_5[] = {5, 1, 2, 3, 4, 0};
    elem_t swap_4_1[] = {5, 4, 2, 3, 1, 0};

    char *msg;

    msg = "should swap(0, 5)";
    swap(&list, 0, 5);
    assert_arr_eq(list.data, list.len, swap_0_5, LEN, msg);

    msg = "should swap(4, 1)";
    swap(&list, 4, 1);
    assert_arr_eq(list.data, list.len, swap_4_1, LEN, msg);

    msg = "should not swap(3, 3)";
    swap(&list, 3, 3);
    assert_arr_eq(list.data, list.len, swap_4_1, LEN, msg);

    msg = "should not swap when out of range";
    swap(&list, 0, LEN);
    assert_arr_eq(list.data, list.len, swap_4_1, LEN, msg);
}

void test_reverse(void) {
    SqList list = test_data();

    elem_t rev[] = {5, 4, 3, 2, 1, 0};

    char *msg;

    msg = "should reverse";
    reverse(&list);
    assert_arr_eq(list.data, list.len, rev, LEN, msg);
}

void test_is_empty(void) {
    SqList list = test_data();

    char *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert(!is_empty(&list), msg);

    msg = "should be empty when empty";
    clear(&list);
    assert(is_empty(&list), msg);
}

void test_get(void) {
    SqList list = test_data();

    elem_t e;

    char *msg;

    msg = "should not get when NULL";
    assert(!get(NULL, 0, NULL), msg);

    msg = "should get";
    assert(get(&list, list.len - 1, &e), msg);
    assert_eq(e, list.data[list.len - 1], msg);

    msg = "should not get when out of range";
    assert(!get(&list, list.len, &e), msg);
    assert_eq(e, list.data[list.len - 1], msg);
}

void test_set(void) {
    SqList list = test_data();

    elem_t e = 10;

    char *msg;

    msg = "should not set when NULL";
    assert(!set(NULL, 0, e), msg);

    msg = "should set";
    assert(set(&list, list.len - 1, e), msg);
    assert_eq(list.data[list.len - 1], e, msg);

    msg = "should not set when out of range";
    assert(!set(&list, list.len, e), msg);
}

void test_find(void) {
    SqList list = test_data();

    size_t i;

    char *msg;

    msg = "should not find when NULL";
    assert(!find(NULL, 0, NULL), msg);

    msg = "should find";
    assert(find(&list, 5, &i), msg);
    assert_eq(i, 5, msg);

    msg = "should not find";
    assert(!find(&list, 6, &i), msg);
    assert_eq(i, 5, msg);
}

void test_insert(void) {
    SqList list = test_data();

    elem_t e = 10;

    char *msg;

    msg = "should not insert when NULL";
    assert(!insert(NULL, 0, e), msg);

    msg = "should insert in head";
    assert(insert(&list, 0, ++e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.data[0], e, msg);

    msg = "should insert in middle";
    assert(insert(&list, 3, ++e), msg);
    assert_eq(list.len, LEN + 2, msg);
    assert_eq(list.data[3], e, msg);

    msg = "should insert in tail";
    assert(insert(&list, list.len, ++e), msg);
    assert_eq(list.len, LEN + 3, msg);
    assert_eq(list.data[LEN + 2], e, msg);

    msg = "should not insert when index is out of range";
    assert(!insert(&list, list.len + 1, ++e), msg);
    assert_eq(list.len, LEN + 3, msg);
    assert(!find(&list, e, NULL), msg);
}

void test_push(void) {
    SqList list = test_data();

    elem_t e = 10;

    char *msg;

    msg = "should not push when NULL";
    assert(!push(NULL, e), msg);

    msg = "should push";
    assert(push(&list, e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.data[list.len - 1], e, msg);

    msg      = "should not push when full";
    list.len = MAXLEN;
    assert(!push(&list, e), msg);
    assert_eq(list.len, MAXLEN, msg);
}

void test_del(void) {
    SqList list = test_data();

    elem_t e;
    elem_t deleted;

    char *msg;

    msg = "should not del when NULL";
    assert(!del(NULL, 0, NULL), msg);

    msg     = "should del in head";
    deleted = list.data[0];
    assert(del(&list, 0, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, deleted, msg);

    msg     = "should del in middle";
    deleted = list.data[list.len / 2];
    assert(del(&list, list.len / 2, &e), msg);
    assert_eq(list.len, LEN - 2, msg);
    assert_eq(e, deleted, msg);

    msg     = "should del in tail";
    deleted = list.data[list.len - 1];
    assert(del(&list, list.len - 1, &e), msg);
    assert_eq(list.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not del when index is out of range";
    assert(!del(&list, list.len, &e), msg);
    assert_eq(list.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);
}

void test_pop(void) {
    SqList list = test_data();

    elem_t e;
    elem_t popped;

    char *msg;

    msg = "should not pop when NULL";
    assert(!pop(NULL, NULL), msg);

    msg    = "should pop";
    popped = list.data[list.len - 1];
    assert(pop(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop when empty";
    clear(&list);
    assert(!pop(&list, &e), msg);
    assert_eq(list.len, 0, msg);
    assert_eq(e, popped, msg);
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "sqlist_create");
    run_test(test_init, prefix, "sqlist_init");
    run_test(test_swap, prefix, "sqlist_swap");
    run_test(test_reverse, prefix, "sqlist_reverse");
    run_test(test_is_empty, prefix, "sqlist_is_empty");
    run_test(test_get, prefix, "sqlist_get");
    run_test(test_set, prefix, "sqlist_set");
    run_test(test_find, prefix, "sqlist_find");
    run_test(test_insert, prefix, "sqlist_insert");
    run_test(test_push, prefix, "sqlist_push");
    run_test(test_del, prefix, "sqlist_del");
    run_test(test_pop, prefix, "sqlist_pop");

    return 0;
}

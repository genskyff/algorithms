#include "sqlist.h"
#include "test_helper.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    SqList test_data() {                                                       \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

bool test_create(void) {
    SqList list = create();
    bool   is_all_passed;
    char  *msg;

    msg           = "should get a empty sqlist";
    is_all_passed = assert_eq(list.len, 0, msg);

    return is_all_passed;
}

bool test_init(void) {
    SqList list = init(LEN, 0, 1, 2, 3, 4, 5);
    SqList tmp  = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should get a initialized sqlist";
    is_all_passed = assert_eq(list.len, LEN, msg);
    is_all_passed = assert_arr_eq(list.data, list.len, tmp.data, tmp.len, msg);

    return is_all_passed;
}

bool test_swap(void) {
    SqList list = test_data();

    // expect array's name like swap_<i>_<j>
    elem_t swap_0_5[] = {5, 1, 2, 3, 4, 0};
    elem_t swap_4_1[] = {5, 4, 2, 3, 1, 0};

    bool  is_all_passed;
    char *msg;

    msg = "should swap(0, 5)";
    swap(&list, 0, 5);
    is_all_passed = assert_arr_eq(list.data, list.len, swap_0_5, LEN, msg);

    msg = "should swap(4, 1)";
    swap(&list, 4, 1);
    is_all_passed = assert_arr_eq(list.data, list.len, swap_4_1, LEN, msg);

    msg = "should not swap(3, 3)";
    swap(&list, 3, 3);
    is_all_passed = assert_arr_eq(list.data, list.len, swap_4_1, LEN, msg);

    msg = "should not swap when out of range";
    swap(&list, 0, LEN);
    is_all_passed = assert_arr_eq(list.data, list.len, swap_4_1, LEN, msg);

    return is_all_passed;
}

bool test_reverse(void) {
    SqList list = test_data();

    elem_t rev[] = {5, 4, 3, 2, 1, 0};

    bool  is_all_passed;
    char *msg;

    msg = "should reverse";
    reverse(&list);
    is_all_passed = assert_arr_eq(list.data, list.len, rev, LEN, msg);

    return is_all_passed;
}

bool test_is_empty(void) {
    SqList list = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should be empty when NULL";
    is_all_passed = assert(is_empty(NULL), msg);

    msg           = "should not be empty";
    is_all_passed = assert(!is_empty(&list), msg);

    msg = "should be empty when empty";
    clear(&list);
    is_all_passed = assert(is_empty(&list), msg);

    return is_all_passed;
}

bool test_get(void) {
    SqList list = test_data();

    elem_t e;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not get when NULL";
    is_all_passed = assert(!get(NULL, 0, NULL), msg);

    msg           = "should get";
    is_all_passed = assert(get(&list, list.len - 1, &e), msg);
    is_all_passed = assert_eq(e, list.data[list.len - 1], msg);

    msg           = "should not get when out of range";
    is_all_passed = assert(!get(&list, list.len, &e), msg);
    is_all_passed = assert_eq(e, list.data[list.len - 1], msg);

    return is_all_passed;
}

bool test_set(void) {
    SqList list = test_data();

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not set when NULL";
    is_all_passed = assert(!set(NULL, 0, e), msg);

    msg           = "should set";
    is_all_passed = assert(set(&list, list.len - 1, e), msg);
    is_all_passed = assert_eq(list.data[list.len - 1], e, msg);

    msg           = "should not set when out of range";
    is_all_passed = assert(!set(&list, list.len, e), msg);

    return is_all_passed;
}

bool test_find(void) {
    SqList list = test_data();

    size_t i;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not find when NULL";
    is_all_passed = assert(!find(NULL, 0, NULL), msg);

    msg           = "should find";
    is_all_passed = assert(find(&list, 5, &i), msg);
    is_all_passed = assert_eq(i, 5, msg);

    msg           = "should not find";
    is_all_passed = assert(!find(&list, 6, &i), msg);
    is_all_passed = assert_eq(i, 5, msg);

    return is_all_passed;
}

bool test_insert(void) {
    SqList list = test_data();

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not insert when NULL";
    is_all_passed = assert(!insert(NULL, 0, e), msg);

    msg           = "should insert in head";
    is_all_passed = assert(insert(&list, 0, ++e), msg);
    is_all_passed = assert_eq(list.len, LEN + 1, msg);
    is_all_passed = assert_eq(list.data[0], e, msg);

    msg           = "should insert in middle";
    is_all_passed = assert(insert(&list, 3, ++e), msg);
    is_all_passed = assert_eq(list.len, LEN + 2, msg);
    is_all_passed = assert_eq(list.data[3], e, msg);

    msg           = "should insert in tail";
    is_all_passed = assert(insert(&list, list.len, ++e), msg);
    is_all_passed = assert_eq(list.len, LEN + 3, msg);
    is_all_passed = assert_eq(list.data[LEN + 2], e, msg);

    msg           = "should not insert when index is out of range";
    is_all_passed = assert(!insert(&list, list.len + 1, ++e), msg);
    is_all_passed = assert_eq(list.len, LEN + 3, msg);
    is_all_passed = assert(!find(&list, e, NULL), msg);

    return is_all_passed;
}

bool test_push(void) {
    SqList list = test_data();

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not push when NULL";
    is_all_passed = assert(!push(NULL, e), msg);

    msg           = "should push";
    is_all_passed = assert(push(&list, e), msg);
    is_all_passed = assert_eq(list.len, LEN + 1, msg);
    is_all_passed = assert_eq(list.data[list.len - 1], e, msg);

    msg           = "should not push when full";
    list.len      = MAXLEN;
    is_all_passed = assert(!push(&list, e), msg);
    is_all_passed = assert_eq(list.len, MAXLEN, msg);

    return is_all_passed;
}

bool test_del(void) {
    SqList list = test_data();

    elem_t e;
    elem_t deleted;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not del when NULL";
    is_all_passed = assert(!del(NULL, 0, NULL), msg);

    msg           = "should del in head";
    deleted       = list.data[0];
    is_all_passed = assert(del(&list, 0, &e), msg);
    is_all_passed = assert_eq(list.len, LEN - 1, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    msg           = "should del in middle";
    deleted       = list.data[list.len / 2];
    is_all_passed = assert(del(&list, list.len / 2, &e), msg);
    is_all_passed = assert_eq(list.len, LEN - 2, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    msg           = "should del in tail";
    deleted       = list.data[list.len - 1];
    is_all_passed = assert(del(&list, list.len - 1, &e), msg);
    is_all_passed = assert_eq(list.len, LEN - 3, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    msg           = "should not del when index is out of range";
    is_all_passed = assert(!del(&list, list.len, &e), msg);
    is_all_passed = assert_eq(list.len, LEN - 3, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    return is_all_passed;
}

bool test_pop(void) {
    SqList list = test_data();

    elem_t e;
    elem_t popped;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not pop when NULL";
    is_all_passed = assert(!pop(NULL, NULL), msg);

    msg           = "should pop";
    popped        = list.data[list.len - 1];
    is_all_passed = assert(pop(&list, &e), msg);
    is_all_passed = assert_eq(list.len, LEN - 1, msg);
    is_all_passed = assert_eq(e, popped, msg);

    msg = "should not pop when empty";
    clear(&list);
    is_all_passed = assert(!pop(&list, &e), msg);
    is_all_passed = assert_eq(list.len, 0, msg);
    is_all_passed = assert_eq(e, popped, msg);

    return is_all_passed;
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

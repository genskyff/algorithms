#include "sqlist.h"
#include "test.h"
#include "type.h"
#include "utils.h"

#define LEN 6
SqList LIST = {.data = {0, 1, 2, 3, 4, 5}, .len = LEN};

bool test_sqlist(void) {
    SqList list = sqlist();
    bool   is_all_passed;
    char  *msg;

    msg           = "should get a empty sqlist";
    is_all_passed = assert_eq(list.len, 0, msg);

    return is_all_passed;
}

bool test_sqlist_init(void) {
    size_t n      = 6;
    SqList list   = sqlist_init(n, 0, 1, 2, 3, 4, 5);
    elem_t data[] = {0, 1, 2, 3, 4, 5};

    bool  is_all_passed;
    char *msg;

    msg           = "should get a initialized sqlist";
    is_all_passed = assert_eq(list.len, n, msg);
    is_all_passed = assert_arr_eq(list.data, n, data, n, msg);

    return is_all_passed;
}

bool test_is_empty(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    bool  is_all_passed;
    char *msg;

    msg           = "should be empty when NULL";
    is_all_passed = assert(is_empty(NULL), msg);

    msg           = "should not be empty";
    is_all_passed = assert(!is_empty(&tmp), msg);

    msg = "should be empty when empty";
    clear(&tmp);
    is_all_passed = assert(is_empty(&tmp), msg);

    return is_all_passed;
}

bool test_get(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    elem_t e;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not get when NULL";
    is_all_passed = assert(!get(NULL, 0, NULL), msg);

    msg           = "should get";
    is_all_passed = assert(get(&tmp, tmp.len - 1, &e), msg);
    is_all_passed = assert_eq(e, tmp.data[tmp.len - 1], msg);

    msg           = "should not get";
    is_all_passed = assert(!get(&tmp, tmp.len, &e), msg);
    is_all_passed = assert_eq(e, tmp.data[tmp.len - 1], msg);

    return is_all_passed;
}

bool test_set(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not set when NULL";
    is_all_passed = assert(!set(NULL, 0, e), msg);

    msg           = "should set";
    is_all_passed = assert(set(&tmp, tmp.len - 1, e), msg);
    is_all_passed = assert_eq(tmp.data[tmp.len - 1], e, msg);

    msg           = "should not set when index is out of range";
    is_all_passed = assert(!set(&tmp, tmp.len, e), msg);

    return is_all_passed;
}

bool test_find(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    size_t i;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not find when NULL";
    is_all_passed = assert(!find(NULL, 0, NULL), msg);

    msg           = "should find";
    is_all_passed = assert(find(&tmp, 5, &i), msg);
    is_all_passed = assert_eq(i, 5, msg);

    msg           = "should not find";
    is_all_passed = assert(!find(&tmp, 6, &i), msg);
    is_all_passed = assert_eq(i, 5, msg);

    return is_all_passed;
}

bool test_insert(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not insert when NULL";
    is_all_passed = assert(!insert(NULL, 0, e), msg);

    msg           = "should insert in head";
    is_all_passed = assert(insert(&tmp, 0, ++e), msg);
    is_all_passed = assert_eq(tmp.len, LEN + 1, msg);
    is_all_passed = assert_eq(tmp.data[0], e, msg);

    msg           = "should insert in middle";
    is_all_passed = assert(insert(&tmp, 3, ++e), msg);
    is_all_passed = assert_eq(tmp.len, LEN + 2, msg);
    is_all_passed = assert_eq(tmp.data[3], e, msg);

    msg           = "should insert in tail";
    is_all_passed = assert(insert(&tmp, tmp.len, ++e), msg);
    is_all_passed = assert_eq(tmp.len, LEN + 3, msg);
    is_all_passed = assert_eq(tmp.data[LEN + 2], e, msg);

    msg           = "should not insert when index is out of range";
    is_all_passed = assert(!insert(&tmp, tmp.len + 1, ++e), msg);
    is_all_passed = assert_eq(tmp.len, LEN + 3, msg);
    is_all_passed = assert(!find(&tmp, e, NULL), msg);

    return is_all_passed;
}

bool test_push(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not push when NULL";
    is_all_passed = assert(!push(NULL, e), msg);

    msg           = "should push";
    is_all_passed = assert(push(&tmp, e), msg);
    is_all_passed = assert_eq(tmp.len, LEN + 1, msg);
    is_all_passed = assert_eq(tmp.data[tmp.len - 1], e, msg);

    msg           = "should not push when full";
    tmp.len       = MAXLEN;
    is_all_passed = assert(!push(&tmp, e), msg);
    is_all_passed = assert_eq(tmp.len, MAXLEN, msg);

    return is_all_passed;
}

bool test_del(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    elem_t e;
    elem_t deleted;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not del when NULL";
    is_all_passed = assert(!del(NULL, 0, NULL), msg);

    msg           = "should del in head";
    deleted       = tmp.data[0];
    is_all_passed = assert(del(&tmp, 0, &e), msg);
    is_all_passed = assert_eq(tmp.len, LEN - 1, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    msg           = "should del in middle";
    deleted       = tmp.data[tmp.len / 2];
    is_all_passed = assert(del(&tmp, tmp.len / 2, &e), msg);
    is_all_passed = assert_eq(tmp.len, LEN - 2, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    msg           = "should del in tail";
    deleted       = tmp.data[tmp.len - 1];
    is_all_passed = assert(del(&tmp, tmp.len - 1, &e), msg);
    is_all_passed = assert_eq(tmp.len, LEN - 3, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    msg           = "should not del when index is out of range";
    is_all_passed = assert(!del(&tmp, tmp.len, &e), msg);
    is_all_passed = assert_eq(tmp.len, LEN - 3, msg);
    is_all_passed = assert_eq(e, deleted, msg);

    return is_all_passed;
}

bool test_pop(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    elem_t e;
    elem_t popped;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not pop when NULL";
    is_all_passed = assert(!pop(NULL, NULL), msg);

    msg           = "should pop";
    popped        = tmp.data[tmp.len - 1];
    is_all_passed = assert(pop(&tmp, &e), msg);
    is_all_passed = assert_eq(tmp.len, LEN - 1, msg);
    is_all_passed = assert_eq(e, popped, msg);

    msg = "should not pop when empty";
    clear(&tmp);
    is_all_passed = assert(!pop(&tmp, &e), msg);
    is_all_passed = assert_eq(tmp.len, 0, msg);
    is_all_passed = assert_eq(e, popped, msg);

    return is_all_passed;
}

int main(void) {
    char *prefix = "ds";
    run_test(test_sqlist, prefix, "sqlist_new");
    run_test(test_sqlist_init, prefix, "sqlist_init");
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

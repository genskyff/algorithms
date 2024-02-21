#include "sqlist.h"
#include "test.h"
#include "type.h"
#include "utils.h"

#define LEN 6
SqList LIST = {.data = {0, 1, 2, 3, 4, 5}, .len = LEN};

bool test_is_empty(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);
    clear(&tmp);

    return assert(is_empty(tmp), NULL);
}

bool test_get(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    elem_t e;
    bool   is_all_passed;
    char *msg;

    msg = "should get";
    is_all_passed = assert(get(tmp, tmp.len - 1, &e), msg);
    is_all_passed = assert(e == tmp.data[tmp.len - 1], msg);

    msg = "should not get";
    is_all_passed = assert(!get(tmp, tmp.len, &e), msg);
    is_all_passed = assert(e == tmp.data[tmp.len - 1], msg);

    return is_all_passed;
}

bool test_find(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    size_t i;
    bool   is_all_passed;
    char *msg;

    msg = "should find";
    is_all_passed = assert(find(tmp, 5, &i), msg);
    is_all_passed = assert(i == 5, msg);

    msg = "should not find";
    is_all_passed = assert(!find(tmp, 6, &i), msg);
    is_all_passed = assert(i == 5, msg);

    return is_all_passed;
}

bool test_insert(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    elem_t e = 10;
    bool   is_all_passed;
    char *msg;

    msg = "should insert in head";
    is_all_passed = assert(insert(&tmp, 0, ++e), msg);
    is_all_passed = assert(tmp.len == LEN + 1, msg);
    is_all_passed = assert(tmp.data[0] == e, msg);

    msg = "should insert in middle";
    is_all_passed = assert(insert(&tmp, 3, ++e), msg);
    is_all_passed = assert(tmp.len == LEN + 2, msg);
    is_all_passed = assert(tmp.data[3] == e, msg);

    msg = "should insert in tail";
    is_all_passed = assert(insert(&tmp, tmp.len, ++e), msg);
    is_all_passed = assert(tmp.len == LEN + 3, msg);
    is_all_passed = assert(tmp.data[LEN + 2] == e, msg);

    msg = "should not insert when index is out of range";
    is_all_passed = assert(!insert(&tmp, tmp.len + 1, ++e), msg);
    is_all_passed = assert(tmp.len == LEN + 3, msg);
    is_all_passed = assert(!find(tmp, e, NULL), msg);

    return is_all_passed;
}

bool test_update(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    return false;
}

bool test_delete(void) {
    SqList tmp = {.len = LIST.len};
    _copy(tmp.data, tmp.len, LIST.data, LIST.len);

    return false;
}

int main(void) {
    char *prefix = "ds";
    run_test(test_is_empty, prefix, "sqlist_is_empty");
    run_test(test_get, prefix, "sqlist_get");
    run_test(test_find, prefix, "sqlist_find");
    run_test(test_insert, prefix, "sqlist_insert");

    return 0;
}

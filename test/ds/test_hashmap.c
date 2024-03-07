#include "hashmap.h"
#include "helper.h"
#include "quick.h"
#include "util.h"
#include <stdlib.h>

#define LEN 6
HashMap test_data() {
    key_t   keys[LEN]   = {"a", "b", "c", "d", "e", "f"};
    value_t values[LEN] = {1, 2, 3, 4, 5, 6};

    return init(keys, values, LEN);
}

void test_create(void) {
    HashMap map = create();
    char   *msg;

    msg = "should get a empty hashmap";
    assert_eq(map.len, 0, msg);
    assert_eq(map.cap, INIT_CAP, msg);
    for (size_t i = 0; i < map.cap; ++i) {
        assert_null(map.buckets[i], msg);
    }
}

void test_init(void) {
    HashMap map = test_data();
    char   *msg;

    msg = "should get a initialized hashmap";
    assert_eq(map.len, LEN, msg);
    assert_eq(map.cap, INIT_CAP, msg);
}

void test_clear(void) {
    HashMap map = test_data();
    char   *msg;

    msg = "should clear";
    clear(&map);
    assert_eq(map.len, 0, msg);
    assert_eq(map.cap, INIT_CAP, msg);
    for (size_t i = 0; i < map.cap; ++i) {
        assert_null(map.buckets[i], msg);
    }
}

void test_is_empty(void) {
    HashMap map = test_data();
    char   *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(is_empty(&map), msg);

    msg = "should be empty when len == 0";
    clear(&map);
    assert(is_empty(&map), msg);
}

void test_get_keys(void) {
    HashMap map = test_data();
    char   *msg;

    msg = "should get NULL when NULL";
    assert_null(get_keys(NULL), msg);

    msg             = "should get keys";
    key_t *keys     = get_keys(&map);
    key_t  tmp[LEN] = {"a", "b", "c", "d", "e", "f"};
    qsort(keys, LEN, sizeof(key_t), _cmp_str);
    assert_arr_eq((elem_t *)keys, map.len, (elem_t *)tmp, LEN, msg);
}

void test_get_values(void) {
    HashMap map = test_data();
    char   *msg;

    msg = "should get NULL when NULL";
    assert_null(get_values(NULL), msg);

    msg               = "should get values";
    value_t *vals     = get_values(&map);
    value_t  tmp[LEN] = {1, 2, 3, 4, 5, 6};
    qsort(vals, LEN, sizeof(value_t), _cmp);
    assert_arr_eq((elem_t *)vals, map.len, (elem_t *)tmp, LEN, msg);
}

void test_get(void) {
    HashMap map = test_data();
    value_t val;
    char   *msg;

    msg = "should not get when NULL";
    assert_not(get(NULL, "a", NULL), msg);

    msg = "should get value by key";
    assert(get(&map, "a", &val), msg);
    assert_eq(val, 1, msg);

    msg = "should not get when key not exists";
    val = 999;
    assert_not(get(&map, "z", NULL), msg);
    assert_eq(val, 999, msg);
}

int main(void) {
    char   *mod    = "ds";
    char   *target = "hashmap";
    HashMap map    = test_data();
    show(NULL, NULL);
    show_keys(NULL, NULL);
    show_values(NULL, NULL);
    show(NULL, &map);
    show_keys(NULL, &map);
    show_values(NULL, &map);

    run_test(test_create, mod, target, "create");
    run_test(test_init, mod, target, "init");
    run_test(test_clear, mod, target, "clear");
    run_test(test_is_empty, mod, target, "is_empty");
    run_test(test_get_keys, mod, target, "get_keys");
    run_test(test_get_values, mod, target, "get_values");
    run_test(test_get, mod, target, "get");

    return 0;
}

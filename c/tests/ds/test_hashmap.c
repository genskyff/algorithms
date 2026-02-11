#include "alg/ds/hashmap.h"
#include "helper.h"
#include "utils.h"
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
        assert_null(map.buckets[i].head, msg);
    }
}

void test_create_with(void) {
    size_t  cap = 100;
    HashMap map = create_with(cap);
    char   *msg;

    msg = "should get a empty hashmap with capacity";
    assert_eq(map.len, 0, msg);
    assert_eq(map.cap, cap, msg);
    for (size_t i = 0; i < map.cap; ++i) {
        assert_null(map.buckets[i].head, msg);
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
        assert_null(map.buckets[i].head, msg);
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

void test_insert(void) {
    HashMap map = create();
    key_t   key = "a";
    value_t val = 1;
    char   *msg;

    msg = "should not insert when NULL";
    assert_not(insert(NULL, key, val), msg);

    msg = "should insert";
    assert(insert(&map, key, val), msg);
    assert_eq(map.len, 1, msg);
    assert(get(&map, key, NULL), msg);

    msg = "should update value when key exists";
    val = 2;
    assert(insert(&map, key, val), msg);
    assert_eq(map.len, 2, msg);
    assert(get(&map, key, &val), msg);
    assert_eq(val, 2, msg);

    msg = "should extend when load factor > 0.75";
    clear(&map);
    char *keys[INIT_CAP];
    for (size_t i = 0; i < INIT_CAP; ++i) {
        keys[i] = (char *)calloc(10, sizeof(char));
        sprintf(keys[i], "%zu", i);
        assert(insert(&map, keys[i], i), msg);
    }
    assert_eq(map.len, INIT_CAP, msg);
    assert_eq(map.cap, INIT_CAP * 2, msg);
    for (size_t i = 0; i < INIT_CAP; ++i) {
        assert(get(&map, keys[i], &val), key);
        assert_eq(val, i, msg);
        assert_eq(val, i, msg);
    }
}

void test_del(void) {
    HashMap map = test_data();
    value_t val;
    char   *msg;

    msg = "should not delete when NULL";
    assert_not(del(NULL, "a"), msg);

    msg = "should delete";
    assert(del(&map, "a"), msg);
    assert_eq(map.len, LEN - 1, msg);
    assert_not(get(&map, "a", NULL), msg);

    msg = "should not delete when key not exists";
    assert_not(del(&map, "z"), msg);
    assert_eq(map.len, LEN - 1, msg);

    msg = "should not delete when empty";
    clear(&map);
    assert_not(del(&map, "a"), msg);
    assert_eq(map.len, 0, msg);

    msg = "should shrink when load factor < LOWER_FACTOR";
    clear(&map);
    char *keys[SHRINK_CAP];
    for (size_t i = 0; i < SHRINK_CAP; ++i) {
        keys[i] = (char *)calloc(10, sizeof(char));
        sprintf(keys[i], "%zu", i);
        assert(insert(&map, keys[i], i), msg);
    }
    assert_eq(map.len, SHRINK_CAP, msg);
    assert_eq(map.cap % INIT_CAP, 0, msg);
    for (size_t i = 0; i < SHRINK_CAP; ++i) {
        assert(del(&map, keys[i]), msg);
    }
    assert_eq(map.len, 0, msg);
    assert_eq(map.cap % INIT_CAP, 0, msg);
}

void test_drop(void) {
    HashMap map = test_data();
    char   *msg;

    msg = "should drop";
    drop(&map);
    assert_null(map.buckets, msg);
    assert_eq(map.len, 0, msg);
    assert_eq(map.cap, 0, msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "hashmap";

    run_test(test_create, mod, target, "create");
    run_test(test_create_with, mod, target, "create_with");
    run_test(test_init, mod, target, "init");
    run_test(test_clear, mod, target, "clear");
    run_test(test_is_empty, mod, target, "is_empty");
    run_test(test_get_keys, mod, target, "get_keys");
    run_test(test_get_values, mod, target, "get_values");
    run_test(test_get, mod, target, "get");
    run_test(test_insert, mod, target, "insert");
    run_test(test_del, mod, target, "del");
    run_test(test_drop, mod, target, "drop");

    return 0;
}

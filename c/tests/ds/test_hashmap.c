#include "alg/ds/hashmap.h"
#include "internal/utils.h"
#include "support/helper.h"
#include <stdlib.h>

#define LEN 6
enum {
    TEST_GROW_LEN   = 32,
    TEST_LARGE_CAP  = 2048,
    TEST_SMALL_CAP  = 8,
    TEST_SHRINK_LEN = 512,
};

AlgHashMap test_data() {
    alg_hashmap_key_t   keys[LEN]   = {"a", "b", "c", "d", "e", "f"};
    alg_hashmap_value_t values[LEN] = {1, 2, 3, 4, 5, 6};

    return alg_hashmap_init(keys, values, LEN);
}

void test_create(void) {
    AlgHashMap map = alg_hashmap_create();
    char      *msg;

    msg = "should get a empty hashmap";
    assert_eq(map.len, 0, msg);
    assert(map.cap > 0, msg);
    for (size_t i = 0; i < map.cap; ++i) {
        assert_null(map.buckets[i].head, msg);
        assert_eq(map.buckets[i].len, 0, msg);
    }

    alg_hashmap_drop(&map);
}

void test_create_with(void) {
    size_t     cap = 100;
    AlgHashMap map = alg_hashmap_create_with(cap);
    char      *msg;

    msg = "should get a empty hashmap with capacity";
    assert_eq(map.len, 0, msg);
    assert_eq(map.cap, cap, msg);
    for (size_t i = 0; i < map.cap; ++i) {
        assert_null(map.buckets[i].head, msg);
    }

    alg_hashmap_drop(&map);
}

void test_init(void) {
    AlgHashMap map = test_data();
    char      *msg;

    msg = "should get a initialized hashmap";
    assert_eq(map.len, LEN, msg);
    assert(map.cap >= map.len, msg);

    alg_hashmap_drop(&map);

    char                first_key[] = "same";
    char                equal_key[] = "same";
    alg_hashmap_key_t   keys[]      = {first_key, equal_key};
    alg_hashmap_value_t values[]    = {1, 2};
    map                             = alg_hashmap_init(keys, values, 2);

    msg = "should update duplicate string key";
    assert_eq(map.len, 1, msg);
    alg_hashmap_value_t value;
    assert(alg_hashmap_get(&map, first_key, &value), msg);
    assert_eq(value, 2, msg);

    alg_hashmap_drop(&map);
}

void test_clear(void) {
    AlgHashMap map = test_data();
    char      *msg;

    msg = "should clear";
    alg_hashmap_clear(&map);
    assert_eq(map.len, 0, msg);
    assert(map.cap > 0, msg);
    for (size_t i = 0; i < map.cap; ++i) {
        assert_null(map.buckets[i].head, msg);
        assert_eq(map.buckets[i].len, 0, msg);
    }

    alg_hashmap_drop(&map);
}

void test_is_empty(void) {
    AlgHashMap map = test_data();
    char      *msg;

    msg = "should be empty when NULL";
    assert(alg_hashmap_is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(alg_hashmap_is_empty(&map), msg);

    msg = "should be empty when len == 0";
    alg_hashmap_clear(&map);
    assert(alg_hashmap_is_empty(&map), msg);

    alg_hashmap_drop(&map);
}

void test_get_keys(void) {
    AlgHashMap map = test_data();
    char      *msg;

    msg = "should get NULL when NULL";
    assert_null(alg_hashmap_get_keys(NULL), msg);

    msg                         = "should get keys";
    alg_hashmap_key_t *keys     = alg_hashmap_get_keys(&map);
    alg_hashmap_key_t  tmp[LEN] = {"a", "b", "c", "d", "e", "f"};
    qsort(keys, LEN, sizeof(alg_hashmap_key_t), alg_internal_cmp_str);
    for (size_t i = 0; i < LEN; ++i) {
        assert_str_eq(keys[i], tmp[i], msg);
    }

    free(keys);
    alg_hashmap_drop(&map);
}

void test_get_values(void) {
    AlgHashMap map = test_data();
    char      *msg;

    msg = "should get NULL when NULL";
    assert_null(alg_hashmap_get_values(NULL), msg);

    msg                           = "should get values";
    alg_hashmap_value_t *vals     = alg_hashmap_get_values(&map);
    alg_hashmap_value_t  tmp[LEN] = {1, 2, 3, 4, 5, 6};
    qsort(vals, LEN, sizeof(alg_hashmap_value_t), alg_internal_cmp);
    assert_arr_eq((alg_elem_t *)vals, map.len, (alg_elem_t *)tmp, LEN, msg);

    free(vals);
    alg_hashmap_drop(&map);
}

void test_get(void) {
    AlgHashMap          map = test_data();
    alg_hashmap_value_t val;
    char               *msg;

    msg = "should not get when NULL";
    assert_not(alg_hashmap_get(NULL, "a", NULL), msg);

    msg = "should get value by key";
    assert(alg_hashmap_get(&map, "a", &val), msg);
    assert_eq(val, 1, msg);

    msg = "should not get when key not exists";
    val = 999;
    assert_not(alg_hashmap_get(&map, "z", NULL), msg);
    assert_eq(val, 999, msg);

    alg_hashmap_drop(&map);
}

void test_insert(void) {
    AlgHashMap          map         = alg_hashmap_create();
    char                key[]       = "a";
    char                equal_key[] = "a";
    alg_hashmap_value_t val         = 1;
    char               *msg;

    msg = "should not insert when NULL";
    assert_not(alg_hashmap_insert(NULL, key, val), msg);

    msg = "should insert";
    assert(alg_hashmap_insert(&map, key, val), msg);
    assert_eq(map.len, 1, msg);
    assert(alg_hashmap_get(&map, key, NULL), msg);

    msg = "should update value when key exists";
    val = 2;
    assert(alg_hashmap_insert(&map, equal_key, val), msg);
    assert_eq(map.len, 1, msg);
    assert(alg_hashmap_get(&map, key, &val), msg);
    assert_eq(val, 2, msg);
    alg_hashmap_key_t *stored_keys = alg_hashmap_get_keys(&map);
    assert(stored_keys[0] == key, msg);
    free(stored_keys);

    msg = "should grow as entries are added";
    alg_hashmap_drop(&map);
    map                = alg_hashmap_create_with(TEST_SMALL_CAP);
    size_t initial_cap = map.cap;
    char  *keys[TEST_GROW_LEN];
    for (size_t i = 0; i < TEST_GROW_LEN; ++i) {
        keys[i] = (char *)calloc(10, sizeof(char));
        sprintf(keys[i], "%zu", i);
        assert(alg_hashmap_insert(&map, keys[i], i), msg);
    }
    assert_eq(map.len, TEST_GROW_LEN, msg);
    assert(map.cap > initial_cap, msg);
    for (size_t i = 0; i < TEST_GROW_LEN; ++i) {
        assert(alg_hashmap_get(&map, keys[i], &val), key);
        assert_eq(val, i, msg);
        assert_eq(val, i, msg);
    }

    alg_hashmap_drop(&map);
    for (size_t i = 0; i < TEST_GROW_LEN; ++i) {
        free(keys[i]);
    }
}

void test_del(void) {
    AlgHashMap map = test_data();
    char      *msg;

    msg = "should not delete when NULL";
    assert_not(alg_hashmap_del(NULL, "a"), msg);

    msg = "should delete";
    assert(alg_hashmap_del(&map, "a"), msg);
    assert_eq(map.len, LEN - 1, msg);
    assert_not(alg_hashmap_get(&map, "a", NULL), msg);

    msg = "should not delete when key not exists";
    assert_not(alg_hashmap_del(&map, "z"), msg);
    assert_eq(map.len, LEN - 1, msg);

    msg = "should not delete when empty";
    alg_hashmap_clear(&map);
    assert_not(alg_hashmap_del(&map, "a"), msg);
    assert_eq(map.len, 0, msg);

    msg = "should shrink after removing entries";
    alg_hashmap_drop(&map);
    map                = alg_hashmap_create_with(TEST_LARGE_CAP);
    size_t initial_cap = map.cap;
    char  *keys[TEST_SHRINK_LEN];
    for (size_t i = 0; i < TEST_SHRINK_LEN; ++i) {
        keys[i] = (char *)calloc(10, sizeof(char));
        sprintf(keys[i], "%zu", i);
        assert(alg_hashmap_insert(&map, keys[i], i), msg);
    }
    assert_eq(map.len, TEST_SHRINK_LEN, msg);
    assert_eq(map.cap, initial_cap, msg);
    for (size_t i = 0; i < TEST_SHRINK_LEN; ++i) {
        assert(alg_hashmap_del(&map, keys[i]), msg);
        free(keys[i]);
    }
    assert_eq(map.len, 0, msg);
    assert(map.cap < initial_cap, msg);

    alg_hashmap_drop(&map);
}

void test_drop(void) {
    AlgHashMap map = test_data();
    char      *msg;

    msg = "should drop";
    alg_hashmap_drop(&map);
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

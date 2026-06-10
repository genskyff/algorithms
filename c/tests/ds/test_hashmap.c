#include "alg/ds/hashmap.h"
#include "internal/utils.h"
#include "support/helper.h"
#include <stdlib.h>

#define LEN 6
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
    assert_eq(map.cap, ALG_HASHMAP_INIT_CAP, msg);
    for (size_t i = 0; i < map.cap; ++i) {
        assert_null(map.buckets[i].head, msg);
    }
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
}

void test_init(void) {
    AlgHashMap map = test_data();
    char      *msg;

    msg = "should get a initialized hashmap";
    assert_eq(map.len, LEN, msg);
    assert_eq(map.cap, ALG_HASHMAP_INIT_CAP, msg);
}

void test_clear(void) {
    AlgHashMap map = test_data();
    char      *msg;

    msg = "should clear";
    alg_hashmap_clear(&map);
    assert_eq(map.len, 0, msg);
    assert_eq(map.cap, ALG_HASHMAP_INIT_CAP, msg);
    for (size_t i = 0; i < map.cap; ++i) {
        assert_null(map.buckets[i].head, msg);
    }
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
    assert_arr_eq((alg_elem_t *)keys, map.len, (alg_elem_t *)tmp, LEN, msg);
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
}

void test_insert(void) {
    AlgHashMap          map = alg_hashmap_create();
    alg_hashmap_key_t   key = "a";
    alg_hashmap_value_t val = 1;
    char               *msg;

    msg = "should not insert when NULL";
    assert_not(alg_hashmap_insert(NULL, key, val), msg);

    msg = "should insert";
    assert(alg_hashmap_insert(&map, key, val), msg);
    assert_eq(map.len, 1, msg);
    assert(alg_hashmap_get(&map, key, NULL), msg);

    msg = "should update value when key exists";
    val = 2;
    assert(alg_hashmap_insert(&map, key, val), msg);
    assert_eq(map.len, 2, msg);
    assert(alg_hashmap_get(&map, key, &val), msg);
    assert_eq(val, 2, msg);

    msg = "should extend when load factor > 0.75";
    alg_hashmap_clear(&map);
    char *keys[ALG_HASHMAP_INIT_CAP];
    for (size_t i = 0; i < ALG_HASHMAP_INIT_CAP; ++i) {
        keys[i] = (char *)calloc(10, sizeof(char));
        sprintf(keys[i], "%zu", i);
        assert(alg_hashmap_insert(&map, keys[i], i), msg);
    }
    assert_eq(map.len, ALG_HASHMAP_INIT_CAP, msg);
    assert_eq(map.cap, ALG_HASHMAP_INIT_CAP * 2, msg);
    for (size_t i = 0; i < ALG_HASHMAP_INIT_CAP; ++i) {
        assert(alg_hashmap_get(&map, keys[i], &val), key);
        assert_eq(val, i, msg);
        assert_eq(val, i, msg);
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

    msg = "should shrink when load factor < LOWER_FACTOR";
    alg_hashmap_clear(&map);
    char *keys[ALG_HASHMAP_SHRINK_CAP];
    for (size_t i = 0; i < ALG_HASHMAP_SHRINK_CAP; ++i) {
        keys[i] = (char *)calloc(10, sizeof(char));
        sprintf(keys[i], "%zu", i);
        assert(alg_hashmap_insert(&map, keys[i], i), msg);
    }
    assert_eq(map.len, ALG_HASHMAP_SHRINK_CAP, msg);
    assert_eq(map.cap % ALG_HASHMAP_INIT_CAP, 0, msg);
    for (size_t i = 0; i < ALG_HASHMAP_SHRINK_CAP; ++i) {
        assert(alg_hashmap_del(&map, keys[i]), msg);
    }
    assert_eq(map.len, 0, msg);
    assert_eq(map.cap % ALG_HASHMAP_INIT_CAP, 0, msg);
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

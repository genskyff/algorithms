#include "hashmap.h"
#include "helper.h"

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
        assert_null(map.bucket[i], msg);
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
        assert_null(map.bucket[i], msg);
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

    return 0;
}

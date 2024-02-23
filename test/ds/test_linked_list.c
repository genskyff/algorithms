#include "linked_list.h"
#include "test.h"
#include "type.h"
#include <stdlib.h>

#define LEN 6
#define TEST_DATA(...)                                                         \
    LinkedList test_data() {                                                   \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

bool test_create(void) {
    LinkedList list = create();
    bool       is_all_passed;
    char      *msg;

    msg           = "should get a empty linked list";
    is_all_passed = assert(list.head == NULL, msg);
    is_all_passed = assert_eq(list.len, 0, msg);

    return is_all_passed;
}

bool test_init(void) {
    LinkedList list     = init(LEN, 0, 1, 2, 3, 4, 5);
    elem_t     tmp[LEN] = {0, 1, 2, 3, 4, 5};
    elem_t    *arr      = to_array(list);

    bool  is_all_passed;
    char *msg;

    msg           = "should get a initialized linked list";
    is_all_passed = assert(list.head != NULL, msg);
    is_all_passed = assert_eq(list.len, LEN, msg);
    is_all_passed = assert_arr_eq(arr, list.len, tmp, LEN, msg);

    return is_all_passed;
}

bool test_from_array(void) {
    elem_t arr[LEN] = {0, 1, 2, 3, 4, 5};

    bool  is_all_passed;
    char *msg;

    msg             = "should get a linked list from array";
    LinkedList list = from_array(arr, LEN);
    is_all_passed   = assert(list.head != NULL, msg);
    is_all_passed   = assert_eq(list.len, LEN, msg);

    msg           = "should get a empty linked list from NULL array";
    is_all_passed = assert(from_array(NULL, LEN).head == NULL, msg);

    return is_all_passed;
}

bool test_to_array(void) {
    LinkedList list     = test_data();
    elem_t     tmp[LEN] = {0, 1, 2, 3, 4, 5};

    bool  is_all_passed;
    char *msg;

    msg           = "should get an array from linked list";
    elem_t *arr   = to_array(list);
    is_all_passed = assert(arr != NULL, msg);
    is_all_passed = assert_arr_eq(arr, list.len, tmp, LEN, msg);

    msg           = "should get NULL from empty linked list";
    is_all_passed = assert(to_array(create()) == NULL, msg);

    return is_all_passed;
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "linked_list_create");
    run_test(test_init, prefix, "linked_list_init");
    run_test(test_from_array, prefix, "linked_list_from_array");
    run_test(test_to_array, prefix, "linked_list_to_array");

    return 0;
}

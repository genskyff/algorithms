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
    elem_t    *arr      = to_array(&list);

    bool  is_all_passed;
    char *msg;

    msg           = "should get a initialized linked list";
    is_all_passed = assert(list.head != NULL, msg);
    is_all_passed = assert_eq(list.len, LEN, msg);
    is_all_passed = assert_arr_eq(arr, list.len, tmp, LEN, msg);

    free(arr);
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
    elem_t *arr   = to_array(&list);
    is_all_passed = assert(arr != NULL, msg);
    is_all_passed = assert_arr_eq(arr, list.len, tmp, LEN, msg);

    msg              = "should get NULL from empty linked list";
    LinkedList empty = create();
    is_all_passed    = assert(to_array(&empty) == NULL, msg);

    free(arr);
    return is_all_passed;
}

bool test_swap(void) {
    LinkedList list = test_data();

    // expect array's name like swap_<i>_<j>
    elem_t swap_0_5[] = {5, 1, 2, 3, 4, 0};
    elem_t swap_0_1[] = {1, 5, 2, 3, 4, 0};

    bool  is_all_passed;
    char *msg;

    msg = "should swap(0, 5)";
    swap(&list, 0, 5);
    elem_t *tmp   = to_array(&list);
    is_all_passed = assert_arr_eq(tmp, list.len, swap_0_5, LEN, msg);
    free(tmp);

    msg = "should swap(0, 1)";
    swap(&list, 0, 1);
    tmp           = to_array(&list);
    is_all_passed = assert_arr_eq(tmp, list.len, swap_0_1, LEN, msg);
    free(tmp);

    msg = "should not swap(3, 3)";
    swap(&list, 3, 3);
    tmp           = to_array(&list);
    is_all_passed = assert_arr_eq(tmp, list.len, swap_0_1, LEN, msg);
    free(tmp);

    return is_all_passed;
}

bool test_reverse(void) {
    LinkedList list  = test_data();
    elem_t     rev[] = {5, 4, 3, 2, 1, 0};

    bool  is_all_passed;
    char *msg;

    msg = "should reverse";
    reverse(&list);
    elem_t *tmp   = to_array(&list);
    is_all_passed = assert_arr_eq(tmp, list.len, tmp, LEN, msg);
    free(tmp);

    return is_all_passed;
}

bool test_clear(void) {
    LinkedList list = test_data();
    clear(&list);

    bool  is_all_passed;
    char *msg;

    msg           = "should clear the linked list";
    is_all_passed = assert(list.head == NULL, msg);
    is_all_passed = assert_eq(list.len, 0, msg);

    return is_all_passed;
}

bool test_is_empty(void) {
    LinkedList list = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should return false for non-empty linked list";
    is_all_passed = assert(!is_empty(&list), msg);

    msg = "should return true for empty linked list";
    clear(&list);
    is_all_passed = assert(is_empty(&list), msg);

    return is_all_passed;
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "linked_list_create");
    run_test(test_init, prefix, "linked_list_init");
    run_test(test_from_array, prefix, "linked_list_from_array");
    run_test(test_to_array, prefix, "linked_list_to_array");
    run_test(test_swap, prefix, "linked_list_swap");
    run_test(test_reverse, prefix, "linked_list_reverse");
    run_test(test_clear, prefix, "linked_list_clear");
    run_test(test_is_empty, prefix, "linked_list_is_empty");

    return 0;
}

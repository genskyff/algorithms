#include "linked_list.h"
#include "test.h"
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
    is_all_passed = assert_eq(length(&list), 0, msg);

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
    is_all_passed = assert_eq(length(&list), LEN, msg);
    is_all_passed = assert_arr_eq(arr, length(&list), tmp, LEN, msg);

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
    is_all_passed   = assert_eq(length(&list), LEN, msg);

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
    is_all_passed = assert_arr_eq(arr, length(&list), tmp, LEN, msg);

    msg              = "should get NULL from empty linked list";
    LinkedList empty = create();
    is_all_passed    = assert(to_array(&empty) == NULL, msg);

    free(arr);
    return is_all_passed;
}

bool test_length(void) {
    LinkedList list = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should get the length of linked list";
    is_all_passed = assert_eq(length(&list), LEN, msg);

    msg              = "should get 0 from empty linked list";
    LinkedList empty = create();
    is_all_passed    = assert_eq(length(&empty), 0, msg);

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
    is_all_passed = assert_arr_eq(tmp, length(&list), swap_0_5, LEN, msg);
    free(tmp);

    msg = "should swap(0, 1)";
    swap(&list, 0, 1);
    tmp           = to_array(&list);
    is_all_passed = assert_arr_eq(tmp, length(&list), swap_0_1, LEN, msg);
    free(tmp);

    msg = "should not swap(3, 3)";
    swap(&list, 3, 3);
    tmp           = to_array(&list);
    is_all_passed = assert_arr_eq(tmp, length(&list), swap_0_1, LEN, msg);
    free(tmp);

    msg = "should not swap when out of range";
    swap(&list, 0, LEN);
    tmp = to_array(&list);
    is_all_passed = assert_arr_eq(tmp, length(&list), swap_0_1, LEN, msg);
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
    is_all_passed = assert_arr_eq(tmp, length(&list), tmp, LEN, msg);
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
    is_all_passed = assert_eq(length(&list), 0, msg);

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

bool test_get(void) {
    LinkedList list = test_data();
    elem_t     e;

    bool  is_all_passed;
    char *msg;

    msg           = "should not get when NULL";
    is_all_passed = assert(!get(NULL, 0, &e), msg);

    msg           = "should get";
    is_all_passed = assert(get(&list, 0, &e), msg);
    is_all_passed = assert_eq(e, 0, msg);

    msg           = "should not get when out of range";
    is_all_passed = assert(!get(&list, length(&list), &e), msg);

    return is_all_passed;
}

bool test_set(void) {
    LinkedList list = test_data();

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not set when NULL";
    is_all_passed = assert(!set(NULL, 0, e), msg);

    msg           = "should set";
    is_all_passed = assert(set(&list, 0, e), msg);
    is_all_passed = assert_eq(list.head->data, 10, msg);

    msg           = "should not set when out of range";
    is_all_passed = assert(!set(&list, length(&list), e), msg);

    return is_all_passed;
}

bool test_find(void) {
    LinkedList list = test_data();

    size_t i;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not find when NULL";
    is_all_passed = assert(!find(NULL, 0, NULL), msg);

    msg           = "should find";
    is_all_passed = assert(find(&list, 5, &i), msg);
    is_all_passed = assert_eq(i, 5, msg);

    msg           = "should not";
    is_all_passed = assert(!find(&list, 6, &i), msg);

    return is_all_passed;
}

bool test_insert(void) {
    LinkedList list = test_data();

    bool  is_all_passed = true;
    char *msg;

    msg           = "should insert";
    is_all_passed = assert(insert(&list, 0, 10), msg);
    is_all_passed = assert_eq(list.head->data, 10, msg);
    is_all_passed = assert_eq(length(&list), LEN + 1, msg);

    msg           = "should not insert when out of range";
    is_all_passed = assert(!insert(&list, length(&list) + 1, 10), msg);

    return is_all_passed;
}

bool test_push(void) {
    LinkedList list = test_data();

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not push when NULL";
    is_all_passed = assert(!push(NULL, e), msg);

    msg           = "should push";
    is_all_passed = assert(push(&list, e), msg);
    elem_t last;
    get(&list, length(&list) - 1, &last);
    is_all_passed = assert_eq(last, e, msg);
    is_all_passed = assert_eq(length(&list), LEN + 1, msg);

    return is_all_passed;
}

bool test_del(void) {
    LinkedList list = test_data();

    elem_t e;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not del when NULL";
    is_all_passed = assert(!del(NULL, 0, &e), msg);

    msg           = "should del";
    is_all_passed = assert(del(&list, 0, &e), msg);
    is_all_passed = assert_eq(e, 0, msg);
    is_all_passed = assert_eq(list.head->data, 1, msg);
    is_all_passed = assert_eq(length(&list), LEN - 1, msg);

    msg           = "should not del when out of range";
    is_all_passed = assert(!del(&list, length(&list), &e), msg);

    return is_all_passed;
}

bool test_pop(void) {
    LinkedList list = test_data();

    elem_t e;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not pop when NULL";
    is_all_passed = assert(!pop(NULL, &e), msg);

    msg           = "should pop";
    is_all_passed = assert(pop(&list, &e), msg);
    is_all_passed = assert_eq(e, 5, msg);
    is_all_passed = assert_eq(length(&list), LEN - 1, msg);

    return is_all_passed;
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "linked_list_create");
    run_test(test_init, prefix, "linked_list_init");
    run_test(test_from_array, prefix, "linked_list_from_array");
    run_test(test_to_array, prefix, "linked_list_to_array");
    run_test(test_length, prefix, "linked_list_length");
    run_test(test_swap, prefix, "linked_list_swap");
    run_test(test_reverse, prefix, "linked_list_reverse");
    run_test(test_clear, prefix, "linked_list_clear");
    run_test(test_is_empty, prefix, "linked_list_is_empty");
    run_test(test_get, prefix, "linked_list_get");
    run_test(test_set, prefix, "linked_list_set");
    run_test(test_find, prefix, "linked_list_find");
    run_test(test_insert, prefix, "linked_list_insert");
    run_test(test_push, prefix, "linked_list_push");
    run_test(test_del, prefix, "linked_list_del");
    run_test(test_pop, prefix, "linked_list_pop");

    return 0;
}

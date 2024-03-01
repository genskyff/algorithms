#include "linked_stack.h"
#include "test_helper.h"
#include <stdlib.h>

#define LEN 6
#define TEST_DATA(...)                                                         \
    LinkedStack test_data() {                                                  \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

bool test_create(void) {
    LinkedStack stack = create();
    bool        is_all_passed;
    char       *msg;

    msg           = "should get a empty linked stack";
    is_all_passed = assert(stack.top == NULL, msg);
    is_all_passed = assert_eq(stack.len, 0, msg);

    return is_all_passed;
}

bool test_init(void) {
    LinkedStack stack    = init(LEN, 0, 1, 2, 3, 4, 5);
    elem_t      tmp[LEN] = {0, 1, 2, 3, 4, 5};
    elem_t     *arr      = to_array(&stack);

    bool  is_all_passed;
    char *msg;

    msg           = "should get a initialized linked stack";
    is_all_passed = assert(stack.top != NULL, msg);
    is_all_passed = assert_eq(stack.len, LEN, msg);
    is_all_passed = assert_arr_eq(arr, stack.len, tmp, LEN, msg);

    free(arr);
    return is_all_passed;
}

bool test_from_array(void) {
    elem_t arr[LEN] = {0, 1, 2, 3, 4, 5};

    bool  is_all_passed;
    char *msg;

    msg               = "should get a linked stack from array";
    LinkedStack stack = from_array(arr, LEN);
    is_all_passed     = assert(stack.top != NULL, msg);
    is_all_passed     = assert_eq(stack.len, LEN, msg);

    msg           = "should get a empty linked stack from NULL array";
    is_all_passed = assert(from_array(NULL, LEN).top == NULL, msg);

    return is_all_passed;
}

bool test_to_array(void) {
    LinkedStack stack    = test_data();
    elem_t      tmp[LEN] = {0, 1, 2, 3, 4, 5};

    bool  is_all_passed;
    char *msg;

    msg           = "should get an array from linked stack";
    elem_t *arr   = to_array(&stack);
    is_all_passed = assert(arr != NULL, msg);
    is_all_passed = assert_arr_eq(arr, stack.len, tmp, LEN, msg);
    free(arr);

    msg               = "should get NULL from empty linked stack";
    LinkedStack empty = create();
    is_all_passed     = assert(to_array(&empty) == NULL, msg);

    return is_all_passed;
}

bool test_clear(void) {
    LinkedStack stack = test_data();

    bool  is_all_passed;
    char *msg;

    msg = "should clear the linked stack";
    clear(&stack);
    is_all_passed = assert(stack.top == NULL, msg);
    is_all_passed = assert_eq(stack.len, 0, msg);

    return is_all_passed;
}

bool test_is_empty(void) {
    LinkedStack stack = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should return false for non-empty linked stack";
    is_all_passed = assert(!is_empty(&stack), msg);

    msg = "should return true for empty linked stack";
    clear(&stack);
    is_all_passed = assert(is_empty(&stack), msg);

    return is_all_passed;
}

bool test_peek(void) {
    LinkedStack stack = test_data();
    elem_t      e;

    bool  is_all_passed;
    char *msg;

    msg           = "should not get top when NULL";
    is_all_passed = assert(!peek(NULL, &e), msg);

    msg           = "should get top";
    is_all_passed = assert(peek(&stack, &e), msg);
    is_all_passed = assert_eq(e, 0, msg);

    msg = "should not get top when empty";
    clear(&stack);
    is_all_passed = assert(!peek(&stack, &e), msg);

    return is_all_passed;
}

bool test_push(void) {
    LinkedStack stack = test_data();

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not push when NULL";
    is_all_passed = assert(!push(NULL, e), msg);

    msg           = "should push";
    is_all_passed = assert(push(&stack, e), msg);
    elem_t top;
    peek(&stack, &top);
    is_all_passed = assert_eq(top, e, msg);
    is_all_passed = assert_eq(stack.len, LEN + 1, msg);

    return is_all_passed;
}

bool test_pop(void) {
    LinkedStack stack = test_data();

    elem_t e;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not pop when NULL";
    is_all_passed = assert(!pop(NULL, &e), msg);

    msg           = "should pop";
    is_all_passed = assert(pop(&stack, &e), msg);
    is_all_passed = assert_eq(e, 0, msg);
    is_all_passed = assert_eq(stack.len, LEN - 1, msg);

    return is_all_passed;
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "linked_stack_create");
    run_test(test_init, prefix, "linked_stack_init");
    run_test(test_from_array, prefix, "linked_stack_from_array");
    run_test(test_to_array, prefix, "linked_stack_to_array");
    run_test(test_clear, prefix, "linked_stack_clear");
    run_test(test_is_empty, prefix, "linked_stack_is_empty");
    run_test(test_peek, prefix, "linked_stack_peek");
    run_test(test_push, prefix, "linked_stack_push");
    run_test(test_pop, prefix, "linked_stack_pop");

    return 0;
}

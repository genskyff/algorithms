#include "linked_stack.h"
#include "test_helper.h"
#include <stdlib.h>

#define LEN 6
#define TEST_DATA(...)                                                         \
    LinkedStack test_data() {                                                  \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    LinkedStack stack = create();

    char *msg;

    msg = "should get a empty linked stack";
    assert(stack.top == NULL, msg);
    assert_eq(stack.len, 0, msg);
}

void test_init(void) {
    LinkedStack stack    = init(LEN, 0, 1, 2, 3, 4, 5);
    elem_t      tmp[LEN] = {0, 1, 2, 3, 4, 5};
    elem_t     *arr      = to_array(&stack);

    char *msg;

    msg = "should get a initialized linked stack";
    assert(stack.top != NULL, msg);
    assert_eq(stack.len, LEN, msg);
    assert_arr_eq(arr, stack.len, tmp, LEN, msg);

    free(arr);
}

void test_from_array(void) {
    elem_t arr[LEN] = {0, 1, 2, 3, 4, 5};

    char *msg;

    msg               = "should get a linked stack from array";
    LinkedStack stack = from_array(arr, LEN);
    assert(stack.top != NULL, msg);
    assert_eq(stack.len, LEN, msg);

    msg = "should get a empty linked stack from NULL array";
    assert(from_array(NULL, LEN).top == NULL, msg);
}

void test_to_array(void) {
    LinkedStack stack    = test_data();
    elem_t      tmp[LEN] = {0, 1, 2, 3, 4, 5};

    char *msg;

    msg         = "should get an array from linked stack";
    elem_t *arr = to_array(&stack);
    assert(arr != NULL, msg);
    assert_arr_eq(arr, stack.len, tmp, LEN, msg);
    free(arr);

    msg               = "should get NULL from empty linked stack";
    LinkedStack empty = create();
    assert(to_array(&empty) == NULL, msg);
}

void test_clear(void) {
    LinkedStack stack = test_data();

    char *msg;

    msg = "should clear the linked stack";
    clear(&stack);
    assert(stack.top == NULL, msg);
    assert_eq(stack.len, 0, msg);
}

void test_is_empty(void) {
    LinkedStack stack = test_data();

    char *msg;

    msg = "should return false for non-empty linked stack";
    assert(!is_empty(&stack), msg);

    msg = "should return true for empty linked stack";
    clear(&stack);
    assert(is_empty(&stack), msg);
}

void test_peek(void) {
    LinkedStack stack = test_data();
    elem_t      e;

    char *msg;

    msg = "should not get top when NULL";
    assert(!peek(NULL, &e), msg);

    msg = "should get top";
    assert(peek(&stack, &e), msg);
    assert_eq(e, 0, msg);

    msg = "should not get top when empty";
    clear(&stack);
    assert(!peek(&stack, &e), msg);
}

void test_push(void) {
    LinkedStack stack = test_data();

    elem_t e = 10;

    char *msg;

    msg = "should not push when NULL";
    assert(!push(NULL, e), msg);

    msg = "should push";
    assert(push(&stack, e), msg);
    elem_t top;
    peek(&stack, &top);
    assert_eq(top, e, msg);
    assert_eq(stack.len, LEN + 1, msg);
}

void test_pop(void) {
    LinkedStack stack = test_data();

    elem_t e;

    char *msg;

    msg = "should not pop when NULL";
    assert(!pop(NULL, &e), msg);

    msg = "should pop";
    assert(pop(&stack, &e), msg);
    assert_eq(e, 0, msg);
    assert_eq(stack.len, LEN - 1, msg);
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

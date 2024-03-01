#include "array_stack.h"
#include "test_helper.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    ArrayStack test_data() {                                                   \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    ArrayStack stack = create();
    char      *msg   = "should get a empty ArrayStack";
    assert_eq(stack.len, 0, msg);
}

void test_init(void) {
    ArrayStack stack    = test_data();
    char      *msg      = "should get a initialized ArrayStack";
    elem_t     tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_eq(stack.len, LEN, msg);
    assert_arr_eq(stack.data, stack.len, tmp, LEN, msg);
}

void test_is_empty(void) {
    ArrayStack stack = test_data();
    char      *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(is_empty(&stack), msg);

    msg = "should be empty when len == 0";
    clear(&stack);
    assert(is_empty(&stack), msg);
}

void test_peek(void) {
    ArrayStack stack = test_data();
    elem_t     e;
    char      *msg;

    msg = "should get top";
    assert(peek(&stack, &e), msg);
    assert_eq(e, stack.data[stack.len - 1], msg);

    msg = "should not get top when empty";
    clear(&stack);
    assert_not(peek(&stack, NULL), msg);
}

void test_push(void) {
    ArrayStack stack = test_data();
    elem_t     e     = 999;
    char      *msg;

    msg = "should push";
    assert(push(&stack, e), msg);
    assert_eq(stack.len, LEN + 1, msg);
    assert_eq(stack.data[stack.len - 1], e, msg);

    msg       = "should not push when full";
    stack.len = MAXLEN;
    assert_not(push(&stack, e), msg);
    assert_eq(stack.len, MAXLEN, msg);
}

void test_pop(void) {
    ArrayStack stack = test_data();
    elem_t     e;
    elem_t     popped;
    char      *msg;

    msg    = "should pop";
    popped = stack.data[stack.len - 1];
    assert(pop(&stack, &e), msg);
    assert_eq(stack.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop when empty";
    clear(&stack);
    assert_not(pop(&stack, NULL), msg);
    assert_eq(stack.len, 0, msg);
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "array_stack_create");
    run_test(test_init, prefix, "array_stack_init");
    run_test(test_is_empty, prefix, "array_stack_is_empty");
    run_test(test_peek, prefix, "array_stack_peek");
    run_test(test_push, prefix, "array_stack_push");
    run_test(test_pop, prefix, "array_stack_pop");

    return 0;
}

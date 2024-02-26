#include "array_stack.h"
#include "test.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    ArrayStack test_data() {                                                   \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

bool test_create(void) {
    ArrayStack stack = create();
    bool       is_all_passed;
    char      *msg;

    msg           = "should get a empty ArrayStack";
    is_all_passed = assert_eq(stack.len, 0, msg);

    return is_all_passed;
}

bool test_init(void) {
    ArrayStack stack   = init(LEN, 0, 1, 2, 3, 4, 5);
    ArrayStack tmp = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should get a initialized ArrayStack";
    is_all_passed = assert_eq(stack.len, LEN, msg);
    is_all_passed = assert_arr_eq(stack.data, stack.len, tmp.data, tmp.len, msg);

    return is_all_passed;
}

bool test_is_empty(void) {
    ArrayStack stack = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should be empty when NULL";
    is_all_passed = assert(is_empty(NULL), msg);

    msg           = "should not be empty";
    is_all_passed = assert(!is_empty(&stack), msg);

    msg = "should be empty after clear";
    clear(&stack);
    is_all_passed = assert(is_empty(&stack), msg);

    return is_all_passed;
}

bool test_peek(void) {
    ArrayStack stack = test_data();

    elem_t e;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not get when NULL";
    is_all_passed = assert(!peek(NULL, NULL), msg);

    msg           = "should get top";
    is_all_passed = assert(peek(&stack, &e), msg);
    is_all_passed = assert_eq(e, stack.data[stack.len - 1], msg);

    msg = "should not get top when empty";
    clear(&stack);
    is_all_passed = assert(!peek(&stack, &e), msg);

    return is_all_passed;
}

bool test_push(void) {
    ArrayStack stack = test_data();

    elem_t e = 10;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not push when NULL";
    is_all_passed = assert(!push(NULL, e), msg);

    msg           = "should push";
    is_all_passed = assert(push(&stack, e), msg);
    is_all_passed = assert_eq(stack.len, LEN + 1, msg);
    is_all_passed = assert_eq(stack.data[stack.len - 1], e, msg);

    msg = "should not push when full";
    stack.len = MAXLEN;
    is_all_passed = assert(!push(&stack, e), msg);

    return is_all_passed;
}

bool test_pop(void) {
    ArrayStack stack = test_data();

    elem_t e;
    elem_t popped;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not pop when NULL";
    is_all_passed = assert(!pop(NULL, NULL), msg);

    msg           = "should pop";
    popped        = stack.data[stack.len - 1];
    is_all_passed = assert(pop(&stack, &e), msg);
    is_all_passed = assert_eq(stack.len, LEN - 1, msg);
    is_all_passed = assert_eq(e, popped, msg);

    msg = "should not pop when empty";
    clear(&stack);
    is_all_passed = assert(!pop(&stack, &e), msg);
    is_all_passed = assert_eq(stack.len, 0, msg);
    is_all_passed = assert_eq(e, popped, msg);

    return is_all_passed;
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

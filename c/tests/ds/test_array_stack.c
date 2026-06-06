#include "alg/ds/array_stack.h"
#include "helper.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    AlgArrayStack test_data() {                                                \
        return alg_array_stack_init(LEN, __VA_ARGS__);                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    AlgArrayStack stack = alg_array_stack_create();
    char         *msg;

    msg = "should get a empty array stack";
    assert_eq(stack.len, 0, msg);
}

void test_init(void) {
    AlgArrayStack stack = alg_array_stack_init(LEN, 0, 1, 2, 3, 4, 5);
    char         *msg;

    msg                 = "should get a initialized array stack";
    alg_elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_eq(stack.len, LEN, msg);
    assert_arr_eq(stack.data, stack.len, tmp, LEN, msg);
}

void test_clear(void) {
    AlgArrayStack stack = test_data();
    char         *msg;

    msg = "should clear";
    alg_array_stack_clear(&stack);
    assert_eq(stack.len, 0, msg);
}

void test_is_empty(void) {
    AlgArrayStack stack = test_data();
    char         *msg;

    msg = "should be empty when NULL";
    assert(alg_array_stack_is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(alg_array_stack_is_empty(&stack), msg);

    msg = "should be empty when len == 0";
    alg_array_stack_clear(&stack);
    assert(alg_array_stack_is_empty(&stack), msg);
}

void test_peek(void) {
    AlgArrayStack stack = test_data();
    alg_elem_t    e;
    char         *msg;

    msg = "should not get top when NULL";
    assert_not(alg_array_stack_peek(NULL, NULL), msg);

    msg = "should get top";
    assert(alg_array_stack_peek(&stack, &e), msg);
    assert_eq(e, stack.data[stack.len - 1], msg);

    msg = "should not get top when empty";
    alg_array_stack_clear(&stack);
    assert_not(alg_array_stack_peek(&stack, NULL), msg);
}

void test_push(void) {
    AlgArrayStack stack = test_data();
    alg_elem_t    e     = 999;
    char         *msg;

    msg = "should not push when NULL";
    assert_not(alg_array_stack_push(NULL, e), msg);

    msg = "should push";
    assert(alg_array_stack_push(&stack, e), msg);
    assert_eq(stack.len, LEN + 1, msg);
    assert_eq(stack.data[stack.len - 1], e, msg);

    msg       = "should not push when full";
    stack.len = ALG_MAX_LEN;
    assert_not(alg_array_stack_push(&stack, e), msg);
    assert_eq(stack.len, ALG_MAX_LEN, msg);
}

void test_pop(void) {
    AlgArrayStack stack = test_data();
    alg_elem_t    e;
    alg_elem_t    popped;
    char         *msg;

    msg = "should not pop when NULL";
    assert_not(alg_array_stack_pop(NULL, NULL), msg);

    msg    = "should pop";
    popped = stack.data[stack.len - 1];
    assert(alg_array_stack_pop(&stack, &e), msg);
    assert_eq(stack.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop when empty";
    alg_array_stack_clear(&stack);
    assert_not(alg_array_stack_pop(&stack, NULL), msg);
    assert_eq(stack.len, 0, msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "array_stack";

    run_test(test_create, mod, target, "create");
    run_test(test_init, mod, target, "init");
    run_test(test_is_empty, mod, target, "is_empty");
    run_test(test_peek, mod, target, "peek");
    run_test(test_push, mod, target, "push");
    run_test(test_pop, mod, target, "pop");

    return 0;
}

#include "alg/ds/linked_stack.h"
#include "support/helper.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    AlgLinkedStack test_data() {                                               \
        return alg_linked_stack_init(LEN, __VA_ARGS__);                        \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    AlgLinkedStack stack = alg_linked_stack_create();
    char          *msg;

    msg = "should get a empty linked stack";
    assert_null(stack.top, msg);
    assert_eq(stack.len, 0, msg);
}

void test_init(void) {
    AlgLinkedStack stack = alg_linked_stack_init(LEN, 0, 1, 2, 3, 4, 5);
    char          *msg;

    msg = "should get a initialized linked stack";
    assert_not_null(stack.top, msg);
    assert_eq(stack.len, LEN, msg);
    alg_elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_list_arr_eq(stack.top, ALG_BACKWARD, tmp, LEN, msg);
    assert_eq(stack.top->data, 5, msg);
}

void test_clear(void) {
    AlgLinkedStack stack = test_data();
    char          *msg;

    msg = "should clear";
    alg_linked_stack_clear(&stack);
    assert_null(stack.top, msg);
    assert_eq(stack.len, 0, msg);
}

void test_is_empty(void) {
    AlgLinkedStack stack = test_data();
    char          *msg;

    msg = "should be empty when NULL";
    assert(alg_linked_stack_is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(alg_linked_stack_is_empty(&stack), msg);

    msg = "should be empty when len == 0";
    alg_linked_stack_clear(&stack);
    assert(alg_linked_stack_is_empty(&stack), msg);
}

void test_peek(void) {
    AlgLinkedStack stack = test_data();
    alg_elem_t     e;
    char          *msg;

    msg = "should not get peek when NULL";
    assert_not(alg_linked_stack_peek(NULL, NULL), msg);

    msg = "should get peek";
    assert(alg_linked_stack_peek(&stack, &e), msg);
    assert_eq(e, stack.top->data, msg);

    msg = "should not get peek when empty";
    alg_linked_stack_clear(&stack);
    assert_not(alg_linked_stack_peek(&stack, NULL), msg);
}

void test_push(void) {
    AlgLinkedStack stack = test_data();
    alg_elem_t     e     = 999;
    char          *msg;

    msg = "should not push when NULL";
    assert_not(alg_linked_stack_push(NULL, e), msg);

    msg = "should push";
    assert(alg_linked_stack_push(&stack, e), msg);
    assert_eq(stack.len, LEN + 1, msg);
    assert_eq(stack.top->data, e, msg);

    msg = "should push when empty";
    alg_linked_stack_clear(&stack);
    assert(alg_linked_stack_push(&stack, e), msg);
    assert_eq(stack.len, 1, msg);
    assert_eq(stack.top->data, e, msg);
}

void test_pop(void) {
    AlgLinkedStack stack = test_data();
    alg_elem_t     e;
    alg_elem_t     popped;
    char          *msg;

    msg = "should not pop when NULL";
    assert_not(alg_linked_stack_pop(NULL, NULL), msg);

    msg    = "should pop";
    popped = stack.top->data;
    assert(alg_linked_stack_pop(&stack, &e), msg);
    assert_eq(stack.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop when empty";
    alg_linked_stack_clear(&stack);
    assert_not(alg_linked_stack_pop(&stack, NULL), msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "linked_stack";

    run_test(test_create, mod, target, "create");
    run_test(test_init, mod, target, "init");
    run_test(test_clear, mod, target, "clear");
    run_test(test_is_empty, mod, target, "is_empty");
    run_test(test_peek, mod, target, "peek");
    run_test(test_push, mod, target, "push");
    run_test(test_pop, mod, target, "pop");

    return 0;
}

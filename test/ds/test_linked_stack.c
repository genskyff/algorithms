#include "helper.h"
#include "linked_stack.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    LinkedStack test_data() {                                                  \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    LinkedStack stack = create();
    char       *msg   = "should get a empty linked stack";
    assert(stack.top == NULL, msg);
    assert_eq(stack.len, 0, msg);
}

void test_init(void) {
    LinkedStack stack = init(LEN, 0, 1, 2, 3, 4, 5);
    char       *msg   = "should get a initialized linked stack";
    assert(stack.top != NULL, msg);
    assert_eq(stack.len, LEN, msg);
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_list_arr_eq(stack.top, BACKWARD, tmp, LEN, msg);
    assert_eq(stack.top->data, 5, msg);
}

void test_clear(void) {
    LinkedStack stack = test_data();
    char       *msg   = "should clear";
    clear(&stack);
    assert(stack.top == NULL, msg);
    assert_eq(stack.len, 0, msg);
}

void test_is_empty(void) {
    LinkedStack stack = test_data();
    char       *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(is_empty(&stack), msg);

    msg = "should be empty when len == 0";
    clear(&stack);
    assert(is_empty(&stack), msg);
}

void test_peek(void) {
    LinkedStack stack = test_data();
    elem_t      e;
    char       *msg;

    msg = "should get peek";
    assert(peek(&stack, &e), msg);
    assert_eq(e, stack.top->data, msg);

    msg = "should not get peek when empty";
    clear(&stack);
    assert_not(peek(&stack, NULL), msg);
}

void test_push(void) {
    LinkedStack stack = test_data();
    elem_t      e     = 999;
    char       *msg;

    msg = "should push";
    assert(push(&stack, e), msg);
    assert_eq(stack.len, LEN + 1, msg);
    assert_eq(stack.top->data, e, msg);

    msg = "should push when empty";
    clear(&stack);
    assert(push(&stack, e), msg);
    assert_eq(stack.len, 1, msg);
    assert_eq(stack.top->data, e, msg);
}

void test_pop(void) {
    LinkedStack stack = test_data();
    elem_t      e;
    elem_t      popped;
    char       *msg;

    msg    = "should pop";
    popped = stack.top->data;
    assert(pop(&stack, &e), msg);
    assert_eq(stack.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop when empty";
    clear(&stack);
    assert_not(pop(&stack, NULL), msg);
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "linked_stack_create");
    run_test(test_init, prefix, "linked_stack_init");
    run_test(test_clear, prefix, "linked_stack_clear");
    run_test(test_is_empty, prefix, "linked_stack_is_empty");
    run_test(test_peek, prefix, "linked_stack_peek");
    run_test(test_push, prefix, "linked_stack_push");
    run_test(test_pop, prefix, "linked_stack_pop");

    return 0;
}

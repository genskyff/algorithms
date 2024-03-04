#include "array_queue.h"
#include "helper.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    ArrayQueue test_data() {                                                   \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    ArrayQueue queue = create();
    char      *msg;

    msg = "should get a empty array queue";
    assert_eq(queue.len, 0, msg);
}

void test_init(void) {
    ArrayQueue queue = init(LEN, 0, 1, 2, 3, 4, 5);
    char      *msg;

    msg             = "should get a initialized array queue";
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_eq(queue.len, LEN, msg);
    assert_arr_eq(queue.data, queue.len, tmp, LEN, msg);
}

void test_clear(void) {
    ArrayQueue queue = test_data();
    char      *msg;

    msg = "should clear";
    clear(&queue);
    assert_eq(queue.len, 0, msg);
    assert_eq(queue.front, 0, msg);
}

void test_is_empty(void) {
    ArrayQueue queue = test_data();
    char      *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(is_empty(&queue), msg);

    msg = "should be empty when len == 0";
    clear(&queue);
    assert(is_empty(&queue), msg);
}

void test_front(void) {
    ArrayQueue queue = test_data();
    elem_t     e;
    char      *msg;

    msg = "should not get front when NULL";
    assert_not(front(NULL, NULL), msg);

    msg = "should get front";
    assert(front(&queue, &e), msg);
    assert_eq(e, queue.data[0], msg);

    msg = "should not get front when empty";
    clear(&queue);
    assert_not(front(&queue, NULL), msg);
}

void test_back(void) {
    ArrayQueue queue = test_data();
    elem_t     e;
    char      *msg;

    msg = "should not get back when NULL";
    assert_not(back(NULL, NULL), msg);

    msg = "should get back";
    assert(back(&queue, &e), msg);
    assert_eq(e, queue.data[queue.len - 1], msg);

    msg = "should not get back when empty";
    clear(&queue);
    assert_not(back(&queue, NULL), msg);
}

void test_push_front(void) {
    ArrayQueue queue = create();
    elem_t     e     = 999;
    char      *msg;

    msg = "should not push_front when NULL";
    assert_not(push_front(NULL, 0), msg);

    msg = "should push_front";
    assert(push_front(&queue, e), msg);
    assert_eq(queue.len, 1, msg);
    assert(push_front(&queue, e), msg);
    assert_eq(queue.len, 2, msg);

    msg       = "should not push_front when full";
    queue.len = MAXLEN;
    assert_not(push_front(&queue, 0), msg);
    assert_eq(queue.len, MAXLEN, msg);
}

void test_push_back(void) {
    ArrayQueue queue = create();
    elem_t     e     = 999;
    char      *msg;

    msg = "should not push_back when NULL";
    assert_not(push_back(NULL, 0), msg);

    msg = "should push_back";
    assert(push_back(&queue, e), msg);
    assert_eq(queue.len, 1, msg);
    assert(push_back(&queue, e), msg);
    assert_eq(queue.len, 2, msg);

    msg       = "should not push_back when full";
    queue.len = MAXLEN;
    assert_not(push_back(&queue, 0), msg);
    assert_eq(queue.len, MAXLEN, msg);
}

void test_pop_front(void) {
    ArrayQueue queue = test_data();
    elem_t     e;
    elem_t     popped;
    char      *msg;

    msg = "should not pop_front when NULL";
    assert_not(pop_front(NULL, NULL), msg);

    msg    = "should pop_front";
    popped = queue.data[0];
    assert(pop_front(&queue, &e), msg);
    assert_eq(queue.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    clear(&queue);
    assert_not(pop_front(&queue, NULL), msg);
    assert_eq(queue.len, 0, msg);
}

void test_pop_back(void) {
    ArrayQueue queue = test_data();
    elem_t     e;
    elem_t     popped;
    char      *msg;

    msg = "should not pop_back when NULL";
    assert_not(pop_back(NULL, NULL), msg);

    msg    = "should pop_back";
    popped = queue.data[queue.len - 1];
    assert(pop_back(&queue, &e), msg);
    assert_eq(queue.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    clear(&queue);
    assert_not(pop_back(&queue, NULL), msg);
    assert_eq(queue.len, 0, msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "array_queue";

    run_test(test_create, mod, target, "create");
    run_test(test_init, mod, target, "init");
    run_test(test_is_empty, mod, target, "is_empty");
    run_test(test_front, mod, target, "front");
    run_test(test_back, mod, target, "back");
    run_test(test_push_front, mod, target, "push_front");
    run_test(test_push_back, mod, target, "push_back");
    run_test(test_pop_front, mod, target, "pop_front");
    run_test(test_pop_back, mod, target, "pop_back");

    return 0;
}

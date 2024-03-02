#include "helper.h"
#include "linked_queue.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    LinkedQueue test_data() {                                                  \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    LinkedQueue queue = create();
    char       *msg   = "should get a empty linked queue";
    assert(queue.front == NULL, msg);
    assert(queue.rear == NULL, msg);
    assert_eq(queue.len, 0, msg);
}

void test_init(void) {
    LinkedQueue queue = init(LEN, 0, 1, 2, 3, 4, 5);
    char       *msg   = "should get a initialized linked queue";
    assert(queue.front != NULL, msg);
    assert(queue.rear != NULL, msg);
    assert_eq(queue.len, LEN, msg);
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_list_arr_eq(queue.front, tmp, LEN, msg);
    assert_eq(queue.rear->data, 5, msg);
}

void test_clear(void) {
    LinkedQueue queue = test_data();
    char       *msg   = "should clear";
    clear(&queue);
    assert(queue.front == NULL, msg);
    assert(queue.rear == NULL, msg);
    assert_eq(queue.len, 0, msg);
}

void test_is_empty(void) {
    LinkedQueue queue = test_data();
    char       *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(is_empty(&queue), msg);

    msg = "should be empty when len == 0";
    clear(&queue);
    assert(is_empty(&queue), msg);
}

void test_front(void) {
    LinkedQueue queue = test_data();
    elem_t      e;
    char       *msg;

    msg = "should get front";
    assert(front(&queue, &e), msg);
    assert_eq(e, queue.front->data, msg);

    msg = "should not get front when empty";
    clear(&queue);
    assert_not(front(&queue, NULL), msg);
}

void test_back(void) {
    LinkedQueue queue = test_data();
    elem_t      e;
    char       *msg;

    msg = "should get back";
    assert(back(&queue, &e), msg);
    assert_eq(e, queue.rear->data, msg);

    msg = "should not get back when empty";
    clear(&queue);
    assert_not(back(&queue, NULL), msg);
}

void test_push_front(void) {
    LinkedQueue queue = test_data();
    elem_t      e     = 999;
    char       *msg;

    msg = "should push_front";
    assert(push_front(&queue, e), msg);
    assert_eq(queue.len, LEN + 1, msg);
    assert_eq(queue.front->data, e, msg);

    msg = "should push_front when empty";
    clear(&queue);
    assert(push_front(&queue, e), msg);
    assert_eq(queue.len, 1, msg);
    assert_eq(queue.front->data, e, msg);
    assert_eq(queue.rear->data, e, msg);
}

void test_push_back(void) {
    LinkedQueue queue = test_data();
    elem_t      e     = 999;
    char       *msg;

    msg = "should push_back";
    assert(push_back(&queue, e), msg);
    assert_eq(queue.len, LEN + 1, msg);
    assert_eq(queue.rear->data, e, msg);

    msg = "should push_back when empty";
    clear(&queue);
    assert(push_back(&queue, e), msg);
    assert_eq(queue.len, 1, msg);
    assert_eq(queue.front->data, e, msg);
    assert_eq(queue.rear->data, e, msg);
}

void test_pop_front(void) {
    LinkedQueue queue = test_data();
    elem_t      e;
    elem_t      popped;
    char       *msg;

    msg    = "should pop_front";
    popped = queue.front->data;
    assert(pop_front(&queue, &e), msg);
    assert_eq(queue.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    clear(&queue);
    assert_not(pop_front(&queue, NULL), msg);
}

void test_pop_back(void) {
    LinkedQueue queue = test_data();
    elem_t      e;
    elem_t      popped;
    char       *msg;

    msg    = "should pop_back";
    popped = queue.rear->data;
    assert(pop_back(&queue, &e), msg);
    assert_eq(queue.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    clear(&queue);
    assert_not(pop_back(&queue, NULL), msg);
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "linked_queue_create");
    run_test(test_init, prefix, "linked_queue_init");
    run_test(test_clear, prefix, "linked_queue_clear");
    run_test(test_is_empty, prefix, "linked_queue_is_empty");
    run_test(test_front, prefix, "linked_queue_front");
    run_test(test_back, prefix, "linked_queue_back");
    run_test(test_push_front, prefix, "linked_queue_push_front");
    run_test(test_push_back, prefix, "linked_queue_push_back");
    run_test(test_pop_front, prefix, "linked_queue_pop_front");
    run_test(test_pop_back, prefix, "linked_queue_pop_back");

    return 0;
}

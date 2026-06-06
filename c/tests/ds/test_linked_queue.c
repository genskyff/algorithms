#include "alg/ds/linked_queue.h"
#include "helper.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    AlgLinkedQueue test_data() {                                               \
        return alg_linked_queue_init(LEN, __VA_ARGS__);                        \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    AlgLinkedQueue queue = alg_linked_queue_create();
    char          *msg;

    msg = "should get a empty linked queue";
    assert_null(queue.front, msg);
    assert_null(queue.rear, msg);
    assert_eq(queue.len, 0, msg);
}

void test_init(void) {
    AlgLinkedQueue queue = alg_linked_queue_init(LEN, 0, 1, 2, 3, 4, 5);
    char          *msg;

    msg = "should get a initialized linked queue";
    assert_not_null(queue.front, msg);
    assert_not_null(queue.rear, msg);
    assert_eq(queue.len, LEN, msg);
    alg_elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_list_arr_eq(queue.front, ALG_FORWARD, tmp, LEN, msg);
    assert_eq(queue.rear->data, 5, msg);
}

void test_clear(void) {
    AlgLinkedQueue queue = test_data();
    char          *msg;

    msg = "should clear";
    alg_linked_queue_clear(&queue);
    assert_null(queue.front, msg);
    assert_null(queue.rear, msg);
    assert_eq(queue.len, 0, msg);
}

void test_is_empty(void) {
    AlgLinkedQueue queue = test_data();
    char          *msg;

    msg = "should be empty when NULL";
    assert(alg_linked_queue_is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(alg_linked_queue_is_empty(&queue), msg);

    msg = "should be empty when len == 0";
    alg_linked_queue_clear(&queue);
    assert(alg_linked_queue_is_empty(&queue), msg);
}

void test_front(void) {
    AlgLinkedQueue queue = test_data();
    alg_elem_t     e;
    char          *msg;

    msg = "should not get front when NULL";
    assert_not(alg_linked_queue_front(NULL, NULL), msg);

    msg = "should get front";
    assert(alg_linked_queue_front(&queue, &e), msg);
    assert_eq(e, queue.front->data, msg);

    msg = "should not get front when empty";
    alg_linked_queue_clear(&queue);
    assert_not(alg_linked_queue_front(&queue, NULL), msg);
}

void test_back(void) {
    AlgLinkedQueue queue = test_data();
    alg_elem_t     e;
    char          *msg;

    msg = "should not get back when NULL";
    assert_not(alg_linked_queue_back(NULL, NULL), msg);

    msg = "should get back";
    assert(alg_linked_queue_back(&queue, &e), msg);
    assert_eq(e, queue.rear->data, msg);

    msg = "should not get back when empty";
    alg_linked_queue_clear(&queue);
    assert_not(alg_linked_queue_back(&queue, NULL), msg);
}

void test_push_front(void) {
    AlgLinkedQueue queue = test_data();
    alg_elem_t     e     = 999;
    char          *msg;

    msg = "should not push_front when NULL";
    assert_not(alg_linked_queue_push_front(NULL, e), msg);

    msg = "should push_front";
    assert(alg_linked_queue_push_front(&queue, e), msg);
    assert_eq(queue.len, LEN + 1, msg);
    assert_eq(queue.front->data, e, msg);

    msg = "should push_front when empty";
    alg_linked_queue_clear(&queue);
    assert(alg_linked_queue_push_front(&queue, e), msg);
    assert_eq(queue.len, 1, msg);
    assert_eq(queue.front->data, e, msg);
    assert_eq(queue.rear->data, e, msg);
}

void test_push_back(void) {
    AlgLinkedQueue queue = test_data();
    alg_elem_t     e     = 999;
    char          *msg;

    msg = "should not push_back when NULL";
    assert_not(alg_linked_queue_push_back(NULL, e), msg);

    msg = "should push_back";
    assert(alg_linked_queue_push_back(&queue, e), msg);
    assert_eq(queue.len, LEN + 1, msg);
    assert_eq(queue.rear->data, e, msg);

    msg = "should push_back when empty";
    alg_linked_queue_clear(&queue);
    assert(alg_linked_queue_push_back(&queue, e), msg);
    assert_eq(queue.len, 1, msg);
    assert_eq(queue.front->data, e, msg);
    assert_eq(queue.rear->data, e, msg);
}

void test_pop_front(void) {
    AlgLinkedQueue queue = test_data();
    alg_elem_t     e;
    alg_elem_t     popped;
    char          *msg;

    msg = "should not pop_front when NULL";
    assert_not(alg_linked_queue_pop_front(NULL, NULL), msg);

    msg    = "should pop_front";
    popped = queue.front->data;
    assert(alg_linked_queue_pop_front(&queue, &e), msg);
    assert_eq(queue.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    alg_linked_queue_clear(&queue);
    assert_not(alg_linked_queue_pop_front(&queue, NULL), msg);
    assert_eq(queue.len, 0, msg);
}

void test_pop_back(void) {
    AlgLinkedQueue queue = test_data();
    alg_elem_t     e;
    alg_elem_t     popped;
    char          *msg;

    msg = "should not pop_back when NULL";
    assert_not(alg_linked_queue_pop_back(NULL, NULL), msg);

    msg    = "should pop_back";
    popped = queue.rear->data;
    assert(alg_linked_queue_pop_back(&queue, &e), msg);
    assert_eq(queue.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    alg_linked_queue_clear(&queue);
    assert_not(alg_linked_queue_pop_back(&queue, NULL), msg);
    assert_eq(queue.len, 0, msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "linked_queue";

    run_test(test_create, mod, target, "create");
    run_test(test_init, mod, target, "init");
    run_test(test_clear, mod, target, "clear");
    run_test(test_is_empty, mod, target, "is_empty");
    run_test(test_front, mod, target, "front");
    run_test(test_back, mod, target, "back");
    run_test(test_push_front, mod, target, "push_front");
    run_test(test_push_back, mod, target, "push_back");
    run_test(test_pop_front, mod, target, "pop_front");
    run_test(test_pop_back, mod, target, "pop_back");

    return 0;
}

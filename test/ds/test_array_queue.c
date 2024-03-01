#include "array_queue.h"
#include "test_helper.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    ArrayQueue test_data() {                                                   \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    ArrayQueue queue = create();

    char *msg;

    msg = "should get a empty ArrayQueue";
    assert_eq(queue.len, 0, msg);
}

void test_init(void) {
    ArrayQueue queue = init(LEN, 0, 1, 2, 3, 4, 5);
    ArrayQueue tmp   = test_data();

    char *msg;

    msg = "should get a initialized ArrayQueue";
    assert_eq(queue.len, LEN, msg);
    is_all_passed =
        assert_arr_eq(queue.data, queue.len, tmp.data, tmp.len, msg);
}

void test_is_empty(void) {
    ArrayQueue queue = test_data();

    char *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert(!is_empty(&queue), msg);

    msg = "should be empty after clear";
    clear(&queue);
    assert(is_empty(&queue), msg);
}

void test_front(void) {
    ArrayQueue queue = test_data();

    elem_t e;

    char *msg;

    msg = "should not get front when NULL";
    assert(!front(NULL, &e), msg);

    msg = "should get front";
    assert(front(&queue, &e), msg);
    assert_eq(e, 0, msg);

    msg = "should not get front when empty";
    clear(&queue);
    assert(!front(&queue, &e), msg);
}

void test_enque(void) {
    ArrayQueue queue = create();

    char *msg;

    msg = "should not enque when NULL";
    assert(!enque(NULL, 0), msg);

    msg = "should enque";
    assert(enque(&queue, 0), msg);
    assert_eq(queue.len, 1, msg);
    assert_eq(enque(&queue, 1), true, msg);
    assert_eq(queue.len, 2, msg);

    msg       = "should not enque when full";
    queue.len = MAXLEN;
    assert(!enque(&queue, 0), msg);
}

void test_deque(void) {
    ArrayQueue queue = test_data();

    elem_t e;

    char *msg;

    msg = "should not deque when NULL";
    assert(!deque(NULL, &e), msg);

    msg = "should deque";
    assert(deque(&queue, &e), msg);
    assert_eq(e, 0, msg);
    assert_eq(queue.len, LEN - 1, msg);

    msg = "should deque after enque";
    enque(&queue, 0);
    assert(deque(&queue, &e), msg);
    assert_eq(e, 1, msg);
    assert_eq(queue.len, LEN - 1, msg);

    msg = "should not deque when empty";
    clear(&queue);
    assert(!deque(&queue, &e), msg);
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "array_queue_create");
    run_test(test_init, prefix, "array_queue_init");
    run_test(test_is_empty, prefix, "array_queue_is_empty");
    run_test(test_front, prefix, "array_queue_front");
    run_test(test_enque, prefix, "array_queue_enque");
    run_test(test_deque, prefix, "array_queue_deque");

    return 0;
}

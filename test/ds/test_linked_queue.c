#include "linked_queue.h"
#include "test_helper.h"
#include <stdlib.h>

#define LEN 6
#define TEST_DATA(...)                                                         \
    LinkedQueue test_data() {                                                  \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

bool test_create(void) {
    LinkedQueue queue = create();
    bool        is_all_passed;
    char       *msg;

    return is_all_passed;
}

bool test_init(void) {
    LinkedQueue queue    = init(LEN, 0, 1, 2, 3, 4, 5);
    elem_t      tmp[LEN] = {0, 1, 2, 3, 4, 5};
    elem_t     *arr      = to_array(&queue);

    bool  is_all_passed;
    char *msg;

    free(arr);
    return is_all_passed;
}

bool test_from_array(void) {
    elem_t arr[LEN] = {0, 1, 2, 3, 4, 5};

    bool  is_all_passed;
    char *msg;

    msg           = "should get a linked queue from array";
    is_all_passed = assert(from_array(arr, LEN).front != NULL, msg);
    is_all_passed = assert_eq(from_array(arr, LEN).len, LEN, msg);

    msg           = "should get a empty linked queue from NULL array";
    is_all_passed = assert(from_array(NULL, LEN).front == NULL, msg);

    return is_all_passed;
}

bool test_to_array(void) {
    LinkedQueue queue    = test_data();
    elem_t      tmp[LEN] = {0, 1, 2, 3, 4, 5};

    bool  is_all_passed;
    char *msg;

    msg           = "should get a array from linked queue";
    elem_t *arr   = to_array(&queue);
    is_all_passed = assert(arr != NULL, msg);
    is_all_passed = assert_arr_eq(arr, queue.len, tmp, LEN, msg);
    free(arr);

    msg               = "should get a NULL array from empty linked queue";
    LinkedQueue empty = create();
    is_all_passed     = assert(to_array(&empty) == NULL, msg);

    return is_all_passed;
}

bool test_clear(void) {
    LinkedQueue queue = test_data();

    bool  is_all_passed;
    char *msg;

    msg = "should clear the linked queue";
    clear(&queue);
    is_all_passed = assert(queue.front == NULL, msg);
    is_all_passed = assert_eq(queue.len, 0, msg);

    return is_all_passed;
}

bool test_is_empty(void) {
    LinkedQueue queue = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should return false for non-empty linked queue";
    is_all_passed = assert(!is_empty(&queue), msg);

    msg = "should return true for empty linked queue";
    clear(&queue);
    is_all_passed = assert(is_empty(&queue), msg);

    return is_all_passed;
}

bool test_head(void) {
    LinkedQueue queue = test_data();

    elem_t e;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not get front when NULL";
    is_all_passed = assert(!front(NULL, &e), msg);

    msg           = "should get front";
    is_all_passed = assert(front(&queue, &e), msg);
    is_all_passed = assert_eq(e, 0, msg);

    return is_all_passed;
}

bool test_enque(void) {
    LinkedQueue queue = create();

    bool  is_all_passed;
    char *msg;

    msg           = "should not enque when NULL";
    is_all_passed = assert(!enque(NULL, 0), msg);

    msg           = "should enque";
    is_all_passed = assert(enque(&queue, 0), msg);
    is_all_passed = assert_eq(queue.len, 1, msg);
    elem_t first;
    front(&queue, &first);
    is_all_passed = assert_eq(first, 0, msg);

    return is_all_passed;
}

bool test_deque(void) {
    LinkedQueue queue = test_data();

    elem_t e;
    bool   is_all_passed;
    char  *msg;

    msg           = "should not deque when NULL";
    is_all_passed = assert(!deque(NULL, &e), msg);

    msg           = "should deque";
    is_all_passed = assert(deque(&queue, &e), msg);
    is_all_passed = assert_eq(e, 0, msg);
    is_all_passed = assert_eq(queue.len, LEN - 1, msg);

    return is_all_passed;
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "linked_queue_create");
    run_test(test_init, prefix, "linked_queue_init");
    run_test(test_from_array, prefix, "linked_queue_from_array");
    run_test(test_to_array, prefix, "linked_queue_to_array");
    run_test(test_clear, prefix, "linked_queue_clear");
    run_test(test_is_empty, prefix, "linked_queue_is_empty");
    run_test(test_head, prefix, "linked_queue_head");
    run_test(test_enque, prefix, "linked_queue_enque");
    run_test(test_deque, prefix, "linked_queue_deque");

    return 0;
}

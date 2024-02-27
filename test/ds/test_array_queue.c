#include "array_queue.h"
#include "test.h"

#define LEN 6
#define TEST_DATA(...)                                                         \
    ArrayQueue test_data() {                                                   \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

bool test_create(void) {
    ArrayQueue queue = create();
    bool       is_all_passed;
    char      *msg;

    msg           = "should get a empty ArrayQueue";
    is_all_passed = assert_eq(queue.len, 0, msg);

    return is_all_passed;
}

bool test_init(void) {
    ArrayQueue queue = init(LEN, 0, 1, 2, 3, 4, 5);
    ArrayQueue tmp   = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should get a initialized ArrayQueue";
    is_all_passed = assert_eq(queue.len, LEN, msg);
    is_all_passed =
        assert_arr_eq(queue.data, queue.len, tmp.data, tmp.len, msg);

    return is_all_passed;
}

bool test_is_empty(void) {
    ArrayQueue queue = test_data();

    bool  is_all_passed;
    char *msg;

    msg           = "should be empty when NULL";
    is_all_passed = assert(is_empty(NULL), msg);

    msg           = "should not be empty";
    is_all_passed = assert(!is_empty(&queue), msg);

    msg = "should be empty after clear";
    clear(&queue);
    is_all_passed = assert(is_empty(&queue), msg);

    return is_all_passed;
}

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "array_queue_create");
    run_test(test_init, prefix, "array_queue_init");
    run_test(test_is_empty, prefix, "array_queue_is_empty");
    return 0;
}

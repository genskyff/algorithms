#include "linked_queue.h"
#include "test.h"
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

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "linked_queue_create");
    run_test(test_init, prefix, "linked_queue_init");

    return 0;
}

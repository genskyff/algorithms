#include "helper.h"
#include "static_linked_list.h"
#include <stdint.h>

#define LEN 6
#define TEST_DATA(...)                                                         \
    SLinkedList test_data() {                                                  \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    SLinkedList list = create();
    char       *msg;

    msg = "should get a empty static linked list";
    assert_eq(list.space, 0, msg);
    assert_eq(list.head, SIZE_MAX, msg);
    assert_eq(list.tail, SIZE_MAX, msg);
    assert_eq(list.len, 0, msg);

    msg = "all nodes should be linked together";
    for (size_t i = 0; i < MAXLEN; i++) {
        assert_eq(list.space, i, msg);
        list.space = list.node[list.space].next;
    }
    assert_eq(list.space, SIZE_MAX, msg);
}

void test_init(void) {
    SLinkedList list = init(LEN, 0, 1, 2, 3, 4, 5);
    char       *msg;

    msg = "should get a initialized static linked list";
    assert_eq(list.space, LEN, msg);
    assert_eq(list.head, 0, msg);
    assert_eq(list.tail, LEN - 1, msg);
    assert_eq(list.len, LEN, msg);

    msg = "all nodes should be linked together";
    for (size_t i = 0, cur = list.head; cur != SIZE_MAX; i++) {
        assert_eq(list.node[cur].data, i, msg);
        assert_eq(list.node[cur].prev, cur == list.head ? SIZE_MAX : cur - 1,
                  msg);
        assert_eq(list.node[cur].next, cur == list.tail ? SIZE_MAX : cur + 1,
                  msg);
        cur = list.node[cur].next;
    }
}

int main(void) {
    char *mod    = "ds";
    char *target = "static_linked_list";

    run_test(test_create, mod, target, "test_create");
    run_test(test_init, mod, target, "test_init");

    return 0;
}

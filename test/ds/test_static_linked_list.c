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
    assert(list.head == SIZE_MAX, msg);
    assert(list.tail == SIZE_MAX, msg);
    assert_eq(list.len, 0, msg);

    msg = "all nodes should be linked together";
    for (size_t i = 0, cur = list.space; cur != SIZE_MAX; i++) {
        assert_eq(cur, i, msg);
        assert(list.node[list.space].prev == SIZE_MAX, msg);
        cur = list.node[cur].next;
    }
}

void test_init(void) {
    SLinkedList list     = init(LEN, 0, 1, 2, 3, 4, 5);
    elem_t      tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char       *msg;

    msg = "should get a initialized static linked list";
    assert_eq(list.space, LEN, msg);
    assert_eq(list.head, 0, msg);
    assert_eq(list.tail, LEN - 1, msg);
    assert_eq(list.len, LEN, msg);
    assert_arr_eq(tmp, LEN, to_array(&list), LEN, msg);

    msg = "all nodes should be linked together";
    for (size_t i = 0, cur = list.head; cur != SIZE_MAX; i++) {
        assert_eq(list.node[cur].data, i, msg);
        assert(list.node[cur].prev == (cur == list.head ? SIZE_MAX : cur - 1),
               msg);
        assert(list.node[cur].next == (cur == list.tail ? SIZE_MAX : cur + 1),
               msg);
        cur = list.node[cur].next;
    }
}

void test_to_array(void) {
    SLinkedList list = test_data();
    char       *msg;

    msg             = "should get an array";
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_arr_eq(to_array(&list), LEN, tmp, LEN, msg);

    msg = "should get NULL when empty";
    clear(&list);
    assert(to_array(&list) == NULL, msg);
}

void test_swap(void) {
    SLinkedList list     = test_data();
    elem_t      tmp[LEN] = {0, 1, 2, 3, 4, 5};
    char       *msg;

    msg = "should not swap when i == j";
    swap(&list, 1, 1);
    assert_arr_eq(tmp, LEN, to_array(&list), LEN, msg);

    msg = "should not swap when out of range";
    swap(&list, 0, LEN);
    assert_arr_eq(tmp, LEN, to_array(&list), LEN, msg);

    msg = "should swap head and tail";
    swap(&list, 0, list.len - 1);
    elem_t swap_endpoint[LEN] = {5, 1, 2, 3, 4, 0};
    assert_arr_eq(swap_endpoint, LEN, to_array(&list), LEN, msg);

    msg = "should swap when |i - j| == 1";
    swap(&list, 0, 1);
    elem_t swap_adjacent[LEN] = {1, 5, 2, 3, 4, 0};
    assert_arr_eq(swap_adjacent, LEN, to_array(&list), LEN, msg);
    assert_eq(list.node[list.tail].data, 0, msg);

    msg = "should swap when i == 0, j > 1";
    swap(&list, 0, 3);
    elem_t swap_head[LEN] = {3, 5, 2, 1, 4, 0};
    assert_arr_eq(swap_head, LEN, to_array(&list), LEN, msg);
    assert_eq(list.node[list.tail].data, 0, msg);

    msg = "should swap when i > 0, j == len - 1";
    swap(&list, 1, list.len - 1);
    elem_t swap_tail[LEN] = {3, 0, 2, 1, 4, 5};
    assert_arr_eq(swap_tail, LEN, to_array(&list), LEN, msg);
    assert_eq(list.node[list.tail].data, 5, msg);
}

void test_reverse(void) {
    SLinkedList list = test_data();
    char       *msg;

    msg = "should reverse";
    reverse(&list);
    elem_t rev[LEN] = {5, 4, 3, 2, 1, 0};
    assert_arr_eq(rev, LEN, to_array(&list), LEN, msg);
}

void test_clear(void) {
    SLinkedList list = test_data();
    char       *msg;

    msg = "should clear";
    clear(&list);
    assert_eq(list.space, 0, msg);
    assert(list.head == SIZE_MAX, msg);
    assert(list.tail == SIZE_MAX, msg);
    assert_eq(list.len, 0, msg);

    msg = "all nodes should be linked together";
    for (size_t i = 0, cur = list.space; cur != SIZE_MAX; i++) {
        assert_eq(cur, i, msg);
        assert(list.node[list.space].prev == SIZE_MAX, msg);
        cur = list.node[cur].next;
    }
}

void test_is_empty(void) {
    SLinkedList list = test_data();
    char       *msg;

    msg = "should be empty when NULL";
    assert(is_empty(NULL), msg);

    msg = "should not be empty";
    assert_not(is_empty(&list), msg);

    msg = "should be empty when len == 0";
    clear(&list);
    assert(is_empty(&list), msg);
}

void test_get(void) {
    SLinkedList list = test_data();
    elem_t      e;
    char       *msg;

    msg = "should not get when out of range";
    assert_not(get(&list, list.len, &e), msg);

    msg = "should get";
    assert(get(&list, list.len - 1, &e), msg);
    assert_eq(e, list.node[list.tail].data, msg);

    msg = "should not get when empty";
    clear(&list);
    assert_not(get(&list, 0, &e), msg);
}

void test_first(void) {
    SLinkedList list = test_data();
    elem_t      e;
    char       *msg;

    msg = "should get first";
    assert(first(&list, &e), msg);
    assert_eq(e, list.node[list.head].data, msg);

    msg = "should not get first when empty";
    clear(&list);
    assert_not(first(&list, &e), msg);
}

void test_last(void) {
    SLinkedList list = test_data();
    elem_t      e;
    char       *msg;

    msg = "should get last";
    assert(last(&list, &e), msg);
    assert_eq(e, list.node[list.tail].data, msg);

    msg = "should not get last when empty";
    clear(&list);
    assert_not(last(&list, &e), msg);
}

void test_set(void) {
    SLinkedList list = test_data();
    elem_t      e    = 999;
    char       *msg;

    msg = "should not set when out of range";
    assert_not(set(&list, list.len, e), msg);
    assert_not(find(&list, e, NULL), msg);

    msg = "should set";
    assert(set(&list, list.len - 1, e), msg);
    assert_eq(list.node[list.tail].data, e, msg);

    msg = "should not set when empty";
    clear(&list);
    assert_not(set(&list, 0, e), msg);
}

void test_find(void) {
    SLinkedList list = test_data();
    size_t      i;
    char       *msg;

    msg = "should find at head";
    assert(find(&list, 0, &i), msg);
    assert_eq(i, 0, msg);

    msg = "should find at tail";
    assert(find(&list, 5, &i), msg);
    assert_eq(i, 5, msg);

    msg = "should not find when no exist";
    i   = 0;
    assert_not(find(&list, 999, &i), msg);
    assert_eq(i, 0, msg);
}

void test_insert(void) {
    SLinkedList list = test_data();
    elem_t      e    = 999;
    char       *msg;

    msg = "should not insert when out of range";
    assert_not(insert(&list, list.len + 1, ++e), msg);
    assert_eq(list.len, LEN, msg);
    assert_not(find(&list, e, NULL), msg);

    msg = "should insert at head";
    assert(insert(&list, 0, ++e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.node[list.head].data, e, msg);

    msg = "should insert at middle";
    assert(insert(&list, list.len / 2, ++e), msg);
    assert_eq(list.len, LEN + 2, msg);
    elem_t mid;
    assert(get(&list, list.len / 2, &mid), msg);
    assert_eq(mid, e, msg);

    msg = "should insert at tail";
    assert(insert(&list, list.len, ++e), msg);
    assert_eq(list.len, LEN + 3, msg);
    assert_eq(list.node[list.tail].data, e, msg);

    msg      = "should not insert when full";
    list.len = MAXLEN;
    assert_not(insert(&list, 0, ++e), msg);
    assert_eq(list.len, MAXLEN, msg);

    msg = "should insert when empty";
    clear(&list);
    assert(insert(&list, 0, ++e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.node[list.head].data, e, msg);
    assert_eq(list.node[list.tail].data, e, msg);
}

void test_push_front(void) {
    SLinkedList list = test_data();
    elem_t      e    = 999;
    char       *msg;

    msg = "should push_front";
    assert(push_front(&list, e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.node[list.head].data, e, msg);

    msg      = "should not push_front when full";
    list.len = MAXLEN;
    assert_not(push_front(&list, e), msg);
    assert_eq(list.len, MAXLEN, msg);

    msg = "should push_front when empty";
    clear(&list);
    assert(push_front(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.node[list.head].data, e, msg);
    assert_eq(list.node[list.tail].data, e, msg);
}

void test_push_back(void) {
    SLinkedList list = test_data();
    elem_t      e    = 999;
    char       *msg;

    msg = "should push_back";
    assert(push_back(&list, e), msg);
    assert_eq(list.len, LEN + 1, msg);
    assert_eq(list.node[list.tail].data, e, msg);

    msg      = "should not push_back when full";
    list.len = MAXLEN;
    assert_not(push_back(&list, e), msg);
    assert_eq(list.len, MAXLEN, msg);

    msg = "should push_back when empty";
    clear(&list);
    assert(push_back(&list, e), msg);
    assert_eq(list.len, 1, msg);
    assert_eq(list.node[list.head].data, e, msg);
    assert_eq(list.node[list.tail].data, e, msg);
}

void test_del(void) {
    SLinkedList list = test_data();
    elem_t      e;
    elem_t      deleted;
    char       *msg;

    msg = "should not del when out of range";
    assert_not(del(&list, list.len, NULL), msg);
    assert_eq(list.len, LEN, msg);

    msg     = "should del at head";
    deleted = list.node[list.head].data;
    assert(del(&list, 0, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, deleted, msg);

    msg = "should del at middle";
    assert(get(&list, list.len / 2, &deleted), msg);
    assert(del(&list, list.len / 2, &e), msg);
    assert_eq(list.len, LEN - 2, msg);
    assert_eq(e, deleted, msg);

    msg     = "should del at tail";
    deleted = list.node[list.tail].data;
    assert(del(&list, list.len - 1, &e), msg);
    assert_eq(list.len, LEN - 3, msg);
    assert_eq(e, deleted, msg);

    msg = "should not del when empty";
    clear(&list);
    assert_not(del(&list, 0, NULL), msg);
    assert_eq(list.len, 0, msg);

    msg = "should delete when len == 1";
    assert(push_back(&list, 999), msg);
    assert(del(&list, 0, &e), msg);
    assert_eq(list.len, 0, msg);
    assert(list.head == SIZE_MAX, msg);
    assert(list.tail == SIZE_MAX, msg);
}

void test_pop_front(void) {
    SLinkedList list = test_data();
    elem_t      e;
    elem_t      popped;
    char       *msg;

    msg    = "should pop_front";
    popped = list.node[list.head].data;
    assert(pop_front(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_front when empty";
    clear(&list);
    assert_not(pop_front(&list, NULL), msg);
    assert_eq(list.len, 0, msg);
}

void test_pop_back(void) {
    SLinkedList list = test_data();
    elem_t      e;
    elem_t      popped;
    char       *msg;

    msg    = "should pop_back";
    popped = list.node[list.tail].data;
    assert(pop_back(&list, &e), msg);
    assert_eq(list.len, LEN - 1, msg);
    assert_eq(e, popped, msg);

    msg = "should not pop_back when empty";
    clear(&list);
    assert_not(pop_back(&list, NULL), msg);
    assert_eq(list.len, 0, msg);
}

int main(void) {
    char *mod    = "ds";
    char *target = "static_linked_list";

    run_test(test_create, mod, target, "test_create");
    run_test(test_init, mod, target, "test_init");
    run_test(test_to_array, mod, target, "test_to_array");
    run_test(test_swap, mod, target, "test_swap");
    run_test(test_reverse, mod, target, "test_reverse");
    run_test(test_clear, mod, target, "test_clear");
    run_test(test_is_empty, mod, target, "test_is_empty");
    run_test(test_get, mod, target, "test_get");
    run_test(test_first, mod, target, "test_first");
    run_test(test_last, mod, target, "test_last");
    run_test(test_set, mod, target, "test_set");
    run_test(test_find, mod, target, "test_find");
    run_test(test_insert, mod, target, "test_insert");
    run_test(test_push_front, mod, target, "test_push_front");
    run_test(test_push_back, mod, target, "test_push_back");
    run_test(test_del, mod, target, "test_del");
    run_test(test_pop_front, mod, target, "test_pop_front");
    run_test(test_pop_back, mod, target, "test_pop_back");

    return 0;
}

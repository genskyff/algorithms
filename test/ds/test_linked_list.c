#include "linked_list.h"
#include "test_helper.h"
#include <stdlib.h>

#define LEN 6
#define TEST_DATA(...)                                                         \
    LinkedList test_data() {                                                   \
        return init(LEN, __VA_ARGS__);                                         \
    }
TEST_DATA(0, 1, 2, 3, 4, 5)

void test_create(void) {
    LinkedList list = create();
    char      *msg  = "should get a empty linked list";
    assert(list.head == NULL, msg);
    assert(list.tail == NULL, msg);
    assert_eq(list.len, 0, msg);
}

void test_init(void) {
    LinkedList list = init(LEN, 0, 1, 2, 3, 4, 5);
    char      *msg  = "should get a initialized linked list";
    assert(list.head != NULL, msg);
    assert_eq(list.len, LEN, msg);
    elem_t tmp[LEN] = {0, 1, 2, 3, 4, 5};
    assert_list_arr_eq(list.head, tmp, LEN, msg);
}

// void test_swap(void) {
//     LinkedList list = test_data();

//     // expect array's name like swap_<i>_<j>
//     elem_t swap_0_5[] = {5, 1, 2, 3, 4, 0};
//     elem_t swap_0_1[] = {1, 5, 2, 3, 4, 0};

//     char *msg;

//     msg = "should swap(0, 5)";
//     swap(&list, 0, 5);
//     elem_t *tmp = to_array(&list);
//     assert_arr_eq(tmp, list.len, swap_0_5, LEN, msg);
//     free(tmp);

//     msg = "should swap(0, 1)";
//     swap(&list, 0, 1);
//     tmp = to_array(&list);
//     assert_arr_eq(tmp, list.len, swap_0_1, LEN, msg);
//     free(tmp);

//     msg = "should not swap(3, 3)";
//     swap(&list, 3, 3);
//     tmp = to_array(&list);
//     assert_arr_eq(tmp, list.len, swap_0_1, LEN, msg);
//     free(tmp);

//     msg = "should not swap when out of range";
//     swap(&list, 0, LEN);
//     tmp = to_array(&list);
//     assert_arr_eq(tmp, list.len, swap_0_1, LEN, msg);
//     free(tmp);
// }

// void test_reverse(void) {
//     LinkedList list  = test_data();
//     elem_t     rev[] = {5, 4, 3, 2, 1, 0};

//     char *msg;

//     msg = "should reverse";
//     reverse(&list);
//     elem_t *tmp = to_array(&list);
//     assert_arr_eq(tmp, list.len, tmp, LEN, msg);
//     free(tmp);
// }

// void test_clear(void) {
//     LinkedList list = test_data();

//     char *msg;

//     msg = "should clear the linked list";
//     clear(&list);
//     assert(list.head == NULL, msg);
//     assert_eq(list.len, 0, msg);
// }

// void test_is_empty(void) {
//     LinkedList list = test_data();

//     char *msg;

//     msg = "should return false for non-empty linked list";
//     assert(!is_empty(&list), msg);

//     msg = "should return true for empty linked list";
//     clear(&list);
//     assert(is_empty(&list), msg);
// }

// void test_get(void) {
//     LinkedList list = test_data();
//     elem_t     e;

//     char *msg;

//     msg = "should not get when NULL";
//     assert(!get(NULL, 0, &e), msg);

//     msg = "should get";
//     assert(get(&list, 0, &e), msg);
//     assert_eq(e, 0, msg);

//     msg = "should not get when out of range";
//     assert(!get(&list, list.len, &e), msg);
// }

// void test_set(void) {
//     LinkedList list = test_data();

//     elem_t e = 10;

//     char *msg;

//     msg = "should not set when NULL";
//     assert(!set(NULL, 0, e), msg);

//     msg = "should set";
//     assert(set(&list, 0, e), msg);
//     assert_eq(list.head->data, 10, msg);

//     msg = "should not set when out of range";
//     assert(!set(&list, list.len, e), msg);
// }

// void test_find(void) {
//     LinkedList list = test_data();

//     size_t i;

//     char *msg;

//     msg = "should not find when NULL";
//     assert(!find(NULL, 0, NULL), msg);

//     msg = "should find";
//     assert(find(&list, 5, &i), msg);
//     assert_eq(i, 5, msg);

//     msg = "should not";
//     assert(!find(&list, 6, &i), msg);
// }

// void test_insert(void) {
//     LinkedList list = test_data();

//     bool true;
//     char *msg;

//     msg = "should insert";
//     assert(insert(&list, 0, 10), msg);
//     assert_eq(list.head->data, 10, msg);
//     assert_eq(list.len, LEN + 1, msg);

//     msg = "should not insert when out of range";
//     assert(!insert(&list, list.len + 1, 10), msg);
// }

// void test_push(void) {
//     LinkedList list = test_data();

//     elem_t e = 10;

//     char *msg;

//     msg = "should not push when NULL";
//     assert(!push(NULL, e), msg);

//     msg = "should push";
//     assert(push(&list, e), msg);
//     elem_t last;
//     get(&list, list.len - 1, &last);
//     assert_eq(last, e, msg);
//     assert_eq(list.len, LEN + 1, msg);
// }

// void test_del(void) {
//     LinkedList list = test_data();

//     elem_t e;

//     char *msg;

//     msg = "should not del when NULL";
//     assert(!del(NULL, 0, &e), msg);

//     msg = "should del";
//     assert(del(&list, 0, &e), msg);
//     assert_eq(e, 0, msg);
//     assert_eq(list.head->data, 1, msg);
//     assert_eq(list.len, LEN - 1, msg);

//     msg = "should not del when out of range";
//     assert(!del(&list, list.len, &e), msg);
// }

// void test_pop(void) {
//     LinkedList list = test_data();

//     elem_t e;

//     char *msg;

//     msg = "should not pop when NULL";
//     assert(!pop(NULL, &e), msg);

//     msg = "should pop";
//     assert(pop(&list, &e), msg);
//     assert_eq(e, 5, msg);
//     assert_eq(list.len, LEN - 1, msg);
// }

int main(void) {
    char *prefix = "ds";
    run_test(test_create, prefix, "linked_list_create");
    run_test(test_init, prefix, "linked_list_init");
    // run_test(test_from_array, prefix, "linked_list_from_array");
    // run_test(test_to_array, prefix, "linked_list_to_array");
    // run_test(test_length, prefix, "linked_list_length");
    // run_test(test_swap, prefix, "linked_list_swap");
    // run_test(test_reverse, prefix, "linked_list_reverse");
    // run_test(test_clear, prefix, "linked_list_clear");
    // run_test(test_is_empty, prefix, "linked_list_is_empty");
    // run_test(test_get, prefix, "linked_list_get");
    // run_test(test_set, prefix, "linked_list_set");
    // run_test(test_find, prefix, "linked_list_find");
    // run_test(test_insert, prefix, "linked_list_insert");
    // run_test(test_push, prefix, "linked_list_push");
    // run_test(test_del, prefix, "linked_list_del");
    // run_test(test_pop, prefix, "linked_list_pop");

    return 0;
}

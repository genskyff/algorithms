#include "test.h"
#include "type.h"
#include "utils.h"
#include <string.h>

#define LEN 6
elem_t ARR[LEN] = {0, 1, 2, 3, 4, 5};

bool test_swap(void) {
    elem_t tmp[LEN];

    // expect array's name like swap_<i>_<j>
    elem_t swap_0_5[] = {5, 1, 2, 3, 4, 0};
    elem_t swap_4_1[] = {0, 4, 2, 3, 1, 5};

    bool  is_all_passed;
    char *msg;

    msg = "should swap(0, 5)";
    _copy(tmp, LEN, ARR, LEN);
    _swap(tmp, 0, 5);
    is_all_passed = assert_arr_eq(tmp, LEN, swap_0_5, LEN, msg);

    msg = "should swap(4, 1)";
    _copy(tmp, LEN, ARR, LEN);
    _swap(tmp, 4, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, swap_4_1, LEN, msg);

    msg = "should not swap(3, 3)";
    _copy(tmp, LEN, ARR, LEN);
    _swap(tmp, 3, 3);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

bool test_reverse(void) {
    elem_t tmp[LEN];

    // expect array's name like reverse_<len>
    elem_t reverse_len[] = {5, 4, 3, 2, 1, 0};
    elem_t reverse_2[]   = {1, 0};
    elem_t reverse_1[]   = {0};

    bool  is_all_passed;
    char *msg;

    msg = "should reverse [0..len]";
    _copy(tmp, LEN, ARR, LEN);
    _reverse(tmp, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, reverse_len, LEN, msg);

    msg = "should reverse [0..2]";
    _copy(tmp, 2, ARR, 2);
    _reverse(tmp, 2);
    is_all_passed = assert_arr_eq(tmp, 2, reverse_2, 2, msg);

    msg = "should not reverse [0..1]";
    _copy(tmp, 1, ARR, 1);
    _reverse(tmp, 1);
    is_all_passed = assert_arr_eq(tmp, 1, reverse_1, 1, msg);

    return is_all_passed;
}

bool test_reverse_slice(void) {
    elem_t tmp[LEN];

    // expect array's name like reverse_<start>_<end>
    elem_t reverse_1_5[]    = {0, 4, 3, 2, 1, 5};
    elem_t reverse_1_over[] = {0, 5, 4, 3, 2, 1};

    bool  is_all_passed;
    char *msg;

    msg = "should reverse [1..5]";
    _copy(tmp, LEN, ARR, LEN);
    _reverse_slice(tmp, LEN, 1, 5);
    is_all_passed = assert_arr_eq(tmp, LEN, reverse_1_5, LEN, msg);

    msg = "should reverse [1..len+1]";
    _copy(tmp, LEN, ARR, LEN);
    _reverse_slice(tmp, LEN, 1, LEN + 1);
    is_all_passed = assert_arr_eq(tmp, LEN, reverse_1_over, LEN, msg);

    msg = "should not reverse [2..3]";
    _copy(tmp, LEN, ARR, LEN);
    _reverse_slice(tmp, LEN, 2, 3);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should not reverse [3..2]";
    _copy(tmp, LEN, ARR, LEN);
    _reverse_slice(tmp, LEN, 3, 2);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

bool test_find(void) {
    size_t i;
    bool   is_all_passed;
    char  *msg;

    // expect result's name like find_<e>
    msg           = "should find [0]";
    bool find_0   = _find(ARR, LEN, 0, &i);
    is_all_passed = assert(find_0 && i == 0, msg);

    msg            = "should find tail";
    bool find_tail = _find(ARR, LEN, LEN - 1, &i);
    is_all_passed  = assert(find_tail && i == 5, msg);

    msg           = "should not find out of range";
    bool find_100 = _find(ARR, LEN, 100, &i);
    is_all_passed = assert(!find_100 && i == 5, msg);

    return is_all_passed;
}

bool test_find_slice(void) {
    size_t i;
    bool   is_all_passed;
    char  *msg;

    // expect result's name like find_<start>_<end>_<e>
    msg               = "should find in [0..len]";
    bool find_0_len_0 = _find_slice(ARR, LEN, 0, LEN, 0, &i);
    is_all_passed     = assert(find_0_len_0 && i == 0, msg);

    msg             = "should find in [1..5]";
    bool find_1_5_3 = _find_slice(ARR, LEN, 1, 5, 3, &i);
    is_all_passed   = assert(find_1_5_3 && i == 3, msg);

    msg             = "should not find in [2..3]";
    bool find_2_3_1 = _find_slice(ARR, LEN, 2, 3, 1, &i);
    is_all_passed   = assert(!find_2_3_1, msg);

    return is_all_passed;
}

bool test_copy(void) {
    elem_t tmp[LEN];
    elem_t tmp_less[LEN - 1];
    elem_t tmp_over[LEN + 1];
    memset(tmp_over, 0, (LEN + 1) * sizeof(elem_t));

    // expect array's name like copy_<len>
    elem_t copy_over[LEN + 1];
    _copy(copy_over, LEN + 1, ARR, LEN);
    copy_over[LEN] = 0;

    bool  is_all_passed;
    char *msg;

    // copy_len
    msg = "should copy [0..len]";
    _copy(tmp, LEN, ARR, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // copy self in place, no change
    msg = "should copy [0..len] in place";
    _copy(tmp, LEN, tmp, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, tmp, LEN, msg);

    // copy_less, tmp_less same as ARR[0..LEN-1]
    msg = "should copy [0..len] to [0..len-1]";
    _copy(tmp_less, LEN - 1, ARR, LEN);
    is_all_passed = assert_arr_eq(tmp_less, LEN - 1, ARR, LEN - 1, msg);

    // copy_over, tmp_over[0..LEN] same as ARR
    msg = "should copy [0..len+1] to [0..len]";
    _copy(tmp_over, LEN + 1, ARR, LEN);
    is_all_passed = assert_arr_eq(tmp_over, LEN + 1, copy_over, LEN + 1, msg);

    return is_all_passed;
}

bool test_copy_slice(void) {
    elem_t tmp[LEN];

    // expect array's name like copy_<d_len>_<s_len>
    elem_t copy_lhalf_rhalf[] = {3, 4, 5, 0, 0, 0};
    elem_t copy_overlap[]     = {1, 2, 3, 4, 5, 5};
    elem_t copy_less_over[]   = {0, 1, 2, 0, 0, 0};
    elem_t copy_over_less[]   = {0, 1, 2, 0, 0, 0};

    bool  is_all_passed;
    char *msg;

    // copy_lhalf_rhalf
    msg = "should copy [0..len/2] to [len/2..len]";
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN / 2, ARR, LEN, LEN / 2, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, copy_lhalf_rhalf, LEN, msg);

    // copy_overlap in place
    msg = "should copy [1..len] to [0..len-1] in place";
    _copy(tmp, LEN, ARR, LEN);
    _copy_slice(tmp, LEN, 0, LEN - 1, tmp, LEN, 1, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, copy_overlap, LEN, msg);

    // copy_less_over
    msg = "should copy [0..len] to [0..len/2]";
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN / 2, ARR, LEN, 0, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, copy_less_over, LEN, msg);

    // copy_over_less
    msg = "should copy [0..len/2] to [0..len]";
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN, ARR, LEN, 0, LEN / 2);
    is_all_passed = assert_arr_eq(tmp, LEN, copy_over_less, LEN, msg);

    // copy_len_len, same as ARR
    msg = "should copy [0..len] to [0..len]";
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN, ARR, LEN, 0, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // copy_len_over, same as ARR
    msg = "should copy [0..len+1] to [0..len]";
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN, ARR, LEN, 0, LEN + 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // copy_over_len, same as ARR
    msg = "should copy [0..len] to [0..len+1]";
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN + 1, ARR, LEN, 0, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

bool test_move_left(void) {
    elem_t tmp[LEN];

    // expect array's name like move_<n>
    elem_t move_2[] = {2, 3, 4, 5, 4, 5};

    bool  is_all_passed;
    char *msg;

    // move_2
    msg = "should move 2 steps left";
    _copy(tmp, LEN, ARR, LEN);
    _move_left(tmp, LEN, 2);
    is_all_passed = assert_arr_eq(tmp, LEN, move_2, LEN, msg);

    // move_len, no change
    msg = "should not move left when n == len";
    _copy(tmp, LEN, ARR, LEN);
    _move_left(tmp, LEN, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // move_over, no change
    msg = "should not move left when n > len";
    _copy(tmp, LEN, ARR, LEN);
    _move_left(tmp, LEN, LEN + 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

bool test_move_left_slice(void) {
    elem_t tmp[LEN];

    // expect array's name like move_<start>_<end>_<n>
    elem_t move_0_len_2[]  = {2, 3, 4, 5, 4, 5};
    elem_t move_1_5_1[]    = {0, 2, 3, 4, 4, 5};
    elem_t move_1_over_1[] = {0, 2, 3, 4, 5, 5};

    bool  is_all_passed;
    char *msg;

    // move_0_len_2
    msg = "should move 2 steps left in [0..len]";
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 0, LEN, 2);
    is_all_passed = assert_arr_eq(tmp, LEN, move_0_len_2, LEN, msg);

    // move_1_5_1
    msg = "should move 1 step left in [1..5]";
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 1, 5, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, move_1_5_1, LEN, msg);

    // move_1_over_1
    msg = "should move 1 step left in [1..len+1]";
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 1, LEN + 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, move_1_over_1, LEN, msg);

    // move_1_5_over, no change
    msg = "should not move left slice when n > len";
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 1, 5, LEN + 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // move_3_1_1, no change
    msg = "should not move left slice when start >= end";
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 3, 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

bool test_move_right(void) {
    elem_t tmp[LEN];

    // expect array's name like move_<n>
    elem_t move_2[] = {0, 1, 0, 1, 2, 3};

    bool  is_all_passed;
    char *msg;

    // move_2
    msg = "should move 2 steps right";
    _copy(tmp, LEN, ARR, LEN);
    _move_right(tmp, LEN, 2);
    is_all_passed = assert_arr_eq(tmp, LEN, move_2, LEN, msg);

    // move_len, no change
    msg = "should not move right when n == len";
    _copy(tmp, LEN, ARR, LEN);
    _move_right(tmp, LEN, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // move_over, no change
    msg = "should not move right when n > len";
    _copy(tmp, LEN, ARR, LEN);
    _move_right(tmp, LEN, LEN + 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

bool test_move_right_slice(void) {
    elem_t tmp[LEN];

    // expect array's name like move_<start>_<end>_<n>
    elem_t move_0_len_2[]  = {0, 1, 0, 1, 2, 3};
    elem_t move_1_5_1[]    = {0, 1, 1, 2, 3, 5};
    elem_t move_1_over_1[] = {0, 1, 1, 2, 3, 4};

    bool  is_all_passed;
    char *msg;

    // move_0_len_2
    msg = "should move 2 steps right in [0..len]";
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 0, LEN, 2);
    is_all_passed = assert_arr_eq(tmp, LEN, move_0_len_2, LEN, msg);

    // move_1_5_1
    msg = "should move 1 step right in [1..5]";
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 1, 5, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, move_1_5_1, LEN, msg);

    // move_1_over_1
    msg = "should move 1 step right in [1..len+1]";
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 1, LEN + 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, move_1_over_1, LEN, msg);

    // move_1_5_over, no change
    msg = "should not move right slice when n > len";
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 1, 5, LEN + 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // move_3_1_1, no change
    msg = "should not move right slice when start >= end";
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 3, 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

bool test_rotate_left(void) {
    elem_t tmp[LEN];

    // expect array's name like rotate_<n>
    elem_t rotate_2[]      = {2, 3, 4, 5, 0, 1};
    elem_t rotate_over_3[] = {3, 4, 5, 0, 1, 2};

    bool  is_all_passed;
    char *msg;

    // rotate_2
    msg = "should rotate 2 steps left";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, 2);
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_2, LEN, msg);

    // rotate_over_3
    msg = "should rotate over 3 steps left";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, LEN + 3);
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_over_3, LEN, msg);

    // rotate_0, no change
    msg = "should not rotate left when n == 0";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, 0);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // rotate_len, no change
    msg = "should not rotate left when n == len";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // rotate_2*len, no change
    msg = "should not rotate left when n == 2 * len";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, 2 * LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

bool test_rotate_left_slice(void) {
    elem_t tmp[LEN];

    // expect array's name like rotate_<start>_<end>_<n>
    elem_t rotate_0_len_2[]  = {2, 3, 4, 5, 0, 1};
    elem_t rotate_1_5_1[]    = {0, 2, 3, 4, 1, 5};
    elem_t rotate_1_over_1[] = {0, 2, 3, 4, 5, 1};

    bool  is_all_passed;
    char *msg;

    // rotate_0_len_2
    msg = "should rotate 2 steps left in [0..len]";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 0, LEN, 2);
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_0_len_2, LEN, msg);

    // rotate_1_5_1
    msg = "should rotate 1 step left in [1..5]";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 1, 5, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_1_5_1, LEN, msg);

    // rotate_1_over_1
    msg = "should rotate 1 step left in [1..len+1]";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 1, LEN + 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_1_over_1, LEN, msg);

    // rotate_1_5_2*len, no change
    msg = "should not rotate left slice when n == 2 * len";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 1, 5, 8);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // rotate_3_1_1, no change
    msg = "should not rotate left slice when start >= end";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 3, 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

bool test_rotate_right(void) {
    elem_t tmp[LEN];

    // expect array's name like rotate_<n>
    elem_t rotate_2[]      = {4, 5, 0, 1, 2, 3};
    elem_t rotate_over_3[] = {3, 4, 5, 0, 1, 2};

    bool  is_all_passed;
    char *msg;

    // rotate_2
    msg = "should rotate 2 steps right";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, 2);
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_2, LEN, msg);

    // rotate_over_3
    msg = "should rotate over 3 steps right";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, LEN + 3);
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_over_3, LEN, msg);

    // rotate_0, no change
    msg = "should not rotate right when n == 0";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, 0);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // rotate_len, no change
    msg = "should not rotate right when n == len";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // rotate_2*len, no change
    msg = "should not rotate right when n == 2 * len";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, 2 * LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

bool test_rotate_right_slice(void) {
    elem_t tmp[LEN];

    // expect array's name like rotate_<start>_<end>_<n>
    elem_t rotate_0_len_2[]  = {4, 5, 0, 1, 2, 3};
    elem_t rotate_1_5_1[]    = {0, 4, 1, 2, 3, 5};
    elem_t rotate_1_over_1[] = {0, 5, 1, 2, 3, 4};

    bool  is_all_passed;
    char *msg;

    // rotate_0_len_2
    msg = "should rotate 2 steps right in [0..len]";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 0, LEN, 2);
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_0_len_2, LEN, msg);

    // rotate_1_5_1
    msg = "should rotate 1 step right in [1..5]";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 1, 5, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_1_5_1, LEN, msg);

    // rotate_1_over_1
    msg = "should rotate 1 step right in [1..len+1]";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 1, LEN + 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_1_over_1, LEN, msg);

    // rotate_1_5_2*len, no change
    msg = "should not rotate right slice when n == 2 * len";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 1, 5, 8);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    // rotate_3_1_1, no change
    msg = "should not rotate right slice when start >= end";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 3, 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

int main(void) {
    char *prefix = "utils";
    run_test(test_swap, prefix, "swap");
    run_test(test_reverse, prefix, "reverse");
    run_test(test_reverse_slice, prefix, "reverse_slice");
    run_test(test_find, prefix, "find");
    run_test(test_find_slice, prefix, "find_slice");
    run_test(test_copy, prefix, "copy");
    run_test(test_copy_slice, prefix, "copy_slice");
    run_test(test_move_left, prefix, "move_left");
    run_test(test_move_left_slice, prefix, "move_left_slice");
    run_test(test_move_right, prefix, "move_right");
    run_test(test_move_right_slice, prefix, "move_right_slice");
    run_test(test_rotate_left, prefix, "rotate_left");
    run_test(test_rotate_left_slice, prefix, "rotate_left_slice");
    run_test(test_rotate_right, prefix, "rotate_right");
    run_test(test_rotate_right_slice, prefix, "rotate_right_slice");

    return 0;
}

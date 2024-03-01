#include "test.h"
#include "type.h"
#include "utils.h"
#include <stdlib.h>
#include <time.h>

#define LEN 6
elem_t ARR[LEN] = {0, 1, 2, 3, 4, 5};

bool test_swap(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should not swap when i == j";
    _copy(tmp, LEN, ARR, LEN);
    _swap(tmp, LEN / 2, LEN / 2);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should swap";
    _copy(tmp, LEN, ARR, LEN);
    _swap(tmp, 0, LEN - 1);
    elem_t swap_side[LEN] = {5, 1, 2, 3, 4, 0};
    is_all_passed         = assert_arr_eq(tmp, LEN, swap_side, LEN, msg);

    return is_all_passed;
}

bool test_shuffle(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    srand(time(NULL));

    msg = "should not shuffle when len < 2";
    _copy(tmp, LEN, ARR, LEN);
    _shuffle(tmp, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should shuffle";
    _copy(tmp, LEN, ARR, LEN);
    for (size_t i = 0; i < 2 * LEN; i++) {
        _shuffle(tmp, LEN);
        is_all_passed = assert_arr_ne(tmp, LEN, ARR, LEN, msg);
    }

    return is_all_passed;
}

bool test_clear(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should set all elements to 0";
    _copy(tmp, LEN, ARR, LEN);
    _clear(tmp, LEN);
    elem_t zero[LEN] = {0, 0, 0, 0, 0, 0};
    is_all_passed    = assert_arr_eq(tmp, LEN, zero, LEN, msg);

    return is_all_passed;
}

bool test_reverse(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should not reverse [0, 1)";
    _copy(tmp, LEN, ARR, LEN);
    _reverse(tmp, 1);
    elem_t reverse_one[] = {0};
    is_all_passed        = assert_arr_eq(tmp, 1, reverse_one, 1, msg);

    msg = "should reverse [0, 2)";
    _copy(tmp, LEN, ARR, LEN);
    _reverse(tmp, 2);
    elem_t reverse_two[] = {1, 0};
    is_all_passed        = assert_arr_eq(tmp, 2, reverse_two, 2, msg);

    msg = "should reverse [0, len)";
    _copy(tmp, LEN, ARR, LEN);
    _reverse(tmp, LEN);
    elem_t reverse_all[] = {5, 4, 3, 2, 1, 0};
    is_all_passed        = assert_arr_eq(tmp, LEN, reverse_all, LEN, msg);

    return is_all_passed;
}

bool test_reverse_slice(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should not reverse [1, 2)";
    _copy(tmp, LEN, ARR, LEN);
    _reverse_slice(tmp, LEN, 1, 2);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should not reverse [2, 1)";
    _copy(tmp, LEN, ARR, LEN);
    _reverse_slice(tmp, LEN, 2, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should reverse [1, len-1)";
    _copy(tmp, LEN, ARR, LEN);
    _reverse_slice(tmp, LEN, 1, LEN - 1);
    elem_t reverse_1_len[] = {0, 4, 3, 2, 1, 5};
    is_all_passed          = assert_arr_eq(tmp, LEN, reverse_1_len, LEN, msg);

    msg = "should reverse [1, len+1)";
    _copy(tmp, LEN, ARR, LEN);
    _reverse_slice(tmp, LEN, 1, LEN + 1);
    elem_t reverse_1_over[] = {0, 5, 4, 3, 2, 1};
    is_all_passed           = assert_arr_eq(tmp, LEN, reverse_1_over, LEN, msg);

    return is_all_passed;
}

bool test_find(void) {
    size_t i;
    bool   is_all_passed;
    char  *msg;

    msg           = "should find at [0]";
    bool find_0   = _find(ARR, LEN, 0, &i);
    is_all_passed = assert(find_0 && i == 0, msg);

    msg            = "should find at tail";
    bool find_tail = _find(ARR, LEN, LEN - 1, &i);
    is_all_passed  = assert(find_tail && i == LEN - 1, msg);

    msg            = "should not find when not exist";
    i              = 0;
    bool find_none = _find(ARR, LEN, 999, &i);
    is_all_passed  = assert(!find_none && i == 0, msg);

    return is_all_passed;
}

bool test_find_slice(void) {
    size_t i;
    bool   is_all_passed;
    char  *msg;

    msg           = "should find at [0] in [0, len)";
    bool find_0   = _find_slice(ARR, LEN, 0, LEN, 0, &i);
    is_all_passed = assert(find_0 && i == 0, msg);

    msg            = "should find at [len/2] in [1, len-1)";
    bool find_some = _find_slice(ARR, LEN, 1, LEN - 1, LEN / 2, &i);
    is_all_passed  = assert(find_some && i == 3, msg);

    msg            = "should not find in [1, 3) when not exist";
    bool find_none = _find_slice(ARR, LEN, 1, 3, 0, &i);
    is_all_passed  = assert_not(find_none, msg);

    return is_all_passed;
}

bool test_copy(void) {
    elem_t tmp[LEN];
    elem_t tmp_less[LEN - 1];
    elem_t tmp_over[LEN + 1];
    tmp_over[LEN] = 0;

    bool  is_all_passed;
    char *msg;

    msg = "should copy [0, len)";
    _copy(tmp, LEN, ARR, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should copy [0, len) in place";
    _copy(tmp, LEN, tmp, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, tmp, LEN, msg);

    msg = "should copy [0, len) to [0, len-1)";
    _copy(tmp_less, LEN - 1, ARR, LEN);
    is_all_passed = assert_arr_eq(tmp_less, LEN - 1, ARR, LEN - 1, msg);

    msg = "should copy [0, len+1) to [0, len)";
    _copy(tmp_over, LEN + 1, ARR, LEN);
    elem_t copy_over[LEN + 1] = {0, 1, 2, 3, 4, 5, 0};
    is_all_passed = assert_arr_eq(tmp_over, LEN + 1, copy_over, LEN + 1, msg);

    return is_all_passed;
}

bool test_copy_slice(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should copy  [len/2, len) to [0, len/2)";
    _clear(tmp, LEN);
    _copy_slice(tmp, LEN, 0, LEN / 2, ARR, LEN, LEN / 2, LEN);
    elem_t copy_rhalf_lhalf[] = {3, 4, 5, 0, 0, 0};
    is_all_passed = assert_arr_eq(tmp, LEN, copy_rhalf_lhalf, LEN, msg);

    msg = "should copy [1, len) to [0, len-1) in place";
    _copy(tmp, LEN, ARR, LEN);
    _copy_slice(tmp, LEN, 0, LEN - 1, tmp, LEN, 1, LEN);
    elem_t copy_overlap[] = {1, 2, 3, 4, 5, 5};
    is_all_passed         = assert_arr_eq(tmp, LEN, copy_overlap, LEN, msg);

    msg = "should copy [0, len) to [0, len/2)";
    _clear(tmp, LEN);
    _copy_slice(tmp, LEN, 0, LEN / 2, ARR, LEN, 0, LEN);
    elem_t copy_over_less[] = {0, 1, 2, 0, 0, 0};
    is_all_passed           = assert_arr_eq(tmp, LEN, copy_over_less, LEN, msg);

    msg = "should copy [0, len/2) to [0, len)";
    _clear(tmp, LEN);
    _copy_slice(tmp, LEN, 0, LEN, ARR, LEN, 0, LEN / 2);
    elem_t copy_less_over[] = {0, 1, 2, 0, 0, 0};
    is_all_passed           = assert_arr_eq(tmp, LEN, copy_less_over, LEN, msg);

    msg = "should copy [0, len) to [0, len)";
    _clear(tmp, LEN);
    _copy_slice(tmp, LEN, 0, LEN, ARR, LEN, 0, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should copy [0, len+1) to [0, len)";
    _clear(tmp, LEN);
    _copy_slice(tmp, LEN, 0, LEN, ARR, LEN, 0, LEN + 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should copy [0, len) to [0, len+1)";
    _clear(tmp, LEN);
    _copy_slice(tmp, LEN, 0, LEN + 1, ARR, LEN, 0, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    return is_all_passed;
}

bool test_move_left(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should not move left when n == len";
    _copy(tmp, LEN, ARR, LEN);
    _move_left(tmp, LEN, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should not move left when n > len";
    _copy(tmp, LEN, ARR, LEN);
    _move_left(tmp, LEN, LEN + 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should move 2 steps left";
    _copy(tmp, LEN, ARR, LEN);
    _move_left(tmp, LEN, 2);
    elem_t move_2[] = {2, 3, 4, 5, 4, 5};
    is_all_passed   = assert_arr_eq(tmp, LEN, move_2, LEN, msg);

    return is_all_passed;
}

bool test_move_left_slice(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should not move left slice when n > len";
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 1, LEN - 1, LEN + 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should not move left slice when start > end";
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 2, 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should move 2 steps left slice in [0, len)";
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 0, LEN, 2);
    elem_t move_all_2[] = {2, 3, 4, 5, 4, 5};
    is_all_passed       = assert_arr_eq(tmp, LEN, move_all_2, LEN, msg);

    msg = "should move 2 step left slice in [1, len-1)";
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 1, LEN - 1, 2);
    elem_t move_slice_2[] = {0, 3, 4, 3, 4, 5};
    is_all_passed         = assert_arr_eq(tmp, LEN, move_slice_2, LEN, msg);

    msg = "should move 2 step left slice in [1, len+1)";
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 1, LEN + 1, 2);
    elem_t move_over_2[] = {0, 3, 4, 5, 4, 5};
    is_all_passed        = assert_arr_eq(tmp, LEN, move_over_2, LEN, msg);

    return is_all_passed;
}

bool test_move_right(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should not move right when n == len";
    _copy(tmp, LEN, ARR, LEN);
    _move_right(tmp, LEN, LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should not move right when n > len";
    _copy(tmp, LEN, ARR, LEN);
    _move_right(tmp, LEN, LEN + 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should move 2 steps right";
    _copy(tmp, LEN, ARR, LEN);
    _move_right(tmp, LEN, 2);
    elem_t move_2[] = {0, 1, 0, 1, 2, 3};
    is_all_passed   = assert_arr_eq(tmp, LEN, move_2, LEN, msg);

    return is_all_passed;
}

bool test_move_right_slice(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should not move right slice when n > len";
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 1, LEN - 1, LEN + 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should not move right slice when start > end";
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 2, 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should move 2 steps right slice in [0, len)";
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 0, LEN, 2);
    elem_t move_0_len_2[] = {0, 1, 0, 1, 2, 3};
    is_all_passed         = assert_arr_eq(tmp, LEN, move_0_len_2, LEN, msg);

    msg = "should move 2 step right slice in [1, len-1)";
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 1, 5, 2);
    elem_t move_1_5_1[] = {0, 1, 2, 1, 2, 5};
    is_all_passed       = assert_arr_eq(tmp, LEN, move_1_5_1, LEN, msg);

    msg = "should move 2 step right slice in [1, len+1)";
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 1, LEN + 1, 2);
    elem_t move_1_over_1[] = {0, 1, 2, 1, 2, 3};
    is_all_passed          = assert_arr_eq(tmp, LEN, move_1_over_1, LEN, msg);

    return is_all_passed;
}

bool test_rotate_left(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should not rotate left when n mod len == 0";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, 2 * LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should rotate 2 steps left";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, 2);
    elem_t rotate_2[] = {2, 3, 4, 5, 0, 1};
    is_all_passed     = assert_arr_eq(tmp, LEN, rotate_2, LEN, msg);

    msg = "should rotate 3 steps left when n > len and n mod len != 0";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, LEN + 3);
    elem_t rotate_over_3[] = {3, 4, 5, 0, 1, 2};
    is_all_passed          = assert_arr_eq(tmp, LEN, rotate_over_3, LEN, msg);

    return is_all_passed;
}

bool test_rotate_left_slice(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should not rotate left slice when n mod len == 0";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 1, LEN - 1, LEN - 2);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should not rotate left slice when start > end";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 2, 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should rotate 2 steps left slice in [0, len)";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 0, LEN, 2);
    elem_t rotate_all_2[] = {2, 3, 4, 5, 0, 1};
    is_all_passed         = assert_arr_eq(tmp, LEN, rotate_all_2, LEN, msg);

    msg = "should rotate 1 step left slice in [1, len-1) when n > len and n "
          "mod len != 0";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 1, LEN - 1, LEN - 1);
    elem_t rotate_less_over[] = {0, 2, 3, 4, 1, 5};
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_less_over, LEN, msg);

    msg = "should rotate 1 step left slice in [1, len-1)";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 1, LEN - 1, 1);
    elem_t rotate_less_1[] = {0, 2, 3, 4, 1, 5};
    is_all_passed          = assert_arr_eq(tmp, LEN, rotate_less_1, LEN, msg);

    msg = "should rotate 1 step left slice in [1, len+1)";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 1, LEN + 1, 1);
    elem_t rotate_over_1[] = {0, 2, 3, 4, 5, 1};
    is_all_passed          = assert_arr_eq(tmp, LEN, rotate_over_1, LEN, msg);

    return is_all_passed;
}

bool test_rotate_right(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should not rotate right when n mod len == 0";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, 2 * LEN);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should rotate 2 steps right";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, 2);
    elem_t rotate_2[] = {4, 5, 0, 1, 2, 3};
    is_all_passed     = assert_arr_eq(tmp, LEN, rotate_2, LEN, msg);

    msg = "should rotate over 3 steps right when n > len and n mod len != 0";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, LEN + 3);
    elem_t rotate_over_3[] = {3, 4, 5, 0, 1, 2};
    is_all_passed          = assert_arr_eq(tmp, LEN, rotate_over_3, LEN, msg);

    return is_all_passed;
}

bool test_rotate_right_slice(void) {
    elem_t tmp[LEN];
    bool   is_all_passed;
    char  *msg;

    msg = "should not rotate right slice when n mod len == 0";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 1, LEN - 1, LEN - 2);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should not rotate right slice when start > end";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 2, 1, 1);
    is_all_passed = assert_arr_eq(tmp, LEN, ARR, LEN, msg);

    msg = "should rotate 2 steps right slice in [0, len)";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 0, LEN, 2);
    elem_t rotate_all[] = {4, 5, 0, 1, 2, 3};
    is_all_passed       = assert_arr_eq(tmp, LEN, rotate_all, LEN, msg);

    msg = "should rotate 1 step right slice in [1, len-1)";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 1, 5, 1);
    elem_t rotate_less_1[] = {0, 4, 1, 2, 3, 5};
    is_all_passed          = assert_arr_eq(tmp, LEN, rotate_less_1, LEN, msg);

    msg = "should rotate 1 step right slice in [1, len-1) when n > len and n "
          "mod len != 0";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 1, LEN - 1, LEN - 1);
    elem_t rotate_less_over[] = {0, 4, 1, 2, 3, 5};
    is_all_passed = assert_arr_eq(tmp, LEN, rotate_less_over, LEN, msg);

    msg = "should rotate 1 step right slice in [1, len+1)";
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 1, LEN + 1, 1);
    elem_t rotate_over_1[] = {0, 5, 1, 2, 3, 4};
    is_all_passed          = assert_arr_eq(tmp, LEN, rotate_over_1, LEN, msg);

    return is_all_passed;
}

int main(void) {
    char *prefix = "utils";
    run_test(test_swap, prefix, "swap");
    run_test(test_shuffle, prefix, "shuffle");
    run_test(test_clear, prefix, "clear");
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

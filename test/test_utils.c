#include "test.h"
#include "utils.h"
#include <string.h>

#define LEN 6
elem_t ARR[LEN] = {0, 1, 2, 3, 4, 5};

bool test_swap(void) {
    elem_t tmp[LEN];

    // expect array's name like swap_<i>_<j>
    elem_t swap_0_5[] = {5, 1, 2, 3, 4, 0};
    elem_t swap_4_1[] = {0, 4, 2, 3, 1, 5};

    bool is_all_passed;

    // swap_0_5
    _copy(tmp, LEN, ARR, LEN);
    _swap(tmp, 0, 5);
    is_all_passed = assert_eq(tmp, LEN, swap_0_5, LEN);

    // swap_4_1
    _copy(tmp, LEN, ARR, LEN);
    _swap(tmp, 4, 1);
    is_all_passed = assert_eq(tmp, LEN, swap_4_1, LEN);

    // swap_3_3, no change
    _copy(tmp, LEN, ARR, LEN);
    _swap(tmp, 3, 3);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    return is_all_passed;
}

bool test_find(void) {
    size_t i;
    bool   is_all_passed;

    // expect result's name like find_<e>
    bool find_0   = _find(ARR, LEN, 0, &i);
    is_all_passed = find_0 && i == 0;
    bool find_5   = _find(ARR, LEN, 5, &i);
    is_all_passed = find_5 && i == 5;
    bool find_100 = _find(ARR, LEN, 100, &i);
    is_all_passed = !find_100;

    return is_all_passed;
}

bool test_find_slice(void) {
    size_t i;
    bool   is_all_passed;

    // expect result's name like find_<start>_<end>_<e>
    bool find_0_len_0 = _find_slice(ARR, LEN, 0, LEN, 0, &i);
    is_all_passed     = find_0_len_0 && i == 0;
    bool find_1_5_3   = _find_slice(ARR, LEN, 1, 5, 3, &i);
    is_all_passed     = find_1_5_3 && i == 3;
    bool find_2_3_1   = _find_slice(ARR, LEN, 2, 3, 1, &i);
    is_all_passed     = !find_2_3_1;

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

    bool is_all_passed;

    // copy_len
    _copy(tmp, LEN, ARR, LEN);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // copy self in place, no change
    _copy(tmp, LEN, tmp, LEN);
    is_all_passed = assert_eq(tmp, LEN, tmp, LEN);

    // copy_less, tmp_less same as ARR[0..LEN-1]
    _copy(tmp_less, LEN - 1, ARR, LEN);
    is_all_passed = assert_eq(tmp_less, LEN - 1, ARR, LEN - 1);

    // copy_over, tmp_over[0..LEN] same as ARR
    _copy(tmp_over, LEN + 1, ARR, LEN);
    is_all_passed = assert_eq(tmp_over, LEN + 1, copy_over, LEN + 1);

    return is_all_passed;
}

bool test_copy_slice(void) {
    elem_t tmp[LEN];

    // expect array's name like copy_<d_len>_<s_len>
    elem_t copy_lhalf_rhalf[] = {3, 4, 5, 0, 0, 0};
    elem_t copy_overlap[]     = {1, 2, 3, 4, 5, 5};
    elem_t copy_less_over[]   = {0, 1, 2, 0, 0, 0};
    elem_t copy_over_less[]   = {0, 1, 2, 0, 0, 0};

    bool is_all_passed;

    // copy_lhalf_rhalf
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN / 2, ARR, LEN, LEN / 2, LEN);
    is_all_passed = assert_eq(tmp, LEN, copy_lhalf_rhalf, LEN);

    // copy_overlap in place
    _copy(tmp, LEN, ARR, LEN);
    _copy_slice(tmp, LEN, 0, LEN - 1, tmp, LEN, 1, LEN);
    is_all_passed = assert_eq(tmp, LEN, copy_overlap, LEN);

    // copy_less_over
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN / 2, ARR, LEN, 0, LEN);
    is_all_passed = assert_eq(tmp, LEN, copy_less_over, LEN);

    // copy_over_less
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN, ARR, LEN, 0, LEN / 2);
    is_all_passed = assert_eq(tmp, LEN, copy_over_less, LEN);

    // copy_len_len, same as ARR
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN, ARR, LEN, 0, LEN);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // copy_len_over, same as ARR
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN, ARR, LEN, 0, LEN + 1);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // copy_over_len, same as ARR
    memset(tmp, 0, LEN * sizeof(elem_t));
    _copy_slice(tmp, LEN, 0, LEN + 1, ARR, LEN, 0, LEN);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    return is_all_passed;
}

bool test_move_left(void) {
    elem_t tmp[LEN];

    // expect array's name like move_<n>
    elem_t move_2[] = {2, 3, 4, 5, 4, 5};

    bool is_all_passed;

    // move_2
    _copy(tmp, LEN, ARR, LEN);
    _move_left(tmp, LEN, 2);
    is_all_passed = assert_eq(tmp, LEN, move_2, LEN);

    // move_len, no change
    _copy(tmp, LEN, ARR, LEN);
    _move_left(tmp, LEN, LEN);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // move_over, no change
    _copy(tmp, LEN, ARR, LEN);
    _move_left(tmp, LEN, LEN + 1);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    return is_all_passed;
}

bool test_move_left_slice(void) {
    elem_t tmp[LEN];

    // expect array's name like move_<start>_<end>_<n>
    elem_t move_0_len_2[]  = {2, 3, 4, 5, 4, 5};
    elem_t move_1_5_1[]    = {0, 2, 3, 4, 4, 5};
    elem_t move_1_over_1[] = {0, 2, 3, 4, 5, 5};

    bool is_all_passed;

    // move_0_len_2
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 0, LEN, 2);
    is_all_passed = assert_eq(tmp, LEN, move_0_len_2, LEN);

    // move_1_5_1
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 1, 5, 1);
    is_all_passed = assert_eq(tmp, LEN, move_1_5_1, LEN);

    // move_1_over_1
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 1, LEN + 1, 1);
    is_all_passed = assert_eq(tmp, LEN, move_1_over_1, LEN);

    // move_1_5_over, no change
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 1, 5, LEN + 1);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // move_3_1_1, no change
    _copy(tmp, LEN, ARR, LEN);
    _move_left_slice(tmp, LEN, 3, 1, 1);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    return is_all_passed;
}

bool test_move_right(void) {
    elem_t tmp[LEN];

    // expect array's name like move_<n>
    elem_t move_2[] = {0, 1, 0, 1, 2, 3};

    bool is_all_passed;

    // move_2
    _copy(tmp, LEN, ARR, LEN);
    _move_right(tmp, LEN, 2);
    is_all_passed = assert_eq(tmp, LEN, move_2, LEN);

    // move_len, no change
    _copy(tmp, LEN, ARR, LEN);
    _move_right(tmp, LEN, LEN);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // move_over, no change
    _copy(tmp, LEN, ARR, LEN);
    _move_right(tmp, LEN, LEN + 1);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    return is_all_passed;
}

bool test_move_right_slice(void) {
    elem_t tmp[LEN];

    // expect array's name like move_<start>_<end>_<n>
    elem_t move_0_len_2[]  = {0, 1, 0, 1, 2, 3};
    elem_t move_1_5_1[]    = {0, 1, 1, 2, 3, 5};
    elem_t move_1_over_1[] = {0, 1, 1, 2, 3, 4};

    bool is_all_passed;

    // move_0_len_2
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 0, LEN, 2);
    is_all_passed = assert_eq(tmp, LEN, move_0_len_2, LEN);

    // move_1_5_1
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 1, 5, 1);
    is_all_passed = assert_eq(tmp, LEN, move_1_5_1, LEN);

    // move_1_over_1
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 1, LEN + 1, 1);
    is_all_passed = assert_eq(tmp, LEN, move_1_over_1, LEN);

    // move_1_5_over, no change
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 1, 5, LEN + 1);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // move_3_1_1, no change
    _copy(tmp, LEN, ARR, LEN);
    _move_right_slice(tmp, LEN, 3, 1, 1);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    return is_all_passed;
}

bool test_rotate_left(void) {
    elem_t tmp[LEN];

    // expect array's name like rotate_<n>
    elem_t rotate_2[]      = {2, 3, 4, 5, 0, 1};
    elem_t rotate_over_3[] = {3, 4, 5, 0, 1, 2};

    bool is_all_passed;

    // rotate_2
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, 2);
    is_all_passed = assert_eq(tmp, LEN, rotate_2, LEN);

    // rotate_over_3
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, LEN + 3);
    is_all_passed = assert_eq(tmp, LEN, rotate_over_3, LEN);

    // rotate_0, no change
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, 0);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // rotate_len, no change
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, LEN);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // rotate_2*len, no change
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left(tmp, LEN, 2 * LEN);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    return is_all_passed;
}

bool test_rotate_left_slice(void) {
    elem_t tmp[LEN];

    // expect array's name like rotate_<start>_<end>_<n>
    elem_t rotate_0_len_2[]  = {2, 3, 4, 5, 0, 1};
    elem_t rotate_1_5_1[]    = {0, 2, 3, 4, 1, 5};
    elem_t rotate_1_over_1[] = {0, 2, 3, 4, 5, 1};

    bool is_all_passed;

    // rotate_0_len_2
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 0, LEN, 2);
    is_all_passed = assert_eq(tmp, LEN, rotate_0_len_2, LEN);

    // rotate_1_5_1
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 1, 5, 1);
    is_all_passed = assert_eq(tmp, LEN, rotate_1_5_1, LEN);

    // rotate_1_over_1
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 1, LEN + 1, 1);
    is_all_passed = assert_eq(tmp, LEN, rotate_1_over_1, LEN);

    // rotate_1_5_2*len, no change
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 1, 5, 8);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // rotate_3_1_1, no change
    _copy(tmp, LEN, ARR, LEN);
    _rotate_left_slice(tmp, LEN, 3, 1, 1);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    return is_all_passed;
}

bool test_rotate_right(void) {
    elem_t tmp[LEN];

    // expect array's name like rotate_<n>
    elem_t rotate_2[]      = {4, 5, 0, 1, 2, 3};
    elem_t rotate_over_3[] = {3, 4, 5, 0, 1, 2};

    bool is_all_passed;

    // rotate_2
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, 2);
    is_all_passed = assert_eq(tmp, LEN, rotate_2, LEN);

    // rotate_over_3
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, LEN + 3);
    is_all_passed = assert_eq(tmp, LEN, rotate_over_3, LEN);

    // rotate_0, no change
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, 0);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // rotate_len, no change
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, LEN);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // rotate_2*len, no change
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right(tmp, LEN, 2 * LEN);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    return is_all_passed;
}

bool test_rotate_right_slice(void) {
    elem_t tmp[LEN];

    // expect array's name like rotate_<start>_<end>_<n>
    elem_t rotate_0_len_2[]  = {4, 5, 0, 1, 2, 3};
    elem_t rotate_1_5_1[]    = {0, 4, 1, 2, 3, 5};
    elem_t rotate_1_over_1[] = {0, 5, 1, 2, 3, 4};

    bool is_all_passed;

    // rotate_0_len_2
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 0, LEN, 2);
    is_all_passed = assert_eq(tmp, LEN, rotate_0_len_2, LEN);

    // rotate_1_5_1
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 1, 5, 1);
    is_all_passed = assert_eq(tmp, LEN, rotate_1_5_1, LEN);

    // rotate_1_over_1
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 1, LEN + 1, 1);
    is_all_passed = assert_eq(tmp, LEN, rotate_1_over_1, LEN);

    // rotate_1_5_2*len, no change
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 1, 5, 8);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    // rotate_3_1_1, no change
    _copy(tmp, LEN, ARR, LEN);
    _rotate_right_slice(tmp, LEN, 3, 1, 1);
    is_all_passed = assert_eq(tmp, LEN, ARR, LEN);

    return is_all_passed;
}

int main(void) {
    char *prefix = "utils";
    run_test(test_swap, prefix, "test_swap");
    run_test(test_find, prefix, "test_find");
    run_test(test_find_slice, prefix, "test_find_slice");
    run_test(test_copy, prefix, "test_copy");
    run_test(test_copy_slice, prefix, "test_copy_slice");
    run_test(test_move_left, prefix, "test_move_left");
    run_test(test_move_left_slice, prefix, "test_move_left_slice");
    run_test(test_move_right, prefix, "test_move_right");
    run_test(test_move_right_slice, prefix, "test_move_right_slice");
    run_test(test_rotate_left, prefix, "test_rotate_left");
    run_test(test_rotate_left_slice, prefix, "test_rotate_left_slice");
    run_test(test_rotate_right, prefix, "test_rotate_right");
    run_test(test_rotate_right_slice, prefix, "test_rotate_right_slice");

    return 0;
}

#include "insertion.h"
#include "test.h"
#include "utils.h"

TestSortData DATA[SORT_DATA_LEN];

bool test_insertion_sort(void) {
    bool all_passed;

    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t len = DATA[i].len;
        elem_t tmp[len];
        copy(tmp, len, DATA[i].unsorted, len);
        insertion_sort(tmp, len);
        all_passed = assert_array_eq(tmp, len, DATA[i].sorted, len);
    }

    return all_passed;
}

bool test_binary_insertion_sort(void) {
    bool all_passed;

    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t len = DATA[i].len;
        elem_t tmp[len];
        copy(tmp, len, DATA[i].unsorted, len);
        binary_insertion_sort(tmp, len);
        all_passed = assert_array_eq(tmp, len, DATA[i].sorted, len);
    }

    return all_passed;
}

bool test_shell_sort(void) {
    bool all_passed;

    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t len = DATA[i].len;
        elem_t tmp[len];
        copy(tmp, len, DATA[i].unsorted, len);
        shell_sort(tmp, len);
        all_passed = assert_array_eq(tmp, len, DATA[i].sorted, len);
    }

    return all_passed;
}

int main(void) {
    init_sort_data(DATA);
    run_test(test_insertion_sort, "sort", "test_insertion_sort");
    run_test(test_binary_insertion_sort, "sort", "test_binary_insertion_sort");
    run_test(test_shell_sort, "sort", "test_shell_sort\t");
    return 0;
}

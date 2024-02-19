#include "merge.h"
#include "test.h"
#include "utils.h"

TestSortData DATA[SORT_DATA_LEN];

bool test_merge_sort_recu(void) {
    bool all_passed;

    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t len = DATA[i].len;
        elem_t tmp[len];
        copy(tmp, len, DATA[i].unsorted, len);
        merge_sort_recu(tmp, len);
        all_passed = assert_eq(tmp, len, DATA[i].sorted, len);
    }

    return all_passed;
}

bool test_merge_sort_iter(void) {
    bool all_passed;

    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t len = DATA[i].len;
        elem_t tmp[len];
        copy(tmp, len, DATA[i].unsorted, len);
        merge_sort_iter(tmp, len);
        all_passed = assert_eq(tmp, len, DATA[i].sorted, len);
    }

    return all_passed;
}

int main(void) {
    init_sort_data(DATA);
    run_test(test_merge_sort_recu, "sort", "test_merge_sort_recu");
    run_test(test_merge_sort_iter, "sort", "test_merge_sort_iter");

    return 0;
}

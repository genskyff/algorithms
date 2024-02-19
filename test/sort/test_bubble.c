#include "bubble.h"
#include "test.h"
#include "utils.h"

TestSortData DATA[SORT_DATA_LEN];

bool test_bubble_sort(void) {
    bool all_passed;

    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t len = DATA[i].len;
        elem_t tmp[len];
        copy(tmp, len, DATA[i].unsorted, len);
        bubble_sort(tmp, len);
        all_passed = assert_eq(tmp, len, DATA[i].sorted, len);
    }

    return all_passed;
}

bool test_cocktail_sort(void) {
    bool all_passed;

    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t len = DATA[i].len;
        elem_t tmp[len];
        copy(tmp, len, DATA[i].unsorted, len);
        cocktail_sort(tmp, len);
        all_passed = assert_eq(tmp, len, DATA[i].sorted, len);
    }
    return all_passed;
}

int main(void) {
    init_sort_data(DATA);
    run_test(test_bubble_sort, "sort", "test_bubble_sort\t");
    run_test(test_cocktail_sort, "sort", "test_cocktail_sort\t");

    return 0;
}

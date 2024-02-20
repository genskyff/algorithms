#include "bubble.h"
#include "test.h"
#include "utils.h"
#include <stdlib.h>

TestSortData DATA[SORT_DATA_LEN];

bool test_bubble_sort(void) {
    bool all_passed;

    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t  len = DATA[i].len;
        elem_t *tmp = malloc(len * sizeof(elem_t));
        copy(tmp, len, DATA[i].unsorted, len);
        bubble_sort(tmp, len);
        all_passed = assert_eq(tmp, len, DATA[i].sorted, len);
        free(tmp);
    }

    return all_passed;
}

bool test_cocktail_sort(void) {
    bool all_passed;

    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t  len = DATA[i].len;
        elem_t *tmp = malloc(len * sizeof(elem_t));
        copy(tmp, len, DATA[i].unsorted, len);
        cocktail_sort(tmp, len);
        all_passed = assert_eq(tmp, len, DATA[i].sorted, len);
        free(tmp);
    }

    return all_passed;
}

int main(void) {
    char *prefix = "sort";
    init_sort_data(DATA);
    run_test(test_bubble_sort, prefix, "test_bubble_sort\t");
    run_test(test_cocktail_sort, prefix, "test_cocktail_sort\t");

    return 0;
}

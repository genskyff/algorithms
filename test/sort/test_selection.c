#include "selection.h"
#include "test.h"
#include "utils.h"
#include <stdlib.h>

TestSortData DATA[SORT_DATA_LEN];

bool test_selection_sort(void) {
    bool all_passed;

    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t  len = DATA[i].len;
        elem_t *tmp = malloc(len * sizeof(elem_t));
        _copy(tmp, len, DATA[i].unsorted, len);
        selection_sort(tmp, len);
        all_passed = assert_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }

    return all_passed;
}

int main(void) {
    char *prefix = "sort";
    init_sort_data(DATA);
    run_test(test_selection_sort, prefix, "test_selection_sort");

    return 0;
}

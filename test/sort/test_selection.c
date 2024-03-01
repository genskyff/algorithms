#include "selection.h"
#include "test_helper.h"
#include "utils.h"
#include <stdlib.h>

TestSortData DATA[SORT_DATA_LEN];

void test_selection_sort(void) {
    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t  len = DATA[i].len;
        elem_t *tmp = len == 0 ? NULL : malloc(len * sizeof(elem_t));
        _copy(tmp, len, DATA[i].unsorted, len);
        selection_sort(tmp, len);
        assert_arr_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }
}

int main(void) {
    char *prefix = "sort";
    init_sort_data(DATA);
    run_test(test_selection_sort, prefix, "selection_sort");

    return 0;
}

#include "helper.h"
#include "merge.h"
#include "utils.h"
#include <stdlib.h>


TestSortData DATA[SORT_DATA_LEN];

void test_merge_sort_recu(void) {
    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t  len = DATA[i].len;
        elem_t *tmp = len == 0 ? NULL : malloc(len * sizeof(elem_t));
        _copy(tmp, len, DATA[i].unsorted, len);
        merge_sort_recu(tmp, len);
        assert_arr_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }
}

void test_merge_sort_iter(void) {
    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t  len = DATA[i].len;
        elem_t *tmp = len == 0 ? NULL : malloc(len * sizeof(elem_t));
        _copy(tmp, len, DATA[i].unsorted, len);
        merge_sort_iter(tmp, len);
        assert_arr_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }
}

int main(void) {
    char *prefix = "sort";
    init_sort_data(DATA);
    run_test(test_merge_sort_recu, prefix, "merge_sort_recu");
    run_test(test_merge_sort_iter, prefix, "merge_sort_iter");

    return 0;
}

#include "alg/sort/merge.h"
#include "helper.h"
#include "internal/utils.h"
#include <stdlib.h>

TestSortData DATA[SORT_DATA_LEN];

void test_merge_sort_recu(void) {
    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        alg_elem_t  len = DATA[i].len;
        alg_elem_t *tmp = len == 0 ? NULL : malloc(len * sizeof(alg_elem_t));
        alg_internal_copy(tmp, len, DATA[i].unsorted, len);
        alg_merge_sort_recu(tmp, len);
        assert_arr_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }
}

void test_merge_sort_iter(void) {
    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        alg_elem_t  len = DATA[i].len;
        alg_elem_t *tmp = len == 0 ? NULL : malloc(len * sizeof(alg_elem_t));
        alg_internal_copy(tmp, len, DATA[i].unsorted, len);
        alg_merge_sort_iter(tmp, len);
        assert_arr_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }
}

int main(void) {
    char *mod    = "sort";
    char *target = NULL;

    init_sort_data(DATA);
    run_test(test_merge_sort_recu, mod, target, "merge_sort_recu");
    run_test(test_merge_sort_iter, mod, target, "merge_sort_iter");

    return 0;
}

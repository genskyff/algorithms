#include "alg/sort/quick.h"
#include "helper.h"
#include "internal/utils.h"
#include <stdlib.h>

TestSortData DATA[SORT_DATA_LEN];

void test_quick_sort(void) {
    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        alg_elem_t  len = DATA[i].len;
        alg_elem_t *tmp = len == 0 ? NULL : malloc(len * sizeof(alg_elem_t));
        alg_internal_copy(tmp, len, DATA[i].unsorted, len);
        alg_quick_sort(tmp, len);
        assert_arr_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }
}

int main(void) {
    char *mod    = "sort";
    char *target = NULL;

    init_sort_data(DATA);
    run_test(test_quick_sort, mod, target, "quick_sort");

    return 0;
}

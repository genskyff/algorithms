#include "alg/sort/bubble.h"
#include "helper.h"
#include "utils.h"
#include <stdlib.h>

TestSortData DATA[SORT_DATA_LEN];

void test_bubble_sort(void) {
    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        alg_elem_t  len = DATA[i].len;
        alg_elem_t *tmp = len == 0 ? NULL : malloc(len * sizeof(alg_elem_t));
        alg_internal_copy(tmp, len, DATA[i].unsorted, len);
        alg_bubble_sort(tmp, len);
        assert_arr_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }
}

void test_cocktail_sort(void) {
    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        alg_elem_t  len = DATA[i].len;
        alg_elem_t *tmp = len == 0 ? NULL : malloc(len * sizeof(alg_elem_t));
        alg_internal_copy(tmp, len, DATA[i].unsorted, len);
        alg_cocktail_sort(tmp, len);
        assert_arr_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }
}

int main(void) {
    char *mod    = "sort";
    char *target = NULL;

    init_sort_data(DATA);
    run_test(test_bubble_sort, mod, target, "bubble_sort");
    run_test(test_cocktail_sort, mod, target, "cocktail_sort");

    return 0;
}

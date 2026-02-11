#include "alg/sort/insertion.h"
#include "helper.h"
#include "utils.h"
#include <stdlib.h>

TestSortData DATA[SORT_DATA_LEN];

void test_insertion_sort(void) {
    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t  len = DATA[i].len;
        elem_t *tmp = len == 0 ? NULL : malloc(len * sizeof(elem_t));
        _copy(tmp, len, DATA[i].unsorted, len);
        insertion_sort(tmp, len);
        assert_arr_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }
}

void test_binary_insertion_sort(void) {
    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t  len = DATA[i].len;
        elem_t *tmp = len == 0 ? NULL : malloc(len * sizeof(elem_t));
        _copy(tmp, len, DATA[i].unsorted, len);
        binary_insertion_sort(tmp, len);
        assert_arr_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }
}

void test_shell_sort(void) {
    for (size_t i = 0; i < SORT_DATA_LEN; i++) {
        elem_t  len = DATA[i].len;
        elem_t *tmp = len == 0 ? NULL : malloc(len * sizeof(elem_t));
        _copy(tmp, len, DATA[i].unsorted, len);
        shell_sort(tmp, len);
        assert_arr_eq(tmp, len, DATA[i].sorted, len, NULL);
        free(tmp);
    }
}

int main(void) {
    char *mod    = "sort";
    char *target = NULL;

    init_sort_data(DATA);
    run_test(test_insertion_sort, mod, target, "insertion_sort");
    run_test(test_binary_insertion_sort, mod, target, "binary_insertion_sort");
    run_test(test_shell_sort, mod, target, "shell_sort");

    return 0;
}

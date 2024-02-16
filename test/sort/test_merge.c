#include "merge.h"
#include "test.h"
#include "utils.h"
#include <stdlib.h>

bool test_merge_sort_recu(void) {
    bool all_passed = true;

    for (size_t i = 0; i < DATA_LEN; i++) {
        elem_t *data = (elem_t *)malloc(DATA[i].unsorted.len * sizeof(elem_t));
        Array   arr  = {data, DATA[i].unsorted.len};
        copy(&arr, &DATA[i].unsorted);
        merge_sort_recu(&arr);
        all_passed = assert_eq(&arr, &DATA[i].sorted);
        free(data);
    }

    return all_passed;
}

bool test_merge_sort_iter(void) {
    bool all_passed = true;

    for (size_t i = 0; i < DATA_LEN; i++) {
        elem_t *data = (elem_t *)malloc(DATA[i].unsorted.len * sizeof(elem_t));
        Array   arr  = {data, DATA[i].unsorted.len};
        copy(&arr, &DATA[i].unsorted);
        merge_sort_iter(&arr);
        all_passed = assert_eq(&arr, &DATA[i].sorted);
        free(data);
    }

    return all_passed;
}

int main(void) {
    run_test(test_merge_sort_recu, "test_merge_sort_recu");
    run_test(test_merge_sort_iter, "test_merge_sort_iter");

    return 0;
}

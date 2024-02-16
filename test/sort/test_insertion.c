#include "insertion.h"
#include "test.h"
#include "utils.h"
#include <stdlib.h>

bool test_insertion_sort(void) {
    bool all_passed = true;

    for (size_t i = 0; i < DATA_LEN; i++) {
        elem_t *data = (elem_t *)malloc(DATA[i].unsorted.len * sizeof(elem_t));
        Array   arr  = {data, DATA[i].unsorted.len};
        copy(&arr, &DATA[i].unsorted);
        insertion_sort(&arr);
        all_passed = assert_eq(&arr, &DATA[i].sorted);
        free(data);
    }

    return all_passed;
}

bool test_binary_insertion_sort(void) {
    bool all_passed = true;

    for (size_t i = 0; i < DATA_LEN; i++) {
        elem_t *data = (elem_t *)malloc(DATA[i].unsorted.len * sizeof(elem_t));
        Array   arr  = {data, DATA[i].unsorted.len};
        copy(&arr, &DATA[i].unsorted);
        binary_insertion_sort(&arr);
        all_passed = assert_eq(&arr, &DATA[i].sorted);
        free(data);
    }

    return all_passed;
}

bool test_shell_sort(void) {
    bool all_passed = true;

    for (size_t i = 0; i < DATA_LEN; i++) {
        elem_t *data = (elem_t *)malloc(DATA[i].unsorted.len * sizeof(elem_t));
        Array   arr  = {data, DATA[i].unsorted.len};
        copy(&arr, &DATA[i].unsorted);
        shell_sort(&arr);
        all_passed = assert_eq(&arr, &DATA[i].sorted);
        free(data);
    }

    return all_passed;
}

int main(void) {
    run_test(test_insertion_sort, "test_insertion_sort");
    run_test(test_binary_insertion_sort, "test_binary_insertion_sort");
    run_test(test_shell_sort, "test_shell_sort\t");
    return 0;
}

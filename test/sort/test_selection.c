#include "selection.h"
#include "test.h"
#include "utils.h"
#include <stdlib.h>

TestData DATA[DATA_LEN];

bool test_selection_sort(void) {
    bool all_passed = true;

    for (size_t i = 0; i < DATA_LEN; i++) {
        elem_t *data = (elem_t *)malloc(DATA[i].unsorted.len * sizeof(elem_t));
        Array   arr  = {data, DATA[i].unsorted.len};
        copy(&arr, &DATA[i].unsorted);
        selection_sort(&arr);
        all_passed = assert_eq(&arr, &DATA[i].sorted);
        free(data);
    }

    return all_passed;
}

int main(void) {
    init_data(DATA);
    run_test(test_selection_sort, "test_selection_sort");

    return 0;
}

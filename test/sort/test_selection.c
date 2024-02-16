#include "data.h"
#include "selection.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void test_selection_sort(void) {
    printf("test selection_sort\t\t");

    for (int i = 0; i < DATA_LEN; i++) {
        int *arr = (int *)malloc(DATA[i].len * sizeof(int));

        copy(DATA[i].unsorted, arr, DATA[i].len);
        selection_sort(arr, DATA[i].len);
        assert_eq(arr, DATA[i].sorted, DATA[i].len);
    }
}

int main(void) {
    test_selection_sort();

    return 0;
}

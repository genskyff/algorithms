#include "data.h"
#include "quick.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void test_quick_sort(void) {
    printf("test quick_sort\t\t\t");

    for (int i = 0; i < DATA_LEN; i++) {
        int *arr = (int *)malloc(DATA[i].len * sizeof(int));

        copy(DATA[i].unsorted, arr, DATA[i].len);
        quick_sort(arr, DATA[i].len);
        assert_eq(arr, DATA[i].sorted, DATA[i].len);
    }
}

int main(void) {
    test_quick_sort();

    return 0;
}

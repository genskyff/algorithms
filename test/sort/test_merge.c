#include "data.h"
#include "merge.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void test_merge_sort_recu(void) {
    printf("test merge_sort_recu\t\t");

    for (int i = 0; i < DATA_LEN; i++) {
        int *arr = (int *)malloc(DATA[i].len * sizeof(int));

        copy(DATA[i].unsorted, arr, DATA[i].len);
        merge_sort_recu(arr, DATA[i].len);
        assert_eq(arr, DATA[i].sorted, DATA[i].len);
    }
}

void test_merge_sort_iter(void) {
    printf("test merge_sort_iter\t\t");

    for (int i = 0; i < DATA_LEN; i++) {
        int *arr = (int *)malloc(DATA[i].len * sizeof(int));

        copy(DATA[i].unsorted, arr, DATA[i].len);
        merge_sort_iter(arr, DATA[i].len);
        assert_eq(arr, DATA[i].sorted, DATA[i].len);
    }
}

int main(void) {
    test_merge_sort_recu();
    test_merge_sort_iter();

    return 0;
}

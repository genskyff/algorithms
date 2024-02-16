#include "data.h"
#include "insertion.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void test_insertion_sort(void) {
    printf("test insertion_sort\t\t");

    for (int i = 0; i < DATA_LEN; i++) {
        int *arr = (int *)malloc(DATA[i].len * sizeof(int));

        copy(DATA[i].unsorted, arr, DATA[i].len);
        insertion_sort(arr, DATA[i].len);
        assert_eq(arr, DATA[i].sorted, DATA[i].len);
    }
}

void test_binary_insertion_sort(void) {
    printf("test binary_insertion_sort\t");

    for (int i = 0; i < DATA_LEN; i++) {
        int *arr = (int *)malloc(DATA[i].len * sizeof(int));

        copy(DATA[i].unsorted, arr, DATA[i].len);
        binary_insertion_sort(arr, DATA[i].len);
        assert_eq(arr, DATA[i].sorted, DATA[i].len);
    }
}

void test_shell_sort(void) {
    printf("test shell_sort\t\t\t");

    for (int i = 0; i < DATA_LEN; i++) {
        int *arr = (int *)malloc(DATA[i].len * sizeof(int));

        copy(DATA[i].unsorted, arr, DATA[i].len);
        shell_sort(arr, DATA[i].len);
        assert_eq(arr, DATA[i].sorted, DATA[i].len);
    }
}

int main(void) {
    test_insertion_sort();
    test_binary_insertion_sort();
    test_shell_sort();

    return 0;
}

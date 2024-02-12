#include "data.h"
#include "insertion.h"
#include "utils.h"
#include <stdio.h>

void test_insertion_sort(void) {
    printf("test_insertion_sort:\t\t");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    insertion_sort(arr, LEN);
    assert_eq(arr, STORED, LEN);
}

void test_binary_insertion_sort(void) {
    printf("test_binary_insertion_sort:\t");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    binary_insertion_sort(arr, LEN);
    assert_eq(arr, STORED, LEN);
}

void test_shell_sort(void) {
    printf("test_shell_sort:\t\t");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    shell_sort(arr, LEN);
    assert_eq(arr, STORED, LEN);
}

int main(void) {
    test_insertion_sort();
    test_binary_insertion_sort();
    test_shell_sort();

    return 0;
}

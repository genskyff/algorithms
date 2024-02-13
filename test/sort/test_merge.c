#include "data.h"
#include "merge.h"
#include "utils.h"
#include <stdio.h>

void test_merge_sort_recu(void) {
    printf("test merge_sort_recu\t\t");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    merge_sort_recu(arr, LEN);
    assert_eq(arr, STORED, LEN);
}

void test_merge_sort_iter(void) {
    printf("test merge_sort_iter\t\t");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    merge_sort_iter(arr, LEN);
    assert_eq(arr, STORED, LEN);
}

int main(void) {
    test_merge_sort_recu();
    test_merge_sort_iter();

    return 0;
}

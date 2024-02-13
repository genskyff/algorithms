#include "data.h"
#include "quick.h"
#include "utils.h"
#include <stdio.h>

void test_quick_sort(void) {
    printf("test quick_sort\t\t\t");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    quick_sort(arr, LEN);
    assert_eq(arr, STORED, LEN);
}

int main(void) {
    test_quick_sort();

    return 0;
}

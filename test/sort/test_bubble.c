#include "bubble.h"
#include "data.h"
#include "utils.h"
#include <stdio.h>

void test_bubble_sort(void) {
    printf("test bubble_sort\t\t");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    bubble_sort(arr, LEN);
    assert_eq(arr, STORED, LEN);
}

void test_cocktail_sort(void) {
    printf("test cocktail_sort\t\t");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    cocktail_sort(arr, LEN);
    assert_eq(arr, STORED, LEN);
}

int main(void) {
    test_bubble_sort();
    test_cocktail_sort();
    return 0;
}

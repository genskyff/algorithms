#include "bubble.h"
#include "data.h"
#include "utils.h"
#include <stdio.h>

void test_bubble_sort(void);
void test_cocktail_sort(void);

int main(void) {
    test_bubble_sort();
    test_cocktail_sort();
    return 0;
}

void test_bubble_sort(void) {
    printf("\n---- test_bubble_sort ----\n");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    bubble_sort(arr, LEN);
    assert_eq(arr, STORED, LEN);
}

void test_cocktail_sort(void) {
    printf("\n---- test_cocktail_sort ----\n");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    cocktail_sort(arr, LEN);
    assert_eq(arr, STORED, LEN);
}

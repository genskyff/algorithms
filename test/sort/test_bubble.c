#include "bubble.h"
#include "data.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void test_bubble_sort(void) {
    printf("test bubble_sort\t\t");

    for (int i = 0; i < DATA_LEN; i++) {
        int *arr = (int *)malloc(DATA[i].len * sizeof(int));

        copy(DATA[i].unsorted, arr, DATA[i].len);
        bubble_sort(arr, DATA[i].len);
        assert_eq(arr, DATA[i].sorted, DATA[i].len);
    }
}

void test_cocktail_sort(void) {
    printf("test cocktail_sort\t\t");

    for (int i = 0; i < DATA_LEN; i++) {
        int *arr = (int *)malloc(DATA[i].len * sizeof(int));

        copy(DATA[i].unsorted, arr, DATA[i].len);
        cocktail_sort(arr, DATA[i].len);
        assert_eq(arr, DATA[i].sorted, DATA[i].len);
    }
}

int main(void) {
    test_bubble_sort();
    test_cocktail_sort();

    return 0;
}

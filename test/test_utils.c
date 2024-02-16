#include "utils.h"
#include <stdio.h>

void test_rotate_left(void) {
    printf("test rotate_left\t\t");

    int arr[]      = {1, 2, 3, 4, 5};
    int expected[] = {3, 4, 5, 1, 2};
    int len        = sizeof(arr) / sizeof(int);

    rotate_left(arr, 0, len, 2);
    assert_eq(arr, expected, 5);
}

void test_rotate_right(void) {
    printf("test rotate_right\t\t");

    int arr[]      = {1, 2, 3, 4, 5};
    int expected[] = {4, 5, 1, 2, 3};
    int len        = sizeof(arr) / sizeof(int);

    rotate_right(arr, 0, len, 2);
    assert_eq(arr, expected, 5);
}

int main(void) {
    test_rotate_left();
    test_rotate_right();

    return 0;
}

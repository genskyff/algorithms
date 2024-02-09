#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

void swap(int *arr, int i, int j) {
    int t  = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

void copy(int *src, int *dest, int len) {
    for (int i = 0; i < len; i++) {
        dest[i] = src[i];
    }
}

void show(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void assert_eq(int *left, int *right, int len) {
    bool flag = true;

    for (int i = 0; i < len; i++) {
        if (left[i] != right[i]) {
            flag = false;
            break;
        }
    }

    if (flag) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
        printf("left:\t");
        show(left, len);
        printf("right:\t");
        show(right, len);
    }
}

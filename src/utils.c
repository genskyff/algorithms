#include "utils.h"
#include <corecrt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *arr, const size_t i, const size_t j) {
    if (i == j) {
        return;
    }

    int t  = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

void copy(const int *src, int *dest, const size_t len) {
    for (int i = 0; i < len; i++) {
        dest[i] = src[i];
    }
}

void rotate_left(int *arr, const size_t begin, const size_t end,
                 const size_t k) {
    if (begin >= end) {
        return;
    }

    int len = end - begin;
    if (len == 0) {
        return;
    }

    int *tmp = (int *)malloc(len * sizeof(int));
    if (tmp == NULL) {
        return;
    }

    int offset = k % len;
    copy(arr + begin, tmp + len - offset, offset);
    copy(arr + begin + offset, tmp, len - offset);
    copy(tmp, arr + begin, len);

    free(tmp);
}

void rotate_right(int *arr, const size_t begin, const size_t end,
                  const size_t n) {
    if (begin >= end) {
        return;
    }

    int len = end - begin;
    if (len == 0) {
        return;
    }

    int *tmp = (int *)malloc(len * sizeof(int));
    if (tmp == NULL) {
        return;
    }

    int offset = n % len;
    copy(arr + end - offset, tmp, offset);
    copy(arr + begin, tmp + offset, len - offset);
    copy(tmp, arr + begin, len);

    free(tmp);
}

void show(const int *arr, const size_t len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

bool _assert_eq(const int *left, const int *right, const size_t len) {
    bool flag = true;

    for (int i = 0; i < len; i++) {
        if (left[i] != right[i]) {
            flag = false;
            break;
        }
    }

    if (flag) {
        return true;
    } else {
        printf("...FAILED\n");
        printf("  |--- left\t");
        show(left, len);
        printf("  |--- right\t");
        show(right, len);
        printf("\n");
        return false;
    }
}

void assert_eq(const int *left, const int *right, const size_t len) {
    // todo
}

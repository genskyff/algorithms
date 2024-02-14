#include "merge.h"
#include <stdlib.h>

#ifdef DEBUG_PRINT
#include "utils.h"
#include <stdio.h>
int LEN;
#endif

void msort_recu(int *arr, int *tmp, int left, int right);
void msort_iter(int *arr, int *tmp, int len);
void merge(int *arr, int *tmp, int left, int mid, int right);

void merge_sort_recu(int *arr, int len) {
#ifdef DEBUG_PRINT
    LEN = len;
    printf("\nbegin:\t");
    show(arr, LEN);
#endif

    if (len < 2) {
        return;
    }

    int *tmp = (int *)malloc(len * sizeof(int));
    msort_recu(arr, tmp, 0, len - 1);
}

void merge_sort_iter(int *arr, int len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len < 2) {
        return;
    }

    int *tmp = (int *)malloc(len * sizeof(int));
    msort_iter(arr, tmp, len);
}

void msort_recu(int *arr, int *tmp, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        msort_recu(arr, tmp, left, mid);
        msort_recu(arr, tmp, mid + 1, right);
        merge(arr, tmp, left, mid, right);
    }
}

void msort_iter(int *arr, int *tmp, int len) {
    int left, mid, right;

    for (int i = 1; i < len; i *= 2) {
        left = 0;
        while (left + i < len) {
            mid   = left + i - 1;
            right = mid + i < len ? mid + i : len - 1;
            merge(arr, tmp, left, mid, right);
            left = right + 1;
        }
    }
}

void merge(int *arr, int *tmp, int left, int mid, int right) {
    int l_pos = left, r_pos = mid + 1, t_pos = left;

    while (l_pos <= mid && r_pos <= right) {
        if (arr[l_pos] < arr[r_pos]) {
            tmp[t_pos++] = arr[l_pos++];
        } else {
            tmp[t_pos++] = arr[r_pos++];
        }
    }

    while (l_pos <= mid) {
        tmp[t_pos++] = arr[l_pos++];
    }

    while (r_pos <= right) {
        tmp[t_pos++] = arr[r_pos++];
    }

    for (int i = left; i < t_pos; i++) {
        arr[i] = tmp[i];
    }

#ifdef DEBUG_PRINT
    printf("next:\t");
    show(arr, LEN);
#endif
}

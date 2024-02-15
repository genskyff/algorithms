#include "merge.h"
#include <stdlib.h>

#ifdef DEBUG_PRINT
#include "utils.h"
#include <stdio.h>
int LEN;
#endif

void msort_recu(int *arr, int *tmp, int lo, int hi);
void msort_iter(int *arr, int *tmp, int len);
void merge(int *arr, int *tmp, int lo, int mid, int hi);

void merge_sort_recu(int *arr, int len) {
#ifdef DEBUG_PRINT
    LEN = len;
    printf("\nbegin:\t");
    show(arr, LEN);
#endif

    if (len == 0) {
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

    if (len == 0) {
        return;
    }

    int *tmp = (int *)malloc(len * sizeof(int));
    msort_iter(arr, tmp, len);
}

void msort_recu(int *arr, int *tmp, int lo, int hi) {
    if (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        msort_recu(arr, tmp, lo, mid);
        msort_recu(arr, tmp, mid + 1, hi);
        merge(arr, tmp, lo, mid, hi);
    }
}

void msort_iter(int *arr, int *tmp, int len) {
    int lo, mid, hi;

    for (int i = 1; i < len; i *= 2) {
        lo = 0;
        while (lo + i < len) {
            mid   = lo + i - 1;
            hi = mid + i < len ? mid + i : len - 1;
            merge(arr, tmp, lo, mid, hi);
            lo = hi + 1;
        }
    }
}

void merge(int *arr, int *tmp, int lo, int mid, int hi) {
    int l_pos = lo, h_pos = mid + 1, t_pos = lo;

    while (l_pos <= mid && h_pos <= hi) {
        if (arr[l_pos] < arr[h_pos]) {
            tmp[t_pos++] = arr[l_pos++];
        } else {
            tmp[t_pos++] = arr[h_pos++];
        }
    }

    while (l_pos <= mid) {
        tmp[t_pos++] = arr[l_pos++];
    }

    while (h_pos <= hi) {
        tmp[t_pos++] = arr[h_pos++];
    }

    for (int i = lo; i < t_pos; i++) {
        arr[i] = tmp[i];
    }

#ifdef DEBUG_PRINT
    printf("next:\t");
    show(arr, LEN);
#endif
}

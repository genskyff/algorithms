#include "merge.h"
#include <stdlib.h>

#ifdef DEBUG_PRINT
#include "utils.h"
#include <stdio.h>
int LEN;
#endif

void msort_recu(int *arr, int *tmp, const size_t low, const size_t high);
void msort_iter(int *arr, int *tmp, const size_t len);
void merge(int *arr, int *tmp, const size_t low, const size_t mid,
           const size_t high);

void merge_sort_recu(int *arr, const size_t len) {
#ifdef DEBUG_PRINT
    LEN = len;
    printf("\nbegin:\t");
    show(arr, LEN);
#endif

    if (len == 0) {
        return;
    }

    int *tmp = (int *)malloc(len * sizeof(int));
    if (tmp == NULL) {
        return;
    }

    msort_recu(arr, tmp, 0, len - 1);
    free(tmp);
}

void merge_sort_iter(int *arr, const size_t len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len == 0) {
        return;
    }

    int *tmp = (int *)malloc(len * sizeof(int));
    if (tmp == NULL) {
        return;
    }

    msort_iter(arr, tmp, len);
    free(tmp);
}

void msort_recu(int *arr, int *tmp, const size_t low, const size_t high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        msort_recu(arr, tmp, low, mid);
        msort_recu(arr, tmp, mid + 1, high);
        merge(arr, tmp, low, mid, high);
    }
}

void msort_iter(int *arr, int *tmp, const size_t len) {
    int low, mid, high;

    for (int i = 1; i < len; i *= 2) {
        low = 0;
        while (low + i < len) {
            mid  = low + i - 1;
            high = mid + i < len ? mid + i : len - 1;
            merge(arr, tmp, low, mid, high);
            low = high + 1;
        }
    }
}

void merge(int *arr, int *tmp, const size_t low, const size_t mid,
           const size_t high) {
    int l_pos = low, h_pos = mid + 1, t_pos = low;

    while (l_pos <= mid && h_pos <= high) {
        if (arr[l_pos] < arr[h_pos]) {
            tmp[t_pos++] = arr[l_pos++];
        } else {
            tmp[t_pos++] = arr[h_pos++];
        }
    }

    while (l_pos <= mid) {
        tmp[t_pos++] = arr[l_pos++];
    }

    while (h_pos <= high) {
        tmp[t_pos++] = arr[h_pos++];
    }

    for (int i = low; i < t_pos; i++) {
        arr[i] = tmp[i];
    }

#ifdef DEBUG_PRINT
    printf("next:\t");
    show(arr, LEN);
#endif
}

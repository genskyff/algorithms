#include "quick.h"
#include "utils.h"

#ifdef DEBUG_PRINT
#include <stdio.h>
int LEN;
#endif

void qsort(int *arr, int lo, int hi);
int  partition(int *arr, int lo, int hi);
void move_pivot_to_hi(int *arr, int lo, int hi);

void quick_sort(int *arr, int len) {
#ifdef DEBUG_PRINT
    LEN = len;
    printf("\nbegin:\t");
    show(arr, LEN);
#endif

    if (len < 2) {
        return;
    }

    qsort(arr, 0, len - 1);
}

void qsort(int *arr, int lo, int hi) {
    while (lo < hi) {
        int pivot = partition(arr, lo, hi);

        if (pivot - lo < hi - pivot) {
            if (pivot > 0) {
                qsort(arr, lo, pivot - 1);
            }
            lo = pivot + 1;
        } else {
            qsort(arr, pivot + 1, hi);
            hi = pivot - 1;
        }

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, LEN);
#endif
    }
}

int partition(int *arr, int lo, int hi) {
    move_pivot_to_hi(arr, lo, hi);
    int pivot = arr[hi];
    int tail  = lo;

    for (int i = lo; i < hi; i++) {
        if (arr[i] < pivot) {
            swap(arr, i, tail);
            tail++;
        }
    }
    swap(arr, tail, hi);

    return tail;
}

void move_pivot_to_hi(int *arr, int lo, int hi) {
    int mid = lo + (hi - lo) / 2;

    if ((arr[lo] < arr[mid]) ^ (arr[lo] < arr[hi])) {
        swap(arr, lo, hi);
    } else if ((arr[mid] < arr[lo]) ^ (arr[mid] < arr[hi])) {
        swap(arr, mid, hi);
    }
}

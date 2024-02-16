#include "quick.h"
#include "utils.h"

#ifdef DEBUG_PRINT
#include <stdio.h>
int LEN;
#endif

void qsort(int *arr, size_t low, size_t high);
int  partition(int *arr, const size_t low, const size_t high);
void move_pivot_to_high(int *arr, const size_t low, const size_t high);

void quick_sort(int *arr, const size_t len) {
#ifdef DEBUG_PRINT
    LEN = len;
    printf("\nbegin:\t");
    show(arr, LEN);
#endif

    if (len == 0) {
        return;
    }

    qsort(arr, 0, len - 1);
}

void qsort(int *arr, size_t low, size_t high) {
    while (low < high) {
        int pivot = partition(arr, low, high);

        if (pivot - low < high - pivot) {
            if (pivot > 0) {
                qsort(arr, low, pivot - 1);
            }
            low = pivot + 1;
        } else {
            qsort(arr, pivot + 1, high);
            high = pivot - 1;
        }

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, LEN);
#endif
    }
}

int partition(int *arr, const size_t low, const size_t high) {
    move_pivot_to_high(arr, low, high);
    int pivot = arr[high];
    int cur   = low;

    for (int i = low; i < high; i++) {
        if (arr[i] < pivot) {
            swap(arr, i, cur);
            cur++;
        }
    }
    swap(arr, cur, high);

    return cur;
}

void move_pivot_to_high(int *arr, const size_t low, const size_t high) {
    int mid   = low + (high - low) / 2;
    int pivot = high;

    if ((arr[low] < arr[mid]) ^ (arr[low] < arr[high])) {
        pivot = low;
    } else if ((arr[mid] < arr[low]) ^ (arr[mid] < arr[high])) {
        pivot = mid;
    }

    swap(arr, pivot, high);
}

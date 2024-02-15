#include "quick.h"
#include "utils.h"

#ifdef DEBUG_PRINT
#include <stdio.h>
int LEN;
#endif

void qsort(int *arr, int low, int high);
int  partition(int *arr, int low, int high);
void move_pivot_to_hi(int *arr, int low, int high);

void quick_sort(int *arr, int len) {
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

void qsort(int *arr, int low, int high) {
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

int partition(int *arr, int low, int high) {
    move_pivot_to_hi(arr, low, high);
    int pivot = arr[high];
    int tail  = low;

    for (int i = low; i < high; i++) {
        if (arr[i] < pivot) {
            swap(arr, i, tail);
            tail++;
        }
    }
    swap(arr, tail, high);

    return tail;
}

void move_pivot_to_hi(int *arr, int low, int high) {
    int mid = low + (high - low) / 2;

    if ((arr[low] < arr[mid]) ^ (arr[low] < arr[high])) {
        swap(arr, low, high);
    } else if ((arr[mid] < arr[low]) ^ (arr[mid] < arr[high])) {
        swap(arr, mid, high);
    }
}

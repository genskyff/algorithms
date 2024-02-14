#include "quick.h"
#include "utils.h"

#ifdef DEBUG_PRINT
#include <stdio.h>
int LEN;
#endif

void qsort(int *arr, int left, int right);
int  partition(int *arr, int left, int right);
void move_pivot_to_right(int *arr, int left, int right);

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

void qsort(int *arr, int left, int right) {
    while (left < right) {
        int pivot = partition(arr, left, right);

        if (pivot - left < right - pivot) {
            if (pivot >= 1) {
                qsort(arr, left, pivot - 1);
            }
            left = pivot + 1;
        } else {
            qsort(arr, pivot + 1, right);
            right = pivot - 1;
        }

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, LEN);
#endif
    }
}

int partition(int *arr, int left, int right) {
    move_pivot_to_right(arr, left, right);
    int pivot = arr[right];
    int tail  = left;

    for (int i = left; i < right; i++) {
        if (arr[i] < pivot) {
            swap(arr, i, tail);
            tail++;
        }
    }
    swap(arr, tail, right);

    return tail;
}

void move_pivot_to_right(int *arr, int left, int right) {
    int mid = left + (right - left) / 2;

    if ((arr[left] < arr[mid]) ^ (arr[left] < arr[right])) {
        swap(arr, left, right);
    } else if ((arr[mid] < arr[left]) ^ (arr[mid] < arr[right])) {
        swap(arr, mid, right);
    }
}

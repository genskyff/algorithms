#include "insertion.h"

#ifdef DEBUG_PRINT
#include "utils.h"
#include <stdio.h>
#endif

void insertion_sort(int *arr, int len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len == 0) {
        return;
    }

    for (int i = 1; i < len; i++) {
        int base = arr[i];
        int j    = i;

        while (j > 0 && arr[j - 1] > base) {
            arr[j] = arr[j - 1];
            j--;
        }

        arr[j] = base;

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, len);
#endif
    }
}

void binary_insertion_sort(int *arr, int len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len == 0) {
        return;
    }

    for (int i = 1; i < len; i++) {
        int base  = arr[i];
        int lo  = 0;
        int hi = i;

        while (lo < hi) {
            int mid = (lo + hi) / 2;

            if (arr[mid] > base) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        for (int j = i - 1; j >= lo; j--) {
            arr[j + 1] = arr[j];
        }

        arr[lo] = base;

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, len);
#endif
    }
}

void shell_sort(int *arr, int len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len == 0) {
        return;
    }

    int gap = 1;

    while (gap < len / 3) {
        gap = gap * 3 + 1;
    }

    while (gap >= 1) {
        for (int i = gap; i < len; i++) {
            int base = arr[i];
            int j    = i;

            while (j >= gap && arr[j - gap] > base) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = base;
        }

        gap = (gap - 1) / 3;

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, len);
#endif
    }
}

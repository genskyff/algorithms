#include "insertion.h"
#include "utils.h"

#ifdef DEBUG_PRINT
#include <stdio.h>
#endif

void insertion_sort(int *arr, const size_t len) {
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

void binary_insertion_sort(int *arr, const size_t len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len == 0) {
        return;
    }

    for (int i = 1; i < len; i++) {
        int base = arr[i];
        int low  = 0;
        int high = i;

        while (low < high) {
            int mid = (low + high) / 2;

            if (arr[mid] > base) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        rotate_right(arr, low, i + 1, 1);
        arr[low] = base;

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, len);
#endif
    }
}

void shell_sort(int *arr, const size_t len) {
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

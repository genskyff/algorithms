#include "bubble.h"
#include "utils.h"
#include <stdbool.h>

#ifdef DEBUG_PRINT
#include <stdio.h>
#endif

void bubble_sort(int *arr, int len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len < 2) {
        return;
    }

    for (int i = 0; i < len; i++) {
        bool swapped = false;

        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
                swapped = true;
            }
        }

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, len);
#endif

        if (!swapped) {
            break;
        }
    }
}

void cocktail_sort(int *arr, int len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len < 2) {
        return;
    }

    int lo  = 0;
    int hi = len - 1;

    while (lo < hi) {
        bool swapped = false;

        for (int i = lo; i < hi; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr, i, i + 1);
                swapped = true;
            }
        }

        if (!swapped) {
#ifdef DEBUG_PRINT
            printf("next:\t");
            show(arr, len);
#endif
            break;
        }

        hi--;
        swapped = false;

        for (int i = hi; i > lo; i--) {
            if (arr[i] < arr[i - 1]) {
                swap(arr, i, i - 1);
                swapped = true;
            }
        }

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, len);
#endif

        if (!swapped) {
            break;
        }

        lo++;
    }
}

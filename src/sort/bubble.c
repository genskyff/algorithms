#include "bubble.h"
#include "utils.h"
#include <stdbool.h>

#ifdef DEBUG_PRINT
#include <stdio.h>
#endif

void bubble_sort(int *arr, const size_t len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

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

void cocktail_sort(int *arr, const size_t len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len == 0) {
        return;
    }

    int low  = 0;
    int high = len - 1;

    while (low < high) {
        bool swapped = false;

        for (int i = low; i < high; i++) {
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

        high--;
        swapped = false;

        for (int i = high; i > low; i--) {
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

        low++;
    }
}

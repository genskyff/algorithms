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
        bool flag = false;

        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
                flag = true;
            }
        }

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, len);
#endif

        if (!flag) {
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

    int left = 0;
    int right   = len - 1;

    while (left < right) {
        bool flag = false;

        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr, i, i + 1);
                flag = true;
            }
        }

        if (!flag) {
#ifdef DEBUG_PRINT
            printf("next:\t");
            show(arr, len);
#endif
            break;
        }

        right--;
        flag = false;

        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                swap(arr, i, i - 1);
                flag = true;
            }
        }

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, len);
#endif

        if (!flag) {
            break;
        }

        left++;
    }
}

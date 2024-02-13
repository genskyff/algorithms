#include "selection.h"
#include "utils.h"

#ifdef DEBUG_PRINT
#include <stdio.h>
#endif

void selection_sort(int *arr, int len) {
#ifdef DEBUG_PRINT
    printf("\nbefore:\t");
    show(arr, len);
#endif

    if (len < 2) {
        return;
    }

    for (int i = 0; i < len - 1; i++) {
        int min = i;

        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        if (i != min) {
            swap(arr, i, min);
        }

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, len);
#endif
    }
}

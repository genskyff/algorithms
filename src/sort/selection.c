#include "selection.h"
#include "utils.h"

#ifdef DEBUG_PRINT
#include <stdio.h>
#endif

void selection_sort(int *arr, int len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len == 0) {
        return;
    }

    for (int i = 0; i < len - 1; i++) {
        int min = i;

        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        swap(arr, i, min);

#ifdef DEBUG_PRINT
        printf("next:\t");
        show(arr, len);
#endif
    }
}

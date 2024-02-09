#include "selection.h"
#include "utils.h"
#include <stdbool.h>

void selection_sort(int *arr, int len) {
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
    }
}

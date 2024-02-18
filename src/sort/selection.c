#include "selection.h"

void selection_sort(Array *arr) {
    if (arr->len == 0) {
        return;
    }

    for (size_t i = 0; i < arr->len - 1; i++) {
        size_t min = i;

        for (size_t j = i + 1; j < arr->len; j++) {
            if (arr->data[j] < arr->data[min]) {
                min = j;
            }
        }

        array_swap(arr, i, min);
    }
}

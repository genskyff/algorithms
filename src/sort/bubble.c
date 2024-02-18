#include "bubble.h"
#include <stdbool.h>

void bubble_sort(Array *arr) {
    for (size_t i = 0; i < arr->len; i++) {
        bool is_swapped = false;

        for (size_t j = 0; j < arr->len - i - 1; j++) {
            if (arr->data[j] > arr->data[j + 1]) {
                swap(arr, j, j + 1);
                is_swapped = true;
            }
        }

        if (!is_swapped) {
            break;
        }
    }
}

void cocktail_sort(Array *arr) {
    if (arr->len == 0) {
        return;
    }

    size_t low  = 0;
    size_t high = arr->len - 1;

    while (low < high) {
        bool is_swapped = false;

        for (size_t i = low; i < high; i++) {
            if (arr->data[i] > arr->data[i + 1]) {
                swap(arr, i, i + 1);
                is_swapped = true;
            }
        }

        if (!is_swapped) {
            break;
        }

        high--;
        is_swapped = false;

        for (size_t i = high; i > low; i--) {
            if (arr->data[i] < arr->data[i - 1]) {
                swap(arr, i, i - 1);
                is_swapped = true;
            }
        }

        if (!is_swapped) {
            break;
        }

        low++;
    }
}

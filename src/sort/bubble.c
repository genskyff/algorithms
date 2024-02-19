#include "bubble.h"
#include "utils.h"
#include <stdbool.h>

void bubble_sort(elem_t *arr, size_t len) {
    for (size_t i = 0; i < len; i++) {
        bool is_swapped = false;

        for (size_t j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
                is_swapped = true;
            }
        }

        if (!is_swapped) {
            break;
        }
    }
}

void cocktail_sort(elem_t *arr, size_t len) {
    if (len == 0) {
        return;
    }

    size_t low  = 0;
    size_t high = len - 1;

    while (low < high) {
        bool is_swapped = false;

        for (size_t i = low; i < high; i++) {
            if (arr[i] > arr[i + 1]) {
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
            if (arr[i] < arr[i - 1]) {
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

#include "insertion.h"

void insertion_sort(Array *arr) {
    for (size_t i = 1; i < arr->len; i++) {
        elem_t base = arr->data[i];
        size_t j    = i;

        while (j > 0 && arr->data[j - 1] > base) {
            arr->data[j] = arr->data[j - 1];
            j--;
        }

        arr->data[j] = base;
    }
}

void binary_insertion_sort(Array *arr) {
    for (size_t i = 1; i < arr->len; i++) {
        elem_t base = arr->data[i];
        size_t low  = 0;
        size_t high = i;

        while (low < high) {
            size_t mid = (low + high) / 2;

            if (arr->data[mid] > base) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        array_rotate_right_slice(arr, low, i + 1, 1);
        arr->data[low] = base;
    }
}

void shell_sort(Array *arr) {
    size_t gap = 1;

    while (gap < arr->len / 3) {
        gap = gap * 3 + 1;
    }

    while (gap >= 1) {
        for (size_t i = gap; i < arr->len; i++) {
            elem_t base = arr->data[i];
            size_t j    = i;

            while (j >= gap && arr->data[j - gap] > base) {
                arr->data[j] = arr->data[j - gap];
                j -= gap;
            }

            arr->data[j] = base;
        }

        gap = (gap - 1) / 3;
    }
}

#include "alg/sort/insertion.h"
#include "internal/utils.h"

void alg_insertion_sort(alg_elem_t *arr, size_t len) {
    for (size_t i = 1; i < len; i++) {
        alg_elem_t base = arr[i];
        size_t     j    = i;

        while (j > 0 && arr[j - 1] > base) {
            arr[j] = arr[j - 1];
            j--;
        }

        arr[j] = base;
    }
}

void alg_binary_insertion_sort(alg_elem_t *arr, size_t len) {
    for (size_t i = 1; i < len; i++) {
        alg_elem_t base = arr[i];
        size_t     low  = 0;
        size_t     high = i;

        while (low < high) {
            size_t mid = low + (high - low) / 2;

            if (arr[mid] > base) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        alg_internal_rotate_right_slice(arr, len, low, i + 1, 1);
        arr[low] = base;
    }
}

void alg_shell_sort(alg_elem_t *arr, size_t len) {
    size_t gap = 1;

    while (gap < len / 3) {
        gap = gap * 3 + 1;
    }

    while (gap >= 1) {
        for (size_t i = gap; i < len; i++) {
            alg_elem_t base = arr[i];
            size_t     j    = i;

            while (j >= gap && arr[j - gap] > base) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = base;
        }

        gap = (gap - 1) / 3;
    }
}

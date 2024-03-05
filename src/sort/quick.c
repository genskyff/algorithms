#include "quick.h"
#include "util.h"

void _move_pivot_to_high(elem_t *arr, size_t low, size_t high) {
    size_t mid   = low + (high - low) / 2;
    size_t pivot = high;

    if ((arr[low] < arr[mid]) ^ (arr[low] < arr[high])) {
        pivot = low;
    } else if ((arr[mid] < arr[low]) ^ (arr[mid] < arr[high])) {
        pivot = mid;
    }

    _swap(arr, pivot, high);
}

size_t _partition(elem_t *arr, size_t low, size_t high) {
    _move_pivot_to_high(arr, low, high);
    elem_t pivot = arr[high];
    size_t cur   = low;

    for (size_t i = low; i < high; i++) {
        if (arr[i] < pivot) {
            _swap(arr, i, cur);
            cur++;
        }
    }
    _swap(arr, cur, high);

    return cur;
}

void _qsort(elem_t *arr, size_t low, size_t high) {
    while (low < high) {
        size_t pivot = _partition(arr, low, high);

        if (pivot - low < high - pivot) {
            if (pivot > 0) {
                _qsort(arr, low, pivot - 1);
            }
            low = pivot + 1;
        } else {
            _qsort(arr, pivot + 1, high);
            high = pivot - 1;
        }
    }
}

void quick_sort(elem_t *arr, size_t len) {

    if (len == 0) {
        return;
    }

    _qsort(arr, 0, len - 1);
}

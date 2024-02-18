#include "quick.h"
#include "utils.h"

void   qsort(Array *arr, size_t low, size_t high);
size_t partition(Array *arr, size_t low, size_t high);
void   move_pivot_to_high(Array *arr, size_t low, size_t high);

void quick_sort(Array *arr) {

    if (arr->len == 0) {
        return;
    }

    qsort(arr, 0, arr->len - 1);
}

void qsort(Array *arr, size_t low, size_t high) {
    while (low < high) {
        size_t pivot = partition(arr, low, high);

        if (pivot - low < high - pivot) {
            if (pivot > 0) {
                qsort(arr, low, pivot - 1);
            }
            low = pivot + 1;
        } else {
            qsort(arr, pivot + 1, high);
            high = pivot - 1;
        }
    }
}

size_t partition(Array *arr, size_t low, size_t high) {
    move_pivot_to_high(arr, low, high);
    elem_t pivot = arr->data[high];
    size_t cur   = low;

    for (size_t i = low; i < high; i++) {
        if (arr->data[i] < pivot) {
            swap(arr, i, cur);
            cur++;
        }
    }
    swap(arr, cur, high);

    return cur;
}

void move_pivot_to_high(Array *arr, size_t low, size_t high) {
    size_t mid   = low + (high - low) / 2;
    size_t pivot = high;

    if ((arr->data[low] < arr->data[mid]) ^
        (arr->data[low] < arr->data[high])) {
        pivot = low;
    } else if ((arr->data[mid] < arr->data[low]) ^
               (arr->data[mid] < arr->data[high])) {
        pivot = mid;
    }

    swap(arr, pivot, high);
}

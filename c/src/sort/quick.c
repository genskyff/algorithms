#include "alg/sort/quick.h"
#include "internal/utils.h"

static void quick_move_pivot_to_high(alg_elem_t *arr, size_t low, size_t high);
static size_t quick_partition(alg_elem_t *arr, size_t low, size_t high);
static void   quick_sort_range(alg_elem_t *arr, size_t low, size_t high);

static void quick_move_pivot_to_high(alg_elem_t *arr, size_t low, size_t high) {
    size_t mid   = low + (high - low) / 2;
    size_t pivot = high;

    if ((arr[low] < arr[mid]) ^ (arr[low] < arr[high])) {
        pivot = low;
    } else if ((arr[mid] < arr[low]) ^ (arr[mid] < arr[high])) {
        pivot = mid;
    }

    alg_internal_swap(arr, pivot, high);
}

static size_t quick_partition(alg_elem_t *arr, size_t low, size_t high) {
    quick_move_pivot_to_high(arr, low, high);
    alg_elem_t pivot = arr[high];
    size_t     cur   = low;

    for (size_t i = low; i < high; i++) {
        if (arr[i] < pivot) {
            alg_internal_swap(arr, i, cur);
            cur++;
        }
    }
    alg_internal_swap(arr, cur, high);

    return cur;
}

static void quick_sort_range(alg_elem_t *arr, size_t low, size_t high) {
    while (low < high) {
        size_t pivot = quick_partition(arr, low, high);

        if (pivot - low < high - pivot) {
            if (pivot > 0) {
                quick_sort_range(arr, low, pivot - 1);
            }
            low = pivot + 1;
        } else {
            quick_sort_range(arr, pivot + 1, high);
            high = pivot - 1;
        }
    }
}

void alg_quick_sort(alg_elem_t *arr, size_t len) {
    if (len == 0) {
        return;
    }

    quick_sort_range(arr, 0, len - 1);
}

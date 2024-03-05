#include "selection.h"
#include "util.h"

void selection_sort(elem_t *arr, size_t len) {
    if (len == 0) {
        return;
    }

    for (size_t i = 0; i < len - 1; i++) {
        size_t min = i;

        for (size_t j = i + 1; j < len; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        _swap(arr, i, min);
    }
}

#include "merge.h"
#include <stdlib.h>

void _merge(elem_t *arr, elem_t *tmp, size_t low, size_t mid, size_t high);
void _msort_iter(elem_t *arr, elem_t *tmp, size_t len);
void _msort_recu(elem_t *arr, elem_t *tmp, size_t low, size_t high);

void _merge(elem_t *arr, elem_t *tmp, size_t low, size_t mid, size_t high) {
    size_t l_pos = low;
    size_t h_pos = mid + 1;
    size_t t_pos = low;

    while (l_pos <= mid && h_pos <= high) {
        if (arr[l_pos] < arr[h_pos]) {
            tmp[t_pos++] = arr[l_pos++];
        } else {
            tmp[t_pos++] = arr[h_pos++];
        }
    }

    while (l_pos <= mid) {
        tmp[t_pos++] = arr[l_pos++];
    }

    while (h_pos <= high) {
        tmp[t_pos++] = arr[h_pos++];
    }

    for (size_t i = low; i < t_pos; i++) {
        arr[i] = tmp[i];
    }
}

void _msort_iter(elem_t *arr, elem_t *tmp, size_t len) {
    size_t low, mid, high;

    for (size_t i = 1; i < len; i *= 2) {
        low = 0;
        while (low + i < len) {
            mid  = low + i - 1;
            high = mid + i < len ? mid + i : len - 1;
            _merge(arr, tmp, low, mid, high);
            low = high + 1;
        }
    }
}

void _msort_recu(elem_t *arr, elem_t *tmp, size_t low, size_t high) {
    if (low < high) {
        size_t mid = low + (high - low) / 2;

        _msort_recu(arr, tmp, low, mid);
        _msort_recu(arr, tmp, mid + 1, high);
        _merge(arr, tmp, low, mid, high);
    }
}

void merge_sort_recu(elem_t *arr, size_t len) {
    if (len < 2) {
        return;
    }

    elem_t *tmp = (elem_t *)malloc(len * sizeof(elem_t));
    if (tmp == NULL) {
        return;
    }

    _msort_recu(arr, tmp, 0, len - 1);
    free(tmp);
}

void merge_sort_iter(elem_t *arr, size_t len) {
    if (len < 2) {
        return;
    }

    elem_t *tmp = (elem_t *)malloc(len * sizeof(elem_t));
    if (tmp == NULL) {
        return;
    }

    _msort_iter(arr, tmp, len);
    free(tmp);
}

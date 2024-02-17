#include "merge.h"
#include <stdlib.h>

void msort_recu(const Array *arr, const Array *tmp, const size_t low,
                const size_t high);
void msort_iter(const Array *arr, const Array *tmp);
void merge(const Array *arr, const Array *tmp, const size_t low,
           const size_t mid, const size_t high);

void merge_sort_recu(const Array *arr) {
    if (arr->len < 2) {
        return;
    }

    elem_t *data = (elem_t *)malloc(arr->len * sizeof(elem_t));
    if (data == NULL) {
        return;
    }
    Array tmp = {data, arr->len};
    msort_recu(arr, &tmp, 0, arr->len - 1);
    free(data);
}

void merge_sort_iter(const Array *arr) {
    if (arr->len < 2) {
        return;
    }

    elem_t *data = (elem_t *)malloc(arr->len * sizeof(elem_t));
    if (data == NULL) {
        return;
    }
    Array tmp = {data, arr->len};
    msort_iter(arr, &tmp);
    free(data);
}

void msort_recu(const Array *arr, const Array *tmp, const size_t low,
                const size_t high) {
    if (low < high) {
        size_t mid = low + (high - low) / 2;

        msort_recu(arr, tmp, low, mid);
        msort_recu(arr, tmp, mid + 1, high);
        merge(arr, tmp, low, mid, high);
    }
}

void msort_iter(const Array *arr, const Array *tmp) {
    size_t low, mid, high;

    for (size_t i = 1; i < arr->len; i *= 2) {
        low = 0;
        while (low + i < arr->len) {
            mid  = low + i - 1;
            high = mid + i < arr->len ? mid + i : arr->len - 1;
            merge(arr, tmp, low, mid, high);
            low = high + 1;
        }
    }
}

void merge(const Array *arr, const Array *tmp, const size_t low,
           const size_t mid, const size_t high) {
    size_t l_pos = low, h_pos = mid + 1, t_pos = low;

    while (l_pos <= mid && h_pos <= high) {
        if (arr->data[l_pos] < arr->data[h_pos]) {
            tmp->data[t_pos++] = arr->data[l_pos++];
        } else {
            tmp->data[t_pos++] = arr->data[h_pos++];
        }
    }

    while (l_pos <= mid) {
        tmp->data[t_pos++] = arr->data[l_pos++];
    }

    while (h_pos <= high) {
        tmp->data[t_pos++] = arr->data[h_pos++];
    }

    for (size_t i = low; i < t_pos; i++) {
        arr->data[i] = tmp->data[i];
    }
}

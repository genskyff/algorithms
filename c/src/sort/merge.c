#include "alg/sort/merge.h"
#include <stdlib.h>

static void merge_ranges(alg_elem_t *arr, alg_elem_t *tmp, size_t low,
                         size_t mid, size_t high);
static void merge_sort_iter_impl(alg_elem_t *arr, alg_elem_t *tmp, size_t len);
static void merge_sort_recu_impl(alg_elem_t *arr, alg_elem_t *tmp, size_t low,
                                 size_t high);

static void merge_ranges(alg_elem_t *arr, alg_elem_t *tmp, size_t low,
                         size_t mid, size_t high) {
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

static void merge_sort_iter_impl(alg_elem_t *arr, alg_elem_t *tmp, size_t len) {
    size_t low, mid, high;

    for (size_t i = 1; i < len; i *= 2) {
        low = 0;
        while (low + i < len) {
            mid  = low + i - 1;
            high = mid + i < len ? mid + i : len - 1;
            merge_ranges(arr, tmp, low, mid, high);
            low = high + 1;
        }
    }
}

static void merge_sort_recu_impl(alg_elem_t *arr, alg_elem_t *tmp, size_t low,
                                 size_t high) {
    if (low < high) {
        size_t mid = low + (high - low) / 2;

        merge_sort_recu_impl(arr, tmp, low, mid);
        merge_sort_recu_impl(arr, tmp, mid + 1, high);
        merge_ranges(arr, tmp, low, mid, high);
    }
}

void alg_merge_sort_recu(alg_elem_t *arr, size_t len) {
    if (len < 2) {
        return;
    }

    alg_elem_t *tmp = (alg_elem_t *)malloc(len * sizeof(alg_elem_t));
    if (tmp == NULL) {
        return;
    }

    merge_sort_recu_impl(arr, tmp, 0, len - 1);
    free(tmp);
}

void alg_merge_sort_iter(alg_elem_t *arr, size_t len) {
    if (len < 2) {
        return;
    }

    alg_elem_t *tmp = (alg_elem_t *)malloc(len * sizeof(alg_elem_t));
    if (tmp == NULL) {
        return;
    }

    merge_sort_iter_impl(arr, tmp, len);
    free(tmp);
}

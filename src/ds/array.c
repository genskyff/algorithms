#include "array.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(Array *arr, size_t i, size_t j) {
    if (i == j || i >= arr->len || j >= arr->len) {
        return;
    }

    elem_t tmp   = arr->data[i];
    arr->data[i] = arr->data[j];
    arr->data[j] = tmp;
}

void show(Array arr) {
    for (size_t i = 0; i < arr.len; i++) {
        printf("%d ", arr.data[i]);
    }
    printf("\n");
}

void show_slice(Array arr, size_t begin, size_t end) {
    if (begin >= end || begin >= arr.len) {
        return;
    }

    for (size_t i = begin; i < MIN(end, arr.len); i++) {
        printf("%d ", arr.data[i]);
    }
    printf("\n");
}

void copy(Array *dst, Array *src) {
    memcpy(dst->data, src->data, MIN(dst->len, src->len) * sizeof(elem_t));
}

void copy_slice(Array *dst, size_t d_begin, size_t d_end, Array *src,
                size_t s_begin, size_t s_end) {
    if (d_begin >= d_end || d_begin >= dst->len || s_begin >= s_end ||
        s_begin >= src->len) {
        return;
    }

    size_t len = MIN(d_end - d_begin, s_end - s_begin);
    memcpy(dst->data + d_begin, src->data + s_begin, len * sizeof(elem_t));
}

void rotate_left(Array *arr, size_t n) {
    size_t k = n % arr->len;

    if (k == 0) {
        return;
    }

    elem_t *tmp = (elem_t *)malloc(k * sizeof(elem_t));
    memcpy(tmp, arr->data, k * sizeof(elem_t));
    memmove(arr->data, arr->data + k, (arr->len - k) * sizeof(elem_t));
    memcpy(arr->data + arr->len - k, tmp, k * sizeof(elem_t));
    free(tmp);
}

void rotate_left_slice(Array *arr, size_t begin, size_t end, size_t n) {
    if (begin >= end || begin >= arr->len) {
        return;
    }

    size_t k = n % (end - begin);

    if (k == 0) {
        return;
    }

    elem_t *tmp = (elem_t *)malloc(k * sizeof(elem_t));
    memcpy(tmp, arr->data + begin, k * sizeof(elem_t));
    memmove(arr->data + begin, arr->data + begin + k,
            (end - begin - k) * sizeof(elem_t));
    memcpy(arr->data + end - k, tmp, k * sizeof(elem_t));
    free(tmp);
}

void rotate_right(Array *arr, size_t n) {
    size_t k = n % arr->len;

    if (k == 0) {
        return;
    }

    elem_t *tmp = (elem_t *)malloc(k * sizeof(elem_t));
    memcpy(tmp, arr->data + arr->len - k, k * sizeof(elem_t));
    memmove(arr->data + k, arr->data, (arr->len - k) * sizeof(elem_t));
    memcpy(arr->data, tmp, k * sizeof(elem_t));
    free(tmp);
}

void rotate_right_slice(Array *arr, size_t begin, size_t end, size_t n) {
    if (begin >= end || begin >= arr->len) {
        return;
    }

    size_t k = n % (end - begin);

    if (k == 0) {
        return;
    }

    elem_t *tmp = (elem_t *)malloc(k * sizeof(elem_t));
    memcpy(tmp, arr->data + end - k, k * sizeof(elem_t));
    memmove(arr->data + begin + k, arr->data + begin,
            (end - begin - k) * sizeof(elem_t));
    memcpy(arr->data + begin, tmp, k * sizeof(elem_t));
    free(tmp);
}

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(elem_t *arr, size_t i, size_t j) {
    if (i == j) {
        return;
    }

    elem_t tmp = arr[i];
    arr[i]     = arr[j];
    arr[j]     = tmp;
}

void show(FILE *stream, elem_t *arr, size_t len) {
    if (len == 0) {
        return;
    }

    if (stream == NULL) {
        stream = stdout;
    }

    for (size_t i = 0; i < len; i++) {
        fprintf(stream, "%d ", arr[i]);
    }
    fprintf(stream, "\n");
}

void show_slice(FILE *stream, elem_t *arr, size_t len, size_t start,
                size_t end) {
    end = MIN(len, end);
    if (start >= end) {
        return;
    }

    show(stream, arr + start, end - start);
}

void copy(elem_t *dst, size_t d_len, elem_t *src, size_t s_len) {
    memmove(dst, src, MIN(d_len, s_len) * sizeof(elem_t));
}

void copy_slice(elem_t *dst, size_t d_len, size_t d_start, size_t d_end,
                elem_t *src, size_t s_len, size_t s_start, size_t s_end) {
    d_end = MIN(d_len, d_end);
    s_end = MIN(s_len, s_end);
    if (d_start >= d_end || s_start >= s_end) {
        return;
    }

    size_t len = MIN(d_end - d_start, s_end - s_start);
    copy(dst + d_start, len, src + s_start, len);
}

void move_left(elem_t *arr, size_t len, size_t n) {
    if (n == 0 || len <= 1) {
        return;
    }

    n = MIN(len, n);
    memmove(arr, arr + n, (len - n) * sizeof(elem_t));
}

void move_left_slice(elem_t *arr, size_t len, size_t start, size_t end,
                     size_t n) {
    end = MIN(len, end);
    if (start >= end) {
        return;
    }

    n = MIN(len, n);
    move_left(arr + start, end - start, n);
}

void move_right(elem_t *arr, size_t len, size_t n) {
    if (n == 0 || len <= 1) {
        return;
    }

    n = MIN(len, n);
    memmove(arr + n, arr, (len - n) * sizeof(elem_t));
}

void move_right_slice(elem_t *arr, size_t len, size_t start, size_t end,
                      size_t n) {
    end = MIN(len, end);
    if (start >= end) {
        return;
    }

    n = MIN(len, n);
    move_right(arr + start, end - start, n);
}

void rotate_left(elem_t *arr, size_t len, size_t n) {
    if (len == 0 || n % len == 0) {
        return;
    }

    n = n % len;

    elem_t *tmp = (elem_t *)malloc(n * sizeof(elem_t));
    memmove(tmp, arr, n * sizeof(elem_t));
    memmove(arr, arr + n, (len - n) * sizeof(elem_t));
    memmove(arr + len - n, tmp, n * sizeof(elem_t));
    free(tmp);
}

void rotate_left_slice(elem_t *arr, size_t len, size_t start, size_t end,
                       size_t n) {
    end = MIN(len, end);
    if (start >= end || n % (end - start) == 0) {
        return;
    }

    n = n % (end - start);
    rotate_left(arr + start, end - start, n);
}

void rotate_right(elem_t *arr, size_t len, size_t n) {
    if (len == 0 || n % len == 0) {
        return;
    }

    n = n % len;

    elem_t *tmp = (elem_t *)malloc(n * sizeof(elem_t));
    memmove(tmp, arr + len - n, n * sizeof(elem_t));
    memmove(arr + n, arr, (len - n) * sizeof(elem_t));
    memmove(arr, tmp, n * sizeof(elem_t));
    free(tmp);
}

void rotate_right_slice(elem_t *arr, size_t len, size_t start, size_t end,
                        size_t n) {
    end = MIN(len, end);
    if (start >= end || n % (end - start) == 0) {
        return;
    }

    n = n % (end - start);
    rotate_right(arr + start, end - start, n);
}

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _swap(elem_t *arr, size_t i, size_t j) {
    if (arr == NULL || i == j) {
        return;
    }

    elem_t tmp = arr[i];
    arr[i]     = arr[j];
    arr[j]     = tmp;
}

void _reverse(elem_t *arr, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        _swap(arr, i, len - i - 1);
    }
}

void _show(FILE *stream, elem_t *arr, size_t len) {
    if (arr == NULL || len == 0) {
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

void _show_slice(FILE *stream, elem_t *arr, size_t len, size_t start,
                 size_t end) {
    end = MIN(len, end);
    if (arr == NULL || start >= end) {
        return;
    }

    _show(stream, arr + start, end - start);
}

bool _find(elem_t *arr, size_t len, elem_t e, size_t *i) {
    if (arr == NULL) {
        return false;
    }

    for (size_t j = 0; j < len; j++) {
        if (arr[j] == e) {
            if (i != NULL) {
                *i = j;
            }
            return true;
        }
    }

    return false;
}

bool _find_slice(elem_t *arr, size_t len, size_t start, size_t end, elem_t e,
                 size_t *i) {
    end = MIN(len, end);
    if (arr == NULL || start >= end) {
        return false;
    }

    if (_find(arr + start, end - start, e, i)) {
        if (i != NULL) {
            *i += start;
        }
        return true;
    }

    return false;
}

void _copy(elem_t *dst, size_t d_len, elem_t *src, size_t s_len) {
    if (dst == NULL || src == NULL || d_len == 0 || s_len == 0) {
        return;
    }
    memmove(dst, src, MIN(d_len, s_len) * sizeof(elem_t));
}

void _copy_slice(elem_t *dst, size_t d_len, size_t d_start, size_t d_end,
                 elem_t *src, size_t s_len, size_t s_start, size_t s_end) {
    d_end = MIN(d_len, d_end);
    s_end = MIN(s_len, s_end);
    if (dst == NULL || src == NULL || d_start >= d_end || s_start >= s_end) {
        return;
    }

    size_t len = MIN(d_end - d_start, s_end - s_start);
    _copy(dst + d_start, len, src + s_start, len);
}

void _move_left(elem_t *arr, size_t len, size_t n) {
    if (arr == NULL || len <= 1 || n == 0 || n >= len) {
        return;
    }

    memmove(arr, arr + n, (len - n) * sizeof(elem_t));
}

void _move_left_slice(elem_t *arr, size_t len, size_t start, size_t end,
                      size_t n) {
    end = MIN(len, end);
    if (arr == NULL || start >= end) {
        return;
    }

    n = MIN(len, n);
    _move_left(arr + start, end - start, n);
}

void _move_right(elem_t *arr, size_t len, size_t n) {
    if (arr == NULL || len <= 1 || n == 0 || n >= len) {
        return;
    }

    memmove(arr + n, arr, (len - n) * sizeof(elem_t));
}

void _move_right_slice(elem_t *arr, size_t len, size_t start, size_t end,
                       size_t n) {
    end = MIN(len, end);
    if (arr == NULL || start >= end) {
        return;
    }

    n = MIN(len, n);
    _move_right(arr + start, end - start, n);
}

void _rotate_left(elem_t *arr, size_t len, size_t n) {
    if (arr == NULL || len == 0 || n % len == 0) {
        return;
    }

    n = n % len;

    elem_t *tmp = (elem_t *)malloc(n * sizeof(elem_t));
    memmove(tmp, arr, n * sizeof(elem_t));
    memmove(arr, arr + n, (len - n) * sizeof(elem_t));
    memmove(arr + len - n, tmp, n * sizeof(elem_t));
    free(tmp);
}

void _rotate_left_slice(elem_t *arr, size_t len, size_t start, size_t end,
                        size_t n) {
    end = MIN(len, end);
    if (arr == NULL || start >= end || n % (end - start) == 0) {
        return;
    }

    n = n % (end - start);
    _rotate_left(arr + start, end - start, n);
}

void _rotate_right(elem_t *arr, size_t len, size_t n) {
    if (arr == NULL || len == 0 || n % len == 0) {
        return;
    }

    n = n % len;

    elem_t *tmp = (elem_t *)malloc(n * sizeof(elem_t));
    memmove(tmp, arr + len - n, n * sizeof(elem_t));
    memmove(arr + n, arr, (len - n) * sizeof(elem_t));
    memmove(arr, tmp, n * sizeof(elem_t));
    free(tmp);
}

void _rotate_right_slice(elem_t *arr, size_t len, size_t start, size_t end,
                         size_t n) {
    end = MIN(len, end);
    if (arr == NULL || start >= end || n % (end - start) == 0) {
        return;
    }

    n = n % (end - start);
    _rotate_right(arr + start, end - start, n);
}

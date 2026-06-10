#include "internal/utils.h"
#include <stdlib.h>
#include <string.h>

alg_elem_t alg_internal_min(alg_elem_t *arr, size_t len) {
    if (arr == NULL || len == 0) {
        return 0;
    }

    alg_elem_t min = arr[0];
    for (size_t i = 1; i < len; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    return min;
}

alg_elem_t alg_internal_max(alg_elem_t *arr, size_t len) {
    if (arr == NULL || len == 0) {
        return 0;
    }

    alg_elem_t max = arr[0];
    for (size_t i = 1; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

void alg_internal_swap(alg_elem_t *arr, size_t i, size_t j) {
    if (arr == NULL || i == j) {
        return;
    }

    alg_elem_t tmp = arr[i];
    arr[i]         = arr[j];
    arr[j]         = tmp;
}

void alg_internal_shuffle(alg_elem_t *arr, size_t len) {
    if (arr == NULL || len < 2) {
        return;
    }

    for (size_t i = 1; i < len; i++) {
        size_t j = rand() % (i + 1);
        alg_internal_swap(arr, i, j);
    }
}

void alg_internal_clear(alg_elem_t *arr, size_t len) {
    if (arr == NULL || len == 0) {
        return;
    }

    memset(arr, 0, len * sizeof(alg_elem_t));
}

void alg_internal_has_alloc_err(void *data, const char *location) {
    const char *location_label =
        (location == NULL || *location == '\0') ? "unkonwn" : location;
    if (data == NULL) {
        fprintf(stderr,
                "\x1b[1;31merror: \x1b[0mfailed to allocate memory at "
                "\x1b[33m`%s`\x1b[0m\n\n",
                location_label);
        exit(EXIT_FAILURE);
    }
}

int alg_internal_cmp(const void *v1, const void *v2) {
    if (v1 == NULL && v2 == NULL) {
        return 0;
    } else if (v1 == NULL) {
        return -1;
    } else if (v2 == NULL) {
        return 1;
    } else {
        return *(alg_elem_t *)v1 - *(alg_elem_t *)v2;
    }
}

int alg_internal_cmp_str(const void *s1, const void *s2) {
    if (s1 == NULL && s2 == NULL) {
        return 0;
    } else if (s1 == NULL) {
        return -1;
    } else if (s2 == NULL) {
        return 1;
    } else {
        return strcmp((char *)s1, (char *)s2);
    }
}

void alg_internal_show(FILE *stream, alg_elem_t *arr, size_t len,
                       const char *sep) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (arr == NULL || len == 0) {
        fprintf(stream, "[]\n");
        return;
    }

    const char *separator = (sep == NULL || *sep == '\0') ? ", " : sep;
    fprintf(stream, "[");
    for (size_t i = 0; i < len; i++) {
        fprintf(stream, "%d%s", arr[i], i == len - 1 ? "]\n" : separator);
    }
}

void alg_internal_show_slice(FILE *stream, alg_elem_t *arr, size_t len,
                             size_t start, size_t end, const char *sep) {
    if (stream == NULL) {
        stream = stdout;
    }

    end = ALG_INTERNAL_MIN(len, end);
    if (arr == NULL || start >= end) {
        fprintf(stream, "[]\n");
        return;
    }

    alg_internal_show(stream, arr + start, end - start, sep);
}

void alg_internal_show_list(FILE *stream, AlgNode *node, AlgDirection dir,
                            const char *sep) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (node == NULL) {
        fprintf(stream, "[]\n");
        return;
    }

    const char *separator = (sep == NULL || *sep == '\0') ? " <-> " : sep;
    fprintf(stream, "[");

    if (dir == ALG_BACKWARD) {
        while (node->prev != NULL) {
            node = node->prev;
        }
    }

    while (node != NULL) {
        fprintf(stream, "%d%s", node->data,
                node->next == NULL ? "]\n" : separator);
        node = node->next;
    }
}

void alg_internal_reverse(alg_elem_t *arr, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        alg_internal_swap(arr, i, len - i - 1);
    }
}

void alg_internal_reverse_slice(alg_elem_t *arr, size_t len, size_t start,
                                size_t end) {
    end = ALG_INTERNAL_MIN(len, end);
    if (arr == NULL || start >= end) {
        return;
    }

    alg_internal_reverse(arr + start, end - start);
}

bool alg_internal_find(alg_elem_t *arr, size_t len, alg_elem_t e, size_t *i) {
    if (arr == NULL || len == 0) {
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

bool alg_internal_find_slice(alg_elem_t *arr, size_t len, size_t start,
                             size_t end, alg_elem_t e, size_t *i) {
    end = ALG_INTERNAL_MIN(len, end);
    if (arr == NULL || start >= end) {
        return false;
    }

    if (alg_internal_find(arr + start, end - start, e, i)) {
        if (i != NULL) {
            *i += start;
        }
        return true;
    }

    return false;
}

void alg_internal_copy(alg_elem_t *dst, size_t d_len, alg_elem_t *src,
                       size_t s_len) {
    if (dst == NULL || src == NULL || d_len == 0 || s_len == 0) {
        return;
    }

    memmove(dst, src, ALG_INTERNAL_MIN(d_len, s_len) * sizeof(alg_elem_t));
}

void alg_internal_copy_slice(alg_elem_t *dst, size_t d_len, size_t d_start,
                             size_t d_end, alg_elem_t *src, size_t s_len,
                             size_t s_start, size_t s_end) {
    d_end = ALG_INTERNAL_MIN(d_len, d_end);
    s_end = ALG_INTERNAL_MIN(s_len, s_end);
    if (dst == NULL || src == NULL || d_start >= d_end || s_start >= s_end) {
        return;
    }

    size_t len = ALG_INTERNAL_MIN(d_end - d_start, s_end - s_start);
    alg_internal_copy(dst + d_start, len, src + s_start, len);
}

void alg_internal_move_left(alg_elem_t *arr, size_t len, size_t n) {
    if (arr == NULL || len <= 1 || n == 0 || n >= len) {
        return;
    }

    memmove(arr, arr + n, (len - n) * sizeof(alg_elem_t));
}

void alg_internal_move_left_slice(alg_elem_t *arr, size_t len, size_t start,
                                  size_t end, size_t n) {
    end = ALG_INTERNAL_MIN(len, end);
    if (arr == NULL || start >= end) {
        return;
    }

    n = ALG_INTERNAL_MIN(len, n);
    alg_internal_move_left(arr + start, end - start, n);
}

void alg_internal_move_right(alg_elem_t *arr, size_t len, size_t n) {
    if (arr == NULL || len <= 1 || n == 0 || n >= len) {
        return;
    }

    memmove(arr + n, arr, (len - n) * sizeof(alg_elem_t));
}

void alg_internal_move_right_slice(alg_elem_t *arr, size_t len, size_t start,
                                   size_t end, size_t n) {
    end = ALG_INTERNAL_MIN(len, end);
    if (arr == NULL || start >= end) {
        return;
    }

    n = ALG_INTERNAL_MIN(len, n);
    alg_internal_move_right(arr + start, end - start, n);
}

void alg_internal_rotate_left(alg_elem_t *arr, size_t len, size_t n) {
    if (arr == NULL || len == 0 || n % len == 0) {
        return;
    }

    n               = n % len;
    alg_elem_t *tmp = (alg_elem_t *)malloc(n * sizeof(alg_elem_t));
    alg_internal_has_alloc_err(tmp, __func__);

    memmove(tmp, arr, n * sizeof(alg_elem_t));
    memmove(arr, arr + n, (len - n) * sizeof(alg_elem_t));
    memmove(arr + len - n, tmp, n * sizeof(alg_elem_t));
    free(tmp);
}

void alg_internal_rotate_left_slice(alg_elem_t *arr, size_t len, size_t start,
                                    size_t end, size_t n) {
    end = ALG_INTERNAL_MIN(len, end);
    if (arr == NULL || start >= end || n % (end - start) == 0) {
        return;
    }

    n = n % (end - start);
    alg_internal_rotate_left(arr + start, end - start, n);
}

void alg_internal_rotate_right(alg_elem_t *arr, size_t len, size_t n) {
    if (arr == NULL || len == 0 || n % len == 0) {
        return;
    }

    n               = n % len;
    alg_elem_t *tmp = (alg_elem_t *)malloc(n * sizeof(alg_elem_t));
    alg_internal_has_alloc_err(tmp, __func__);

    memmove(tmp, arr + len - n, n * sizeof(alg_elem_t));
    memmove(arr + n, arr, (len - n) * sizeof(alg_elem_t));
    memmove(arr, tmp, n * sizeof(alg_elem_t));
    free(tmp);
}

void alg_internal_rotate_right_slice(alg_elem_t *arr, size_t len, size_t start,
                                     size_t end, size_t n) {
    end = ALG_INTERNAL_MIN(len, end);
    if (arr == NULL || start >= end || n % (end - start) == 0) {
        return;
    }

    n = n % (end - start);
    alg_internal_rotate_right(arr + start, end - start, n);
}

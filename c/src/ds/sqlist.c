#include "alg/ds/sqlist.h"
#include "utils.h"
#include <stdarg.h>

AlgSqList alg_sqlist_create(void) {
    AlgSqList list = {.len = 0};

    return list;
}

AlgSqList alg_sqlist_init(size_t n, ...) {
    AlgSqList list = alg_sqlist_create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < ALG_INTERNAL_MIN(n, ALG_MAX_LEN); i++) {
        list.data[list.len++] = va_arg(ap, alg_elem_t);
    }

    va_end(ap);

    return list;
}

void alg_sqlist_swap(AlgSqList *list, size_t i, size_t j) {
    if (list != NULL && ALG_INTERNAL_MAX(i, j) < list->len) {
        alg_internal_swap(list->data, i, j);
    }
}

void alg_sqlist_reverse(AlgSqList *list) {
    if (list != NULL) {
        alg_internal_reverse(list->data, list->len);
    }
}

void alg_sqlist_show(FILE *stream, AlgSqList *list) {
    if (list != NULL) {
        alg_internal_show(stream, list->data, list->len, NULL);
    } else {
        alg_internal_show(stream, NULL, 0, NULL);
    }
}

void alg_sqlist_clear(AlgSqList *list) {
    if (list != NULL) {
        list->len = 0;
    }
}

bool alg_sqlist_is_empty(AlgSqList *list) {
    return list == NULL || list->len == 0;
}

bool alg_sqlist_get(AlgSqList *list, size_t i, alg_elem_t *e) {
    if (alg_sqlist_is_empty(list) || i >= list->len) {
        return false;
    }

    if (e != NULL) {
        *e = list->data[i];
    }

    return true;
}

bool alg_sqlist_first(AlgSqList *list, alg_elem_t *e) {
    return alg_sqlist_get(list, 0, e);
}

bool alg_sqlist_last(AlgSqList *list, alg_elem_t *e) {
    return list != NULL && list->len != 0 &&
           alg_sqlist_get(list, list->len - 1, e);
}

bool alg_sqlist_set(AlgSqList *list, size_t i, alg_elem_t e) {
    if (alg_sqlist_is_empty(list) || i >= list->len) {
        return false;
    }

    list->data[i] = e;

    return true;
}

bool alg_sqlist_find(AlgSqList *list, alg_elem_t e, size_t *i) {
    return list != NULL && alg_internal_find(list->data, list->len, e, i);
}

bool alg_sqlist_insert(AlgSqList *list, size_t i, alg_elem_t e) {
    if (list == NULL || list->len == ALG_MAX_LEN || i > list->len) {
        return false;
    }

    if (i < list->len) {
        alg_internal_move_right_slice(list->data, list->len, i, list->len, 1);
    }

    list->data[i] = e;
    list->len++;

    return true;
}

bool alg_sqlist_push_front(AlgSqList *list, alg_elem_t e) {
    return list != NULL && alg_sqlist_insert(list, 0, e);
}

bool alg_sqlist_push_back(AlgSqList *list, alg_elem_t e) {
    return list != NULL && list->len != ALG_MAX_LEN &&
           alg_sqlist_insert(list, list->len, e);
}

bool alg_sqlist_del(AlgSqList *list, size_t i, alg_elem_t *e) {
    if (alg_sqlist_is_empty(list) || i >= list->len) {
        return false;
    }

    if (e != NULL) {
        *e = list->data[i];
    }

    if (i < list->len - 1) {
        alg_internal_move_left_slice(list->data, list->len, i, list->len, 1);
    }

    list->len--;

    return true;
}

bool alg_sqlist_pop_front(AlgSqList *list, alg_elem_t *e) {
    return list != NULL && alg_sqlist_del(list, 0, e);
}

bool alg_sqlist_pop_back(AlgSqList *list, alg_elem_t *e) {
    return !alg_sqlist_is_empty(list) && alg_sqlist_del(list, list->len - 1, e);
}

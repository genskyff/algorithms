#include "sqlist.h"
#include "util.h"
#include <stdarg.h>

SqList create(void) {
    SqList list = {.len = 0};

    return list;
}

SqList init(size_t n, ...) {
    SqList list = create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < MIN(n, MAXLEN); i++) {
        list.data[list.len++] = va_arg(ap, elem_t);
    }

    va_end(ap);

    return list;
}

void swap(SqList *list, size_t i, size_t j) {
    if (list != NULL && MAX(i, j) < list->len) {
        _swap(list->data, i, j);
    }
}

void reverse(SqList *list) {
    if (list != NULL) {
        _reverse(list->data, list->len);
    }
}

void show(FILE *stream, SqList *list) {
    if (list != NULL) {
        _show(stream, list->data, list->len, NULL);
    } else {
        _show(stream, NULL, 0, NULL);
    }
}

void clear(SqList *list) {
    if (list != NULL) {
        list->len = 0;
    }
}

bool is_empty(SqList *list) {
    return list == NULL || list->len == 0;
}

bool get(SqList *list, size_t i, elem_t *e) {
    if (is_empty(list) || i >= list->len) {
        return false;
    }

    if (e != NULL) {
        *e = list->data[i];
    }

    return true;
}

bool first(SqList *list, elem_t *e) {
    return get(list, 0, e);
}

bool last(SqList *list, elem_t *e) {
    return list != NULL && list->len != 0 && get(list, list->len - 1, e);
}

bool set(SqList *list, size_t i, elem_t e) {
    if (is_empty(list) || i >= list->len) {
        return false;
    }

    list->data[i] = e;

    return true;
}

bool find(SqList *list, elem_t e, size_t *i) {
    return list != NULL && _find(list->data, list->len, e, i);
}

bool insert(SqList *list, size_t i, elem_t e) {
    if (list == NULL || list->len == MAXLEN || i > list->len) {
        return false;
    }

    if (i < list->len) {
        _move_right_slice(list->data, list->len, i, list->len, 1);
    }

    list->data[i] = e;
    list->len++;

    return true;
}

bool push_front(SqList *list, elem_t e) {
    return list != NULL && insert(list, 0, e);
}

bool push_back(SqList *list, elem_t e) {
    return list != NULL && list->len != MAXLEN && insert(list, list->len, e);
}

bool del(SqList *list, size_t i, elem_t *e) {
    if (is_empty(list) || i >= list->len) {
        return false;
    }

    if (e != NULL) {
        *e = list->data[i];
    }

    if (i < list->len - 1) {
        _move_left_slice(list->data, list->len, i, list->len, 1);
    }

    list->len--;

    return true;
}

bool pop_front(SqList *list, elem_t *e) {
    return list != NULL && del(list, 0, e);
}

bool pop_back(SqList *list, elem_t *e) {
    return !is_empty(list) && del(list, list->len - 1, e);
}

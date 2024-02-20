#include "sqlist.h"
#include "utils.h"
#include <stdio.h>

void show(FILE *stream, SqList list) { _show(stream, list.data, list.len); }

void clear(SqList *list) { list->len = 0; }

bool is_empty(SqList list) { return list.len == 0 ? true : false; }

bool get(SqList list, size_t i, elem_t *e) {
    if (list.len == 0 || i >= list.len) {
        return false;
    }

    *e = list.data[i];

    return true;
}

bool find(SqList list, elem_t e, size_t *i) {
    return _find(list.data, list.len, e, i);
}

bool insert(SqList *list, size_t i, elem_t e) {
    if (list->len == MAXLEN || i > list->len + 1) {
        return false;
    }

    if (i < list->len) {
        _move_right_slice(list->data, list->len, i, list->len, 1);
    }

    list->data[i] = e;
    list->len++;

    return true;
}

bool update(SqList *list, size_t i, elem_t e) {
    if (list->len == 0 || i >= list->len) {
        return false;
    }

    list->data[i] = e;

    return true;
}

bool delete(SqList *list, size_t i, elem_t *e) {
    if (list->len == 0 || i >= list->len) {
        return false;
    }

    *e = list->data[i];

    if (i < list->len - 1) {
        _move_left_slice(list->data, list->len, i, list->len, 1);
    }

    list->len--;

    return true;
}

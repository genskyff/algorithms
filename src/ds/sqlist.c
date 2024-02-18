#include "sqlist.h"
#include <stdio.h>

void show(SqList list) {
    for (size_t i = 0; i < list.len; i++)
        printf("%d ", list.data[i]);
    printf("\n");
}

void clear(SqList *list) { list->len = 0; }

bool is_empty(SqList list) { return list.len == 0 ? true : false; }

bool get(SqList list, size_t i, elem_t *e) {
    if (list.len == 0 || i >= list.len) {
        return false;
    }

    *e = list.data[i];

    return true;
}

bool find(SqList list, elem_t e, size_t *i) { return true; }

bool insert(SqList *list, size_t i, elem_t e) {
    if (list->len == MAXLEN || i > list->len + 1) {
        return false;
    }

    if (i < list->len) {
        for (size_t j = list->len - 1; j >= i; j--) {
            list->data[j + 1] = list->data[j];
        }
    }

    list->data[i] = e;
    list->len++;

    return true;
}

bool update(SqList *list, size_t i, elem_t e) {
    if (list->len == 0 || i < 0 || i > list->len - 1)
        return false;

    list->data[i] = e;

    return true;
}

bool delete(SqList *list, size_t i, elem_t *e) {
    if (list->len == 0 || i < 0 || i > list->len - 1)
        return false;

    *e = list->data[i];

    if (i < list->len - 1)
        for (size_t j = i; j < list->len - 1; j++)
            list->data[j] = list->data[j + 1];

    list->len--;

    return true;
}

#include "static_linked_list.h"
#include "utils.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

size_t _alloc(SLinkedList *list) {
    size_t idx = list->space;

    if (idx != SIZE_MAX) {
        list->space = list->node[idx].next;
    }

    return idx;
}

void _free(SLinkedList *list, size_t idx) {
    list->node[idx].next = list->space;
    list->space          = idx;
}

SLinkedList create(void) {
    SLinkedList list = {
        .space = 0, .head = SIZE_MAX, .tail = SIZE_MAX, .len = 0};

    for (size_t i = 0; i < MAXLEN; i++) {
        list.node[i].next = i + 1;
        list.node[i].prev = SIZE_MAX;
    }

    list.node[MAXLEN - 1].next = SIZE_MAX;

    return list;
}

SLinkedList init(size_t n, ...) {
    SLinkedList list = create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < MIN(n, MAXLEN); i++) {
        size_t idx = _alloc(&list);
        if (idx == SIZE_MAX) {
            break;
        }

        list.node[idx].data = va_arg(ap, elem_t);
        list.node[idx].next = SIZE_MAX;
        list.node[idx].prev = list.tail;

        if (list.tail != SIZE_MAX) {
            list.node[list.tail].next = idx;
        }

        list.tail = idx;

        if (list.head == SIZE_MAX) {
            list.head = idx;
        }

        list.len++;
    }

    va_end(ap);

    return list;
}

elem_t *to_array(SLinkedList *list) {
    if (list == NULL || list->len == 0) {
        return NULL;
    }

    elem_t *arr = (elem_t *)malloc(list->len * sizeof(elem_t));
    if (arr == NULL) {
        return NULL;
    }

    size_t cur = list->head;
    for (size_t i = 0; i < list->len; i++) {
        arr[i] = list->node[cur].data;
        cur    = list->node[cur].next;
    }

    return arr;
}

void swap(SLinkedList *list, size_t i, size_t j) {
    if (list == NULL || list->len == 0 || i == j || MAX(i, j) >= list->len) {
        return;
    }

    if (i > j) {
        SWAP(i, j);
    }

    size_t node_i, node_j;
    size_t cur = list->head;
    for (size_t k = 0; k <= j; k++) {
        if (k == i) {
            node_i = cur;
        }

        if (k == j) {
            node_j = cur;
        }

        cur = list->node[cur].next;
    }

    SWAP(list->node[node_i].data, list->node[node_j].data);
}

void reverse(SLinkedList *list) {
    if (list == NULL || list->len == 0) {
        return;
    }

    for (size_t i = 0; i < list->len / 2; i++) {
        swap(list, i, list->len - i - 1);
    }
}

void show(FILE *stream, SLinkedList *list) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (list == NULL || list->len == 0) {
        fprintf(stream, "[]\n");
        return;
    }

    fprintf(stream, "[");
    for (size_t cur = list->head; cur != SIZE_MAX; cur = list->node[cur].next) {
        fprintf(stream, "%d%s", list->node[cur].data,
                list->node[cur].next == SIZE_MAX ? "]\n" : " <-> ");
    }
}

void clear(SLinkedList *list) {
    if (list == NULL) {
        return;
    }

    for (size_t i = list->head; i != SIZE_MAX;) {
        size_t next = list->node[i].next;
        _free(list, i);
        i = next;
    }

    list->space = 0;
    list->head  = SIZE_MAX;
    list->tail  = SIZE_MAX;
    list->len   = 0;

    for (size_t i = 0; i < MAXLEN; i++) {
        list->node[i].next = i + 1;
        list->node[i].prev = SIZE_MAX;
    }

    list->node[MAXLEN - 1].next = SIZE_MAX;
}

bool is_empty(SLinkedList *list) {
    return list == NULL || list->len == 0;
}

bool get(SLinkedList *list, size_t i, elem_t *e) {
    if (list == NULL || list->len == 0 || i >= list->len) {
        return false;
    }

    size_t cur;
    if (i <= (list->len + 1) / 2) {
        cur = list->head;
        for (size_t j = 0; j < i; j++) {
            cur = list->node[cur].next;
        }
    } else {
        cur = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            cur = list->node[cur].prev;
        }
    }

    if (e != NULL) {
        *e = list->node[cur].data;
    }

    return true;
}

bool first(SLinkedList *list, elem_t *e) {
    if (list == NULL || list->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = list->node[list->head].data;
    }

    return true;
}

bool last(SLinkedList *list, elem_t *e) {
    if (list == NULL || list->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = list->node[list->tail].data;
    }

    return true;
}

bool set(SLinkedList *list, size_t i, elem_t e) {
    if (list == NULL || list->len == 0 || i >= list->len) {
        return false;
    }

    size_t cur;
    if (i <= (list->len + 1) / 2) {
        cur = list->head;
        for (size_t j = 0; j < i; j++) {
            cur = list->node[cur].next;
        }
    } else {
        cur = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            cur = list->node[cur].prev;
        }
    }

    list->node[cur].data = e;

    return true;
}

bool find(SLinkedList *list, elem_t e, size_t *i) {
    if (list == NULL || list->len == 0) {
        return false;
    }

    size_t cur = list->head;
    for (size_t j = 0; j < list->len; j++) {
        if (list->node[cur].data == e) {
            if (i != NULL) {
                *i = j;
            }

            return true;
        }

        cur = list->node[cur].next;
    }

    return false;
}

bool insert(SLinkedList *list, size_t i, elem_t e) {
    if (list == NULL || list->len == MAXLEN || i > list->len) {
        return false;
    }

    size_t idx = _alloc(list);
    if (idx == SIZE_MAX) {
        return false;
    }

    list->node[idx].data = e;

    if (i == 0) {
        list->node[idx].next = list->head;
        list->node[idx].prev = SIZE_MAX;

        if (list->head != SIZE_MAX) {
            list->node[list->head].prev = idx;
        }

        list->head = idx;

        if (list->tail == SIZE_MAX) {
            list->tail = idx;
        }
    } else if (i == list->len) {
        list->node[idx].next = SIZE_MAX;
        list->node[idx].prev = list->tail;

        if (list->tail != SIZE_MAX) {
            list->node[list->tail].next = idx;
        } else {
            list->head = idx;
        }

        list->tail = idx;
    } else {
        size_t cur;
        if (i <= (list->len + 1) / 2) {
            cur = list->head;
            for (size_t j = 0; j < i; j++) {
                cur = list->node[cur].next;
            }
        } else {
            cur = list->tail;
            for (size_t j = list->len - 1; j > i; j--) {
                cur = list->node[cur].prev;
            }
        }

        list->node[idx].next                  = list->node[cur].next;
        list->node[idx].prev                  = cur;
        list->node[cur].next                  = idx;
        list->node[list->node[idx].next].prev = idx;
    }

    list->len++;

    return true;
}

bool push_front(SLinkedList *list, elem_t e) {
    return insert(list, 0, e);
}

bool push_back(SLinkedList *list, elem_t e) {
    return list != NULL && insert(list, list->len, e);
}

bool del(SLinkedList *list, size_t i, elem_t *e) {
    if (list == NULL || list->len == 0 || i >= list->len) {
        return false;
    }

    size_t cur;
    if (i <= (list->len + 1) / 2) {
        cur = list->head;
        for (size_t j = 0; j < i; j++) {
            cur = list->node[cur].next;
        }
    } else {
        cur = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            cur = list->node[cur].prev;
        }
    }

    if (e != NULL) {
        *e = list->node[cur].data;
    }

    if (cur != list->head) {
        list->node[list->node[cur].prev].next = list->node[cur].next;

    } else {
        list->head = list->node[cur].next;
    }

    if (cur != list->tail) {
        list->node[list->node[cur].next].prev = list->node[cur].prev;
    } else {
        list->tail = list->node[cur].prev;
    }

    list->len--;
    _free(list, cur);

    return true;
}

bool pop_front(SLinkedList *list, elem_t *e) {
    return del(list, 0, e);
}

bool pop_back(SLinkedList *list, elem_t *e) {
    return list != NULL && list->len != 0 && del(list, list->len - 1, e);
}

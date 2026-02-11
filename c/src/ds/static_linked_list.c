#include "alg/ds/static_linked_list.h"
#include "utils.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

size_t _alloc(SLinkedList *list);
void   _free(SLinkedList *list, size_t idx);

size_t _alloc(SLinkedList *list) {
    size_t idx = list->space;

    if (idx != SIZE_MAX) {
        list->space = list->nodes[idx].next;
    }

    return idx;
}

void _free(SLinkedList *list, size_t idx) {
    list->nodes[idx].next = list->space;
    list->space           = idx;
}

SLinkedList create(void) {
    SLinkedList list = {
        .space = 0, .head = SIZE_MAX, .tail = SIZE_MAX, .len = 0};

    for (size_t i = 0; i < MAXLEN; i++) {
        list.nodes[i].next = i + 1;
        list.nodes[i].prev = SIZE_MAX;
    }

    list.nodes[MAXLEN - 1].next = SIZE_MAX;

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

        list.nodes[idx].data = va_arg(ap, elem_t);
        list.nodes[idx].next = SIZE_MAX;

        if (list.head == SIZE_MAX) {
            list.nodes[idx].prev = SIZE_MAX;
            list.head            = idx;
        } else {
            list.nodes[idx].prev       = list.tail;
            list.nodes[list.tail].next = idx;
        }

        list.tail = idx;
        list.len++;
    }

    va_end(ap);

    return list;
}

elem_t *to_array(SLinkedList *list) {
    if (list == NULL || list->nodes[list->head].data == SIZE_MAX ||
        list->len == 0) {
        return NULL;
    }

    elem_t *arr = (elem_t *)malloc(list->len * sizeof(elem_t));
    if (arr == NULL) {
        return NULL;
    }

    size_t cur = list->head;
    for (size_t i = 0; cur != SIZE_MAX && i < list->len; i++) {
        arr[i] = list->nodes[cur].data;
        cur    = list->nodes[cur].next;
    }

    return arr;
}

void swap(SLinkedList *list, size_t i, size_t j) {
    if (list == NULL || list->nodes[list->head].data == SIZE_MAX || i == j ||
        MAX(i, j) >= list->len) {
        return;
    }

    if (i > j) {
        SWAP(i, j);
    }

    size_t node_i, node_j;
    for (size_t k = 0, cur = list->head; k <= j; k++) {
        if (k == i) {
            node_i = cur;
        }

        if (k == j) {
            node_j = cur;
        }

        cur = list->nodes[cur].next;
    }

    size_t i_prev = list->nodes[node_i].prev;
    size_t i_next = list->nodes[node_i].next;
    size_t j_prev = list->nodes[node_j].prev;
    size_t j_next = list->nodes[node_j].next;

    // adjacent nodes
    if (i_next == node_j) { // node_i is directly connected to node_j
        list->nodes[node_i].next = j_next;
        if (j_next != SIZE_MAX) {
            list->nodes[j_next].prev = node_i;
        }

        list->nodes[node_j].prev = i_prev;
        if (i_prev != SIZE_MAX) {
            list->nodes[i_prev].next = node_j;
        }

        list->nodes[node_j].next = node_i;
        list->nodes[node_i].prev = node_j;
    } else { // non-adjacent nodes
        if (i_prev != SIZE_MAX) {
            list->nodes[i_prev].next = node_j;
        }

        if (i_next != SIZE_MAX) {
            list->nodes[i_next].prev = node_j;
        }

        if (j_prev != SIZE_MAX) {
            list->nodes[j_prev].next = node_i;
        }

        if (j_next != SIZE_MAX) {
            list->nodes[j_next].prev = node_i;
        }

        list->nodes[node_i].prev = j_prev;
        list->nodes[node_j].prev = i_prev;

        size_t tmp               = list->nodes[node_i].next;
        list->nodes[node_i].next = list->nodes[node_j].next;
        list->nodes[node_j].next = tmp;
    }

    if (list->head == node_i) {
        list->head = node_j;
    } else if (list->head == node_j) {
        list->head = node_i;
    }

    if (list->tail == node_i) {
        list->tail = node_j;
    } else if (list->tail == node_j) {
        list->tail = node_i;
    }
}

void reverse(SLinkedList *list) {
    if (list == NULL || list->nodes[list->head].data == SIZE_MAX ||
        list->len == 0) {
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

    if (list == NULL || list->nodes[list->head].data == SIZE_MAX ||
        list->len == 0) {
        fprintf(stream, "[]\n");
        return;
    }

    fprintf(stream, "[");
    for (size_t cur = list->head; cur != SIZE_MAX;
         cur        = list->nodes[cur].next) {
        fprintf(stream, "%d%s", list->nodes[cur].data,
                list->nodes[cur].next == SIZE_MAX ? "]\n" : " <-> ");
    }
}

void clear(SLinkedList *list) {
    if (list != NULL) {
        for (size_t i = list->head; i != SIZE_MAX;) {
            size_t next = list->nodes[i].next;
            _free(list, i);
            i = next;
        }

        list->space = 0;
        list->head  = SIZE_MAX;
        list->tail  = SIZE_MAX;
        list->len   = 0;

        for (size_t i = 0; i < MAXLEN; i++) {
            list->nodes[i].next = i + 1;
            list->nodes[i].prev = SIZE_MAX;
        }

        list->nodes[MAXLEN - 1].next = SIZE_MAX;
    }
}

bool is_empty(SLinkedList *list) {
    return list == NULL || list->nodes[list->head].data == SIZE_MAX ||
           list->len == 0;
}

bool get(SLinkedList *list, size_t i, elem_t *e) {
    if (list == NULL || list->nodes[list->head].data == SIZE_MAX ||
        list->len == 0 || i >= list->len) {
        return false;
    }

    size_t cur;
    if (i <= (list->len + 1) / 2) {
        cur = list->head;
        for (size_t j = 0; j < i; j++) {
            cur = list->nodes[cur].next;
        }
    } else {
        cur = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            cur = list->nodes[cur].prev;
        }
    }

    if (e != NULL) {
        *e = list->nodes[cur].data;
    }

    return true;
}

bool first(SLinkedList *list, elem_t *e) {
    if (list == NULL || list->nodes[list->head].data == SIZE_MAX ||
        list->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = list->nodes[list->head].data;
    }

    return true;
}

bool last(SLinkedList *list, elem_t *e) {
    if (list == NULL || list->nodes[list->head].data == SIZE_MAX ||
        list->len == 0) {
        return false;
    }

    if (e != NULL) {
        *e = list->nodes[list->tail].data;
    }

    return true;
}

bool set(SLinkedList *list, size_t i, elem_t e) {
    if (list == NULL || list->nodes[list->head].data == SIZE_MAX ||
        list->len == 0 || i >= list->len) {
        return false;
    }

    size_t cur;
    if (i <= (list->len + 1) / 2) {
        cur = list->head;
        for (size_t j = 0; j < i; j++) {
            cur = list->nodes[cur].next;
        }
    } else {
        cur = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            cur = list->nodes[cur].prev;
        }
    }

    list->nodes[cur].data = e;

    return true;
}

bool find(SLinkedList *list, elem_t e, size_t *i) {
    if (list == NULL || list->nodes[list->head].data == SIZE_MAX ||
        list->len == 0) {
        return false;
    }

    size_t cur = list->head;
    for (size_t j = 0; list->nodes[cur].data != SIZE_MAX && j < list->len;
         j++) {
        if (list->nodes[cur].data == e) {
            if (i != NULL) {
                *i = j;
            }

            return true;
        }

        cur = list->nodes[cur].next;
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

    list->nodes[idx].data = e;

    if (i == 0) {
        list->nodes[idx].next = list->head;
        list->nodes[idx].prev = SIZE_MAX;

        if (list->head != SIZE_MAX) {
            list->nodes[list->head].prev = idx;
        }

        list->head = idx;

        if (list->tail == SIZE_MAX) {
            list->tail = idx;
        }
    } else if (i == list->len) {
        list->nodes[idx].next = SIZE_MAX;
        list->nodes[idx].prev = list->tail;

        if (list->tail != SIZE_MAX) {
            list->nodes[list->tail].next = idx;
        } else {
            list->head = idx;
        }

        list->tail = idx;
    } else {
        size_t cur;
        if (i <= (list->len + 1) / 2) {
            cur = list->head;
            for (size_t j = 0; j < i; j++) {
                cur = list->nodes[cur].next;
            }
        } else {
            cur = list->tail;
            for (size_t j = list->len - 1; j > i; j--) {
                cur = list->nodes[cur].prev;
            }
        }

        list->nodes[idx].next                   = list->nodes[cur].next;
        list->nodes[idx].prev                   = cur;
        list->nodes[cur].next                   = idx;
        list->nodes[list->nodes[idx].next].prev = idx;
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
    if (list == NULL || list->nodes[list->head].data == SIZE_MAX ||
        list->len == 0 || i >= list->len) {
        return false;
    }

    size_t cur;
    if (i <= (list->len + 1) / 2) {
        cur = list->head;
        for (size_t j = 0; j < i; j++) {
            cur = list->nodes[cur].next;
        }
    } else {
        cur = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            cur = list->nodes[cur].prev;
        }
    }

    if (e != NULL) {
        *e = list->nodes[cur].data;
    }

    if (cur == list->head) {
        list->head = list->nodes[cur].next;
    } else {
        list->nodes[list->nodes[cur].prev].next = list->nodes[cur].next;
    }

    if (cur == list->tail) {
        list->tail = list->nodes[cur].prev;
    } else {
        list->nodes[list->nodes[cur].next].prev = list->nodes[cur].prev;
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

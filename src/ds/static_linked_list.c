#include "static_linked_list.h"
#include "utils.h"
#include <stdarg.h>
#include <stdint.h>

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

void show(FILE *stream, SLinkedList *list) {
    fprintf(stream, "SLinkedList: [");
    for (size_t i = list->head; i != SIZE_MAX; i = list->node[i].next) {
        fprintf(stream, "%d", list->node[i].data);
        if (list->node[i].next != SIZE_MAX) {
            fprintf(stream, " <-> ");
        }
    }
    fprintf(stream, "]\n");
}

void clear(SLinkedList *list) {
    for (size_t i = list->head; i != SIZE_MAX;) {
        size_t next = list->node[i].next;
        _free(list, i);
        i = next;
    }

    list->head = SIZE_MAX;
    list->tail = SIZE_MAX;
    list->len  = 0;
}

bool is_empty(SLinkedList *list) {
    return list->len == 0;
}

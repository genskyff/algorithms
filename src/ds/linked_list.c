#include "linked_list.h"
#include "type.h"
#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

LinkedList create(void) {
    LinkedList list;
    list.head = NULL;
    list.len  = 0;

    return list;
}

LinkedList init(size_t n, ...) {
    elem_t *arr = (elem_t *)malloc(n * sizeof(elem_t));

    if (arr == NULL) {
        fprintf(stderr, "init: failed to allocate memory\n");
        abort();
    }

    va_list ap;
    va_start(ap, n);
    for (size_t i = 0; i < n; i++) {
        arr[i] = va_arg(ap, elem_t);
    }
    va_end(ap);

    LinkedList list = from_array(arr, n);
    free(arr);

    return list;
}

LinkedList from_array(elem_t *arr, size_t len) {
    LinkedList list = create();

    if (arr == NULL || len == 0) {
        return list;
    }

    Node *tail = NULL;

    for (size_t i = 0; i < len; i++) {
        Node *node = (Node *)malloc(sizeof(Node));
        if (node == NULL) {
            return list;
        }

        node->data = arr[i];
        node->next = NULL;

        if (list.head == NULL) {
            list.head = node;
            tail      = node;
        } else {
            tail->next = node;
            tail       = node;
        }

        list.len++;
    }

    return list;
}

elem_t *to_array(LinkedList list) {
    if (list.head == NULL || list.len == 0) {
        return NULL;
    }

    elem_t *arr = (elem_t *)malloc(list.len * sizeof(elem_t));
    if (arr == NULL) {
        return NULL;
    }

    Node *node = list.head;
    for (size_t i = 0; node != NULL && i < list.len; i++) {
        arr[i] = node->data;
        node   = node->next;
    }

    return arr;
}

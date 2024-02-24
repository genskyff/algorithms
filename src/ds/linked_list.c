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

elem_t *to_array(LinkedList *list) {
    if (list == NULL || list->head == NULL || list->len == 0) {
        return NULL;
    }

    elem_t *arr = (elem_t *)malloc(list->len * sizeof(elem_t));
    if (arr == NULL) {
        return NULL;
    }

    Node *node = list->head;
    for (size_t i = 0; node != NULL && i < list->len; i++) {
        arr[i] = node->data;
        node   = node->next;
    }

    return arr;
}

void swap(LinkedList *list, size_t i, size_t j) {
    if (list == NULL || list->head == NULL || list->len == 0) {
        return;
    }

    if (i == j || i >= list->len || j >= list->len) {
        return;
    }

    if (i > j) {
        size_t tmp = i;
        i          = j;
        j          = tmp;
    }

    Node *prev_i = NULL;
    Node *node_i = list->head;
    for (size_t k = 0; k < i; k++) {
        prev_i = node_i;
        node_i = node_i->next;
    }

    Node *prev_j = NULL;
    Node *node_j = list->head;
    for (size_t k = 0; k < j; k++) {
        prev_j = node_j;
        node_j = node_j->next;
    }

    if (prev_i != NULL) {
        prev_i->next = node_j;
    } else {
        list->head = node_j;
    }

    if (prev_j != NULL) {
        prev_j->next = node_i;
    } else {
        list->head = node_i;
    }

    Node *tmp    = node_i->next;
    node_i->next = node_j->next;
    node_j->next = tmp;
}

void reverse(LinkedList *list) {
    if (list == NULL || list->head == NULL || list->len == 0) {
        return;
    }

    for (size_t i = 0; i < list->len / 2; i++) {
        swap(list, i, list->len - i - 1);
    }
}

void show(FILE *stream, LinkedList *list) {
    if (list == NULL || list->head == NULL || list->len == 0) {
        return;
    }

    if (stream == NULL) {
        stream = stdout;
    }

    Node *node = list->head;
    for (size_t i = 0; node != NULL && i < list->len; i++) {
        fprintf(stream, "%d", node->data);
        node = node->next;
        if (node != NULL && i < list->len - 1) {
            fprintf(stream, " -> ");
        }
    }
    fprintf(stream, "\n");
}

void clear(LinkedList *list) {
    Node *node = list->head;
    while (node != NULL) {
        Node *tmp = node;
        node      = node->next;
        free(tmp);
    }

    list->head = NULL;
    list->len  = 0;
}

bool is_empty(LinkedList *list) {
    return list == NULL || list->head == NULL || list->len == 0;
}

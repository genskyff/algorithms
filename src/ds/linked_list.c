#include "linked_list.h"
#include "type.h"
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

bool get(LinkedList *list, size_t i, elem_t *e) {
    if (list == NULL || list->head == NULL || list->len == 0 ||
        i >= list->len) {
        return false;
    }

    Node *node = list->head;
    for (size_t k = 0; k < i; k++) {
        node = node->next;
    }

    if (e != NULL) {
        *e = node->data;
    }

    return true;
}

bool set(LinkedList *list, size_t i, elem_t e) {
    if (list == NULL || list->head == NULL || list->len == 0 ||
        i >= list->len) {
        return false;
    }

    Node *node = list->head;
    for (size_t k = 0; k < i; k++) {
        node = node->next;
    }

    node->data = e;

    return true;
}

bool find(LinkedList *list, elem_t e, size_t *i) {
    if (list == NULL || list->head == NULL || list->len == 0) {
        return false;
    }

    Node *node = list->head;
    for (size_t k = 0; node != NULL && k < list->len; k++) {
        if (node->data == e) {
            if (i != NULL) {
                *i = k;
            }
            return true;
        }
        node = node->next;
    }

    return false;
}

bool insert(LinkedList *list, size_t i, elem_t e) {
    if (list == NULL || i > list->len) {
        return false;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }

    node->data = e;

    if (i == 0) {
        node->next = list->head;
        list->head = node;
    } else {
        Node *prev = list->head;
        for (size_t k = 0; k < i - 1; k++) {
            prev = prev->next;
        }

        node->next = prev->next;
        prev->next = node;
    }

    list->len++;

    return true;
}

bool push(LinkedList *list, elem_t e) {
    return list != NULL && insert(list, list->len, e);
}
bool del(LinkedList *list, size_t i, elem_t *e) {
    if (list == NULL || list->head == NULL || list->len == 0 ||
        i >= list->len) {
        return false;
    }

    if (i == 0) {
        Node *node = list->head;
        list->head = node->next;
        if (e != NULL) {
            *e = node->data;
        }
        free(node);
    } else {
        Node *prev = list->head;
        for (size_t k = 0; k < i - 1; k++) {
            prev = prev->next;
        }

        Node *node = prev->next;
        prev->next = node->next;
        if (e != NULL) {
            *e = node->data;
        }
        free(node);
    }

    list->len--;

    return true;
}

bool pop(LinkedList *list, elem_t *e) {
    if (list == NULL || list->head == NULL || list->len == 0) {
        return false;
    } else {
        return del(list, list->len - 1, e);
    }
}

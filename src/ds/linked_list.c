#include "linked_list.h"
#include <stdarg.h>
#include <stdlib.h>

LinkedList create(void) {
    LinkedList list = {.head = NULL};

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
    }

    return list;
}

elem_t *to_array(LinkedList *list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }

    elem_t *arr = (elem_t *)malloc(length(list) * sizeof(elem_t));
    if (arr == NULL) {
        return NULL;
    }

    Node *node = list->head;
    for (size_t i = 0; node != NULL; i++) {
        arr[i] = node->data;
        node   = node->next;
    }

    return arr;
}

size_t length(LinkedList *list) {
    if (list == NULL || list->head == NULL) {
        return 0;
    }

    size_t len  = 0;
    Node  *node = list->head;
    while (node != NULL) {
        len++;
        node = node->next;
    }

    return len;
}

void swap(LinkedList *list, size_t i, size_t j) {
    if (list == NULL || list->head == NULL) {
        return;
    }

    if (i == j) {
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

        if (node_i == NULL) {
            return;
        }
    }

    Node *prev_j = NULL;
    Node *node_j = list->head;
    for (size_t k = 0; k < j; k++) {
        prev_j = node_j;
        node_j = node_j->next;

        if (node_j == NULL) {
            return;
        }
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
    if (list == NULL || list->head == NULL) {
        return;
    }

    size_t len = length(list);

    for (size_t i = 0; i < len / 2; i++) {
        swap(list, i, len - i - 1);
    }
}

void show(FILE *stream, LinkedList *list) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (list == NULL || list->head == NULL) {
        fprintf(stream, "[]\n");
        return;
    }

    if (stream == NULL) {
        stream = stdout;
    }

    fprintf(stream, "[");
    Node *node = list->head;
    while (node != NULL) {
        fprintf(stream, "%d", node->data);
        node = node->next;
        if (node != NULL) {
            fprintf(stream, " -> ");
        }
    }
    fprintf(stream, "]\n");
}

void clear(LinkedList *list) {
    Node *node = list->head;
    while (node != NULL) {
        Node *tmp = node;
        node      = node->next;
        free(tmp);
    }

    list->head = NULL;
}

bool is_empty(LinkedList *list) {
    return list == NULL || list->head == NULL;
}

bool get(LinkedList *list, size_t i, elem_t *e) {
    if (list == NULL || list->head == NULL) {
        return false;
    }

    Node *node = list->head;
    for (size_t k = 0; node != NULL && k != i; k++) {
        node = node->next;
    }

    if (node == NULL) {
        return false;
    }

    if (e != NULL) {
        *e = node->data;
    }

    return true;
}

bool set(LinkedList *list, size_t i, elem_t e) {
    if (list == NULL || list->head == NULL) {
        return false;
    }

    Node *node = list->head;
    for (size_t k = 0; node != NULL && k != i; k++) {
        node = node->next;
    }

    if (node == NULL) {
        return false;
    }

    node->data = e;

    return true;
}

bool find(LinkedList *list, elem_t e, size_t *i) {
    if (list == NULL || list->head == NULL) {
        return false;
    }

    Node *node = list->head;
    for (size_t k = 0; node != NULL; k++) {
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
    if (list == NULL) {
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
        for (size_t k = 0; k < i - 1 && prev != NULL; k++) {
            prev = prev->next;
        }

        if (prev == NULL) {
            free(node);
            return false;
        }

        node->next = prev->next;
        prev->next = node;
    }

    return true;
}

bool push(LinkedList *list, elem_t e) {
    if (list == NULL) {
        return false;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }

    Node *tail = list->head;
    while (tail != NULL && tail->next != NULL) {
        tail = tail->next;
    }

    node->data = e;
    node->next = NULL;

    if (tail == NULL) {
        list->head = node;
    } else {
        tail->next = node;
    }

    return true;
}

bool del(LinkedList *list, size_t i, elem_t *e) {
    if (list == NULL || list->head == NULL) {
        return false;
    }

    Node *node;
    if (i == 0) {
        node       = list->head;
        list->head = node->next;
    } else {
        Node *prev = list->head;
        for (size_t k = 0; k < i - 1 && prev != NULL; k++) {
            prev = prev->next;
        }

        if (prev == NULL || prev->next == NULL) {
            return false;
        }

        node       = prev->next;
        prev->next = node->next;
    }

    if (e != NULL) {
        *e = node->data;
    }
    free(node);

    return true;
}

bool pop(LinkedList *list, elem_t *e) {
    if (list == NULL || list->head == NULL) {
        return false;
    }

    Node *node = list->head;

    if (node->next == NULL) {
        list->head = NULL;
        if (e != NULL) {
            *e = node->data;
        }
        free(node);

        return true;
    } else {
        while (node->next->next != NULL) {
            node = node->next;
        }

        Node *to_del = node->next;
        if (e != NULL) {
            *e = to_del->data;
        }
        node->next = NULL;
        free(to_del);

        return true;
    }
}

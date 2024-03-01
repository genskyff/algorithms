#include "linked_list.h"
#include "utils.h"
#include <stdarg.h>
#include <stdlib.h>

LinkedList create(void) {
    LinkedList list = {.head = NULL, .tail = NULL, .len = 0};

    return list;
}

LinkedList init(size_t n, ...) {
    LinkedList list = create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        Node *node = (Node *)malloc(sizeof(Node));
        if (node == NULL) {
            fprintf(stderr,
                    "\x1b[1;31merror: \x1b[0mfailed to allocate memory (exec "
                    "\x1b[33minit\x1b[0m)\n\n");
            exit(EXIT_FAILURE);
        }

        node->data = va_arg(ap, elem_t);
        node->next = NULL;

        if (list.head == NULL) {
            node->prev = NULL;
            list.head  = node;
            list.tail  = node;
        } else {
            node->prev      = list.tail;
            list.tail->next = node;
            list.tail       = node;
        }

        list.len++;
    }

    va_end(ap);

    return list;
}

void swap(LinkedList *list, size_t i, size_t j) {
    if (list == NULL || list->head == NULL || i == j ||
        MAX(i, j) >= list->len) {
        return;
    }

    if (i > j) {
        SWAP(i, j);
    }

    Node *node_i = NULL, *node_j = NULL;
    Node *tail = list->head;
    for (size_t k = 0; k < j; k++) {
        if (k == i) {
            node_i = tail;
        }

        if (k == j) {
            node_j = tail;
        }

        tail = tail->next;
    }

    Node *i_prev = node_i->prev;
    Node *i_next = node_i->next;
    if (i_prev != NULL) {
        i_prev->next = node_j;
    } else {
        list->head = node_j;
    }

    Node *j_prev = node_j->prev;
    Node *j_next = node_j->next;
    if (j_next != NULL) {
        j_next->prev = node_i;
    } else {
        list->tail = node_i;
    }

    node_i->prev = j_prev;
    node_i->next = j_next;
    node_j->prev = i_prev;
    node_j->next = i_next;
}

void reverse(LinkedList *list) {
    if (list == NULL || list->head == NULL) {
        return;
    }

    for (size_t i = 0; i < list->len / 2; i++) {
        swap(list, i, list->len - i - 1);
    }
}

void show(FILE *stream, LinkedList *list) {
    if (list != NULL) {
        _show_list(stream, list->head, NULL);
    } else {
        _show_list(stream, NULL, NULL);
    }
}

void clear(LinkedList *list) {
    if (list == NULL) {
        return;
    }

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

#include "alg/ds/linked_list.h"
#include "internal/utils.h"
#include <stdlib.h>

AlgLinkedList alg_linked_list_create(void) {
    AlgLinkedList list = {.head = NULL, .tail = NULL, .len = 0};

    return list;
}

AlgLinkedList alg_linked_list_from_array(const alg_elem_t *arr, size_t len) {
    AlgLinkedList list = alg_linked_list_create();

    for (size_t i = 0; arr != NULL && i < len; i++) {
        AlgNode *node = (AlgNode *)malloc(sizeof(AlgNode));

        node->data = arr[i];
        node->next = NULL;

        if (list.head == NULL) {
            node->prev = NULL;
            list.head  = node;
        } else {
            node->prev      = list.tail;
            list.tail->next = node;
        }

        list.tail = node;
        list.len++;
    }

    return list;
}

void alg_linked_list_swap(AlgLinkedList *list, size_t i, size_t j) {
    if (alg_linked_list_is_empty(list) || i == j ||
        ALG_INTERNAL_MAX(i, j) >= list->len) {
        return;
    }

    if (i > j) {
        ALG_INTERNAL_SWAP(i, j);
    }

    AlgNode *node_i, *node_j;
    AlgNode *node = list->head;
    for (size_t k = 0; k <= j; k++) {
        if (k == i) {
            node_i = node;
        }

        if (k == j) {
            node_j = node;
        }

        node = node->next;
    }

    AlgNode *i_prev = node_i->prev;
    AlgNode *i_next = node_i->next;
    AlgNode *j_prev = node_j->prev;
    AlgNode *j_next = node_j->next;

    // adjacent nodes
    if (i_next == node_j) { // node_i is directly connected to node_j
        node_i->next = j_next;
        if (j_next != NULL) {
            j_next->prev = node_i;
        }

        node_j->prev = i_prev;
        if (i_prev != NULL) {
            i_prev->next = node_j;
        }

        node_j->next = node_i;
        node_i->prev = node_j;
    } else { // non-adjacent nodes
        if (i_prev != NULL) {
            i_prev->next = node_j;
        }

        if (i_next != NULL) {
            i_next->prev = node_j;
        }

        if (j_prev != NULL) {
            j_prev->next = node_i;
        }

        if (j_next != NULL) {
            j_next->prev = node_i;
        }

        node_i->prev = j_prev;
        node_j->prev = i_prev;

        AlgNode *tmp = node_i->next;
        node_i->next = node_j->next;
        node_j->next = tmp;
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

void alg_linked_list_reverse(AlgLinkedList *list) {
    if (alg_linked_list_is_empty(list) || list->len < 2) {
        return;
    }

    for (size_t i = 0; i < list->len / 2; i++) {
        alg_linked_list_swap(list, i, list->len - i - 1);
    }
}

void alg_linked_list_show(FILE *stream, const AlgLinkedList *list) {
    if (list != NULL) {
        alg_internal_show_list(stream, list->head, ALG_FORWARD, NULL);
    } else {
        alg_internal_show_list(stream, NULL, ALG_FORWARD, NULL);
    }
}

void alg_linked_list_clear(AlgLinkedList *list) {
    if (!alg_linked_list_is_empty(list)) {
        AlgNode *node = list->head;
        while (node != NULL) {
            AlgNode *tmp = node;
            node         = node->next;
            free(tmp);
        }

        list->head = NULL;
        list->tail = NULL;
        list->len  = 0;
    }
}

bool alg_linked_list_is_empty(const AlgLinkedList *list) {
    return list == NULL || list->head == NULL || list->tail == NULL ||
           list->len == 0;
}

bool alg_linked_list_get(const AlgLinkedList *list, size_t i, alg_elem_t *e) {
    if (alg_linked_list_is_empty(list) || i >= list->len) {
        return false;
    }

    const AlgNode *node;
    if (i <= (list->len + 1) / 2) {
        node = list->head;
        for (size_t j = 0; j < i; j++) {
            node = node->next;
        }
    } else {
        node = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            node = node->prev;
        }
    }

    if (e != NULL) {
        *e = node->data;
    }

    return true;
}

bool alg_linked_list_first(const AlgLinkedList *list, alg_elem_t *e) {
    if (alg_linked_list_is_empty(list)) {
        return false;
    }

    if (e != NULL) {
        *e = list->head->data;
    }

    return true;
}

bool alg_linked_list_last(const AlgLinkedList *list, alg_elem_t *e) {
    if (alg_linked_list_is_empty(list)) {
        return false;
    }

    if (e != NULL) {
        *e = list->tail->data;
    }

    return true;
}

bool alg_linked_list_set(AlgLinkedList *list, size_t i, alg_elem_t e) {
    if (alg_linked_list_is_empty(list) || i >= list->len) {
        return false;
    }

    AlgNode *node;
    if (i <= (list->len + 1) / 2) {
        node = list->head;
        for (size_t j = 0; j < i; j++) {
            node = node->next;
        }
    } else {
        node = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            node = node->prev;
        }
    }

    node->data = e;

    return true;
}

bool alg_linked_list_find(const AlgLinkedList *list, alg_elem_t e, size_t *i) {
    if (alg_linked_list_is_empty(list)) {
        return false;
    }

    const AlgNode *node = list->head;
    for (size_t j = 0; node != NULL && j < list->len; j++) {
        if (node->data == e) {
            if (i != NULL) {
                *i = j;
            }
            return true;
        }
        node = node->next;
    }

    return false;
}

bool alg_linked_list_insert(AlgLinkedList *list, size_t i, alg_elem_t e) {
    if (list == NULL || i > list->len) {
        return false;
    }

    AlgNode *node = (AlgNode *)malloc(sizeof(AlgNode));
    node->data    = e;

    if (i == 0) {
        node->next = list->head;
        node->prev = NULL;

        if (list->head != NULL) {
            list->head->prev = node;
        }

        list->head = node;

        if (list->len == 0) {
            list->tail = node;
        }
    } else if (i == list->len) {
        node->next = NULL;
        node->prev = list->tail;

        if (list->tail != NULL) {
            list->tail->next = node;
        } else {
            list->head = node;
        }

        list->tail = node;
    } else {
        AlgNode *target;
        if (i <= (list->len + 1) / 2) {
            target = list->head;
            for (size_t j = 0; j < i - 1; j++) {
                target = target->next;
            }
        } else {
            target = list->tail;
            for (size_t j = list->len - 1; j > i; j--) {
                target = target->prev;
            }
        }

        node->next       = target->next;
        node->prev       = target;
        target->next     = node;
        node->next->prev = node;
    }

    list->len++;

    return true;
}

bool alg_linked_list_push_front(AlgLinkedList *list, alg_elem_t e) {
    return alg_linked_list_insert(list, 0, e);
}

bool alg_linked_list_push_back(AlgLinkedList *list, alg_elem_t e) {
    return list != NULL && alg_linked_list_insert(list, list->len, e);
}

bool alg_linked_list_del(AlgLinkedList *list, size_t i, alg_elem_t *e) {
    if (alg_linked_list_is_empty(list) || i >= list->len) {
        return false;
    }

    AlgNode *node;
    if (i <= (list->len + 1) / 2) {
        node = list->head;
        for (size_t j = 0; j < i; j++) {
            node = node->next;
        }
    } else {
        node = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            node = node->prev;
        }
    }

    if (e != NULL) {
        *e = node->data;
    }

    if (node->prev == NULL) {
        list->head = node->next;
    } else {
        node->prev->next = node->next;
    }

    if (node->next == NULL) {
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }

    list->len--;
    free(node);

    return true;
}

bool alg_linked_list_pop_front(AlgLinkedList *list, alg_elem_t *e) {
    return alg_linked_list_del(list, 0, e);
}

bool alg_linked_list_pop_back(AlgLinkedList *list, alg_elem_t *e) {
    return !alg_linked_list_is_empty(list) &&
           alg_linked_list_del(list, list->len - 1, e);
}

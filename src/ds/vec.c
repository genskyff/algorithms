#include "vec.h"
#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

Vec *create(void) {
    return init(0);
}

Vec *init(size_t n, ...) {
    Vec *v = (Vec *)malloc(sizeof(Vec));
    if (v == NULL) {
        return NULL;
    }

    size_t  cap  = n < INIT_CAP ? INIT_CAP : n * EXTEND_RATIO;
    elem_t *data = (elem_t *)malloc(cap * sizeof(elem_t));
    if (data == NULL) {
        free(v);
        return NULL;
    }

    v->len  = 0;
    v->cap  = cap;
    v->data = data;

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        v->data[v->len++] = va_arg(ap, elem_t);
    }

    va_end(ap);

    return v;
}

void show(FILE *stream, Vec *v) {
    if (v != NULL) {
        _show(stream, v->data, v->len);
    }
}

void clear(Vec *v) {
    if (v != NULL) {
        v->len = 0;
    }
}

bool is_empty(Vec *v) {
    return v == NULL || v->len == 0 ? true : false;
}

bool get(Vec *v, size_t i, elem_t *e) {
    if (v == NULL || v->len == 0 || i >= v->len) {
        return false;
    }

    if (e != NULL) {
        *e = v->data[i];
    }

    return true;
}

bool set(Vec *v, size_t i, elem_t e) {
    if (v == NULL || v->len == 0 || i >= v->len) {
        return false;
    }

    v->data[i] = e;

    return true;
}

bool find(Vec *v, elem_t e, size_t *i) {
    return v != NULL && _find(v->data, v->len, e, i);
}

bool insert(Vec *v, size_t i, elem_t e) {
    if (v == NULL || i > v->len) {
        return false;
    }

    if (v->len == v->cap) {
        size_t  new_cap  = v->cap * EXTEND_RATIO;
        elem_t *new_data = (elem_t *)realloc(v->data, new_cap * sizeof(elem_t));
        if (new_data == NULL) {
            return false;
        }

        v->cap  = new_cap;
        v->data = new_data;
    }

    if (i < v->len) {
        _move_right_slice(v->data, v->len, i, v->len, 1);
    }

    v->data[i] = e;
    v->len++;

    return true;
}

bool push(Vec *v, elem_t e) {
    return v != NULL && insert(v, v->len, e);
}

bool del(Vec *v, size_t i, elem_t *e) {
    if (v == NULL || v->len == 0 || i >= v->len) {
        return false;
    }

    if (e != NULL) {
        *e = v->data[i];
    }

    if (i < v->len - 1) {
        _move_left_slice(v->data, v->len, i, v->len, 1);
    }

    v->len--;

    if (v->len > 0 && v->cap >= 4 * INIT_CAP && v->len <= v->cap / 4) {
        size_t  new_cap  = v->cap / 2;
        elem_t *new_data = (elem_t *)realloc(v->data, new_cap * sizeof(elem_t));
        if (new_data != NULL) {
            v->data = new_data;
            v->cap  = new_cap;
        }
    }

    return true;
}

bool pop(Vec *v, elem_t *e) {
    if (v == NULL || v->len == 0) {
        return false;
    } else {
        return del(v, v->len - 1, e);
    }
}

void defer(Vec **v) {
    if (v != NULL && *v != NULL) {
        free((*v)->data);
        free(*v);
        *v = NULL;
    }
}

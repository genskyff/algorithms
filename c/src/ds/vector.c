#include "alg/ds/vector.h"
#include "utils.h"
#include <stdarg.h>
#include <stdlib.h>

bool _shrink(Vec *v);
bool _grow(Vec *v);

bool _shrink(Vec *v) {
    if (v != NULL && v->cap > SHRINK_CAP &&
        v->len < (size_t)(v->cap * LOW_FACTOR)) {
        size_t  base_cap = MAX(INIT_CAP, v->len * GROWTH_FACTOR);
        size_t  new_cap  = (base_cap + INIT_CAP - 1) / INIT_CAP * INIT_CAP;
        elem_t *new_data = (elem_t *)realloc(v->data, new_cap * sizeof(elem_t));
        if (new_data != NULL) {
            v->data = new_data;
            v->cap  = new_cap;
            return true;
        }
    }

    return false;
}

bool _grow(Vec *v) {
    if (v != NULL && v->len == v->cap) {
        size_t  new_cap  = v->cap * GROWTH_FACTOR;
        elem_t *new_data = (elem_t *)realloc(v->data, new_cap * sizeof(elem_t));
        if (new_data != NULL) {
            v->data = new_data;
            v->cap  = new_cap;

            return true;
        }
    }

    return false;
}

Vec create(void) {
    return create_with(INIT_CAP);
}

Vec create_with(size_t cap) {
    if (cap == 0) {
        fprintf(stderr, "\x1b[1;31merror: \x1b[0mcapacity cannot be 0 (exec "
                        "\x1b[33mcreate_with\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    elem_t *data = (elem_t *)malloc(cap * sizeof(elem_t));
    _has_alloc_err(data, __func__);

    Vec v = {.data = data, .len = 0, .cap = cap};

    return v;
}

Vec init(size_t n, ...) {
    size_t cap =
        n < INIT_CAP ? INIT_CAP : (n + INIT_CAP - 1) / INIT_CAP * INIT_CAP;
    elem_t *data = (elem_t *)malloc(cap * sizeof(elem_t));
    _has_alloc_err(data, __func__);

    Vec v = {.data = data, .len = 0, .cap = cap};

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        v.data[v.len++] = va_arg(ap, elem_t);
    }

    va_end(ap);

    return v;
}

void swap(Vec *v, size_t i, size_t j) {
    if (v != NULL && MAX(i, j) < v->len) {
        _swap(v->data, i, j);
    }
}

void reverse(Vec *v) {
    if (v != NULL) {
        _reverse(v->data, v->len);
    }
}

void show(FILE *stream, Vec *v) {
    if (v != NULL) {
        _show(stream, v->data, v->len, NULL);
    } else {
        _show(stream, NULL, 0, NULL);
    }
}

void clear(Vec *v) {
    if (v != NULL) {
        v->len = 0;
        _shrink(v);
    }
}

bool is_empty(Vec *v) {
    return v == NULL || v->len == 0;
}

bool get(Vec *v, size_t i, elem_t *e) {
    if (is_empty(v) || i >= v->len) {
        return false;
    }

    if (e != NULL) {
        *e = v->data[i];
    }

    return true;
}

bool first(Vec *v, elem_t *e) {
    return get(v, 0, e);
}

bool last(Vec *v, elem_t *e) {
    return !is_empty(v) && get(v, v->len - 1, e);
}

bool set(Vec *v, size_t i, elem_t e) {
    if (is_empty(v) || i >= v->len) {
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

    if (v->len == v->cap && !_grow(v)) {
        return false;
    }

    if (i < v->len) {
        _move_right_slice(v->data, v->len, i, v->len, 1);
    }

    v->data[i] = e;
    v->len++;

    return true;
}

bool push_front(Vec *v, elem_t e) {
    return insert(v, 0, e);
}

bool push_back(Vec *v, elem_t e) {
    return v != NULL && insert(v, v->len, e);
}

bool del(Vec *v, size_t i, elem_t *e) {
    if (is_empty(v) || i >= v->len) {
        return false;
    }

    if (e != NULL) {
        *e = v->data[i];
    }

    if (i < v->len - 1) {
        _move_left_slice(v->data, v->len, i, v->len, 1);
    }

    v->len--;
    _shrink(v);

    return true;
}

bool pop_front(Vec *v, elem_t *e) {
    return del(v, 0, e);
}

bool pop_back(Vec *v, elem_t *e) {
    return !is_empty(v) && del(v, v->len - 1, e);
}

void drop(Vec *v) {
    if (v != NULL) {
        free(v->data);
        v->data = NULL;
        v->len  = 0;
        v->cap  = 0;
    }
}

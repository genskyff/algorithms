#include "alg/ds/vector.h"
#include "internal/utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static void vec_shrink(AlgVec *v);
static void vec_grow(AlgVec *v);

static void vec_shrink(AlgVec *v) {
    if (v != NULL && v->cap > ALG_VEC_SHRINK_CAP &&
        v->len < (size_t)(v->cap * ALG_VEC_LOW_FACTOR)) {
        size_t base_cap =
            ALG_INTERNAL_MAX(ALG_VEC_INIT_CAP, v->len * ALG_VEC_GROWTH_FACTOR);
        size_t new_cap = (base_cap + ALG_VEC_INIT_CAP - 1) / ALG_VEC_INIT_CAP *
                         ALG_VEC_INIT_CAP;
        v->data = (alg_elem_t *)realloc(v->data, new_cap * sizeof(alg_elem_t));
        v->cap  = new_cap;
    }
}

static void vec_grow(AlgVec *v) {
    if (v != NULL && v->len == v->cap) {
        size_t new_cap = v->cap * ALG_VEC_GROWTH_FACTOR;
        v->data = (alg_elem_t *)realloc(v->data, new_cap * sizeof(alg_elem_t));
        v->cap  = new_cap;
    }
}

AlgVec alg_vec_create(void) {
    return alg_vec_create_with(ALG_VEC_INIT_CAP);
}

AlgVec alg_vec_create_with(size_t cap) {
    if (cap == 0) {
        fprintf(stderr, "\x1b[1;31merror: \x1b[0mcapacity cannot be 0 (exec "
                        "\x1b[33mcreate_with\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    alg_elem_t *data = (alg_elem_t *)malloc(cap * sizeof(alg_elem_t));

    AlgVec v = {.data = data, .len = 0, .cap = cap};

    return v;
}

AlgVec alg_vec_init(size_t n, ...) {
    size_t cap = n < ALG_VEC_INIT_CAP ? ALG_VEC_INIT_CAP
                                      : (n + ALG_VEC_INIT_CAP - 1) /
                                            ALG_VEC_INIT_CAP * ALG_VEC_INIT_CAP;
    alg_elem_t *data = (alg_elem_t *)malloc(cap * sizeof(alg_elem_t));

    AlgVec v = {.data = data, .len = 0, .cap = cap};

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        v.data[v.len++] = va_arg(ap, alg_elem_t);
    }

    va_end(ap);

    return v;
}

void alg_vec_swap(AlgVec *v, size_t i, size_t j) {
    if (v != NULL && ALG_INTERNAL_MAX(i, j) < v->len) {
        alg_internal_swap(v->data, i, j);
    }
}

void alg_vec_reverse(AlgVec *v) {
    if (v != NULL) {
        alg_internal_reverse(v->data, v->len);
    }
}

void alg_vec_show(FILE *stream, AlgVec *v) {
    if (v != NULL) {
        alg_internal_show(stream, v->data, v->len, NULL);
    } else {
        alg_internal_show(stream, NULL, 0, NULL);
    }
}

void alg_vec_clear(AlgVec *v) {
    if (v != NULL) {
        v->len = 0;
        vec_shrink(v);
    }
}

bool alg_vec_is_empty(AlgVec *v) {
    return v == NULL || v->len == 0;
}

bool alg_vec_get(AlgVec *v, size_t i, alg_elem_t *e) {
    if (alg_vec_is_empty(v) || i >= v->len) {
        return false;
    }

    if (e != NULL) {
        *e = v->data[i];
    }

    return true;
}

bool alg_vec_first(AlgVec *v, alg_elem_t *e) {
    return alg_vec_get(v, 0, e);
}

bool alg_vec_last(AlgVec *v, alg_elem_t *e) {
    return !alg_vec_is_empty(v) && alg_vec_get(v, v->len - 1, e);
}

bool alg_vec_set(AlgVec *v, size_t i, alg_elem_t e) {
    if (alg_vec_is_empty(v) || i >= v->len) {
        return false;
    }

    v->data[i] = e;

    return true;
}

bool alg_vec_find(AlgVec *v, alg_elem_t e, size_t *i) {
    return v != NULL && alg_internal_find(v->data, v->len, e, i);
}

bool alg_vec_insert(AlgVec *v, size_t i, alg_elem_t e) {
    if (v == NULL || i > v->len) {
        return false;
    }

    if (v->len == v->cap) {
        vec_grow(v);
    }

    if (i < v->len) {
        alg_internal_move_right_slice(v->data, v->len, i, v->len, 1);
    }

    v->data[i] = e;
    v->len++;

    return true;
}

bool alg_vec_push_front(AlgVec *v, alg_elem_t e) {
    return alg_vec_insert(v, 0, e);
}

bool alg_vec_push_back(AlgVec *v, alg_elem_t e) {
    return v != NULL && alg_vec_insert(v, v->len, e);
}

bool alg_vec_del(AlgVec *v, size_t i, alg_elem_t *e) {
    if (alg_vec_is_empty(v) || i >= v->len) {
        return false;
    }

    if (e != NULL) {
        *e = v->data[i];
    }

    if (i < v->len - 1) {
        alg_internal_move_left_slice(v->data, v->len, i, v->len, 1);
    }

    v->len--;
    vec_shrink(v);

    return true;
}

bool alg_vec_pop_front(AlgVec *v, alg_elem_t *e) {
    return alg_vec_del(v, 0, e);
}

bool alg_vec_pop_back(AlgVec *v, alg_elem_t *e) {
    return !alg_vec_is_empty(v) && alg_vec_del(v, v->len - 1, e);
}

void alg_vec_drop(AlgVec *v) {
    if (v != NULL) {
        free(v->data);
        v->data = NULL;
        v->len  = 0;
        v->cap  = 0;
    }
}

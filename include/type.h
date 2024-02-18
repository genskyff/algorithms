#ifndef TYPE_H
#define TYPE_H

#include <stddef.h>

typedef int elem_t;

typedef struct {
    elem_t *data;
    size_t  len;
} Array;

typedef struct {
    elem_t *data;
    size_t  len;
} List;

#define ARRAY(...)                                                             \
    ((Array){.data = (elem_t[]){__VA_ARGS__},                                  \
             .len  = sizeof((elem_t[]){__VA_ARGS__}) / sizeof(elem_t)})

#define INIT_ARRAY(_LEN) ((Array){.data = (elem_t[(_LEN)]){}, .len = (_LEN)})

#endif

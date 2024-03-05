#ifndef HASHMAP_H
#define HASHMAP_H

#include "type.h"
#include <stdbool.h>

#define INIT_CAP      100
#define LOAD_FACTOR   0.75
#define GROWTH_FACTOR 2

typedef size_t key_t;
typedef elem_t value_t;

typedef struct {
    key_t   key;
    value_t value;
} Pair;

typedef struct {
    Pair  *bucket;
    size_t len;
    size_t cap;
} HashMap;

HashMap create(void);
HashMap init(key_t *keys, value_t *values, size_t len);
void    show_key_value(FILE *stream, HashMap *map);
void    show_key(FILE *stream, HashMap *map);
void    show_value(FILE *stream, HashMap *map);
void    clear(HashMap *map);
bool    is_empty(HashMap *map);
bool    get(HashMap *map, key_t key, value_t *value);
bool    set(HashMap *map, key_t key, value_t value);
bool    insert(HashMap *map, key_t key, value_t value);
bool    del(HashMap *map, key_t key);
void    drop(HashMap *map);

#endif

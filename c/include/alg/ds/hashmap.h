#ifndef ALG_HASHMAP_H
#define ALG_HASHMAP_H

#include "alg/core.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef const char *alg_hashmap_key_t;
typedef alg_elem_t  alg_hashmap_value_t;

typedef struct AlgHashMapPair {
    alg_hashmap_key_t      key;
    alg_hashmap_value_t    value;
    struct AlgHashMapPair *next;
} AlgHashMapPair;

// separate chaining
typedef struct {
    AlgHashMapPair *head;
    size_t          len;
} AlgHashMapBucket;

typedef struct {
    AlgHashMapBucket *buckets;
    size_t            len;
    size_t            cap;
} AlgHashMap;

AlgHashMap alg_hashmap_create(void);
AlgHashMap alg_hashmap_create_with(size_t cap);
AlgHashMap alg_hashmap_init(const alg_hashmap_key_t   *keys,
                            const alg_hashmap_value_t *values, size_t len);
void       alg_hashmap_show(FILE *stream, const AlgHashMap *map);
void       alg_hashmap_show_keys(FILE *stream, const AlgHashMap *map);
void       alg_hashmap_show_values(FILE *stream, const AlgHashMap *map);
void       alg_hashmap_clear(AlgHashMap *map);
bool       alg_hashmap_is_empty(const AlgHashMap *map);
alg_hashmap_key_t   *alg_hashmap_get_keys(const AlgHashMap *map);
alg_hashmap_value_t *alg_hashmap_get_values(const AlgHashMap *map);
bool alg_hashmap_get(const AlgHashMap *map, alg_hashmap_key_t key,
                     alg_hashmap_value_t *value);
bool alg_hashmap_insert(AlgHashMap *map, alg_hashmap_key_t key,
                        alg_hashmap_value_t value);
bool alg_hashmap_del(AlgHashMap *map, alg_hashmap_key_t key);
void alg_hashmap_drop(AlgHashMap *map);

#endif

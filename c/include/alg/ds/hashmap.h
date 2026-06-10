#ifndef ALG_HASHMAP_H
#define ALG_HASHMAP_H

#include "alg/core.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define ALG_HASHMAP_INIT_CAP      100
#define ALG_HASHMAP_SHRINK_CAP    1000
#define ALG_HASHMAP_BUCKET_CAP    10
#define ALG_HASHMAP_LOW_FACTOR    0.25
#define ALG_HASHMAP_LOAD_FACTOR   0.75
#define ALG_HASHMAP_GROWTH_FACTOR 2

typedef char      *alg_hashmap_key_t;
typedef alg_elem_t alg_hashmap_value_t;

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

AlgHashMap           alg_hashmap_create(void);
AlgHashMap           alg_hashmap_create_with(size_t cap);
AlgHashMap           alg_hashmap_init(alg_hashmap_key_t   *keys,
                                      alg_hashmap_value_t *values, size_t len);
void                 alg_hashmap_show(FILE *stream, AlgHashMap *map);
void                 alg_hashmap_show_keys(FILE *stream, AlgHashMap *map);
void                 alg_hashmap_show_values(FILE *stream, AlgHashMap *map);
void                 alg_hashmap_clear(AlgHashMap *map);
bool                 alg_hashmap_is_empty(AlgHashMap *map);
alg_hashmap_key_t   *alg_hashmap_get_keys(AlgHashMap *map);
alg_hashmap_value_t *alg_hashmap_get_values(AlgHashMap *map);
bool                 alg_hashmap_get(AlgHashMap *map, alg_hashmap_key_t key,
                                     alg_hashmap_value_t *value);
bool                 alg_hashmap_insert(AlgHashMap *map, alg_hashmap_key_t key,
                                        alg_hashmap_value_t value);
bool                 alg_hashmap_del(AlgHashMap *map, alg_hashmap_key_t key);
void                 alg_hashmap_drop(AlgHashMap *map);

#endif

#include "alg/ds/hashmap.h"
#include "internal/utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*PrintFunc)(FILE *stream, AlgHashMapPair *p);
static void hashmap_print(FILE *stream, AlgHashMap *map, PrintFunc print_func,
                          const char *prefix, const char *suffix,
                          const char *sep);
static void hashmap_print_pair(FILE *stream, AlgHashMapPair *p);
static void hashmap_print_key(FILE *stream, AlgHashMapPair *p);
static void hashmap_print_value(FILE *stream, AlgHashMapPair *p);
static uint32_t        hashmap_hash_fnv1a_32(const char *str);
static uint64_t        hashmap_hash_fnv1a_64(const char *str);
static size_t          hashmap_hash(const char *str);
static bool            hashmap_migrate(AlgHashMap *map, size_t new_cap);
static bool            hashmap_shrink(AlgHashMap *map);
static bool            hashmap_grow(AlgHashMap *map);
static void            hashmap_clear_bucket(AlgHashMapBucket *bucket);
static bool            hashmap_is_empty_bucket(AlgHashMapBucket *bucket);
static AlgHashMapPair *hashmap_get_pair_bucket(AlgHashMapBucket *bucket,
                                               alg_hashmap_key_t key);
static bool            hashmap_insert_pair_bucket(AlgHashMapBucket   *bucket,
                                                  alg_hashmap_key_t   key,
                                                  alg_hashmap_value_t value);
static bool            hashmap_del_pair_bucket(AlgHashMapBucket *bucket,
                                               alg_hashmap_key_t key);

static void hashmap_print(FILE *stream, AlgHashMap *map, PrintFunc print_func,
                          const char *prefix, const char *suffix,
                          const char *sep) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (alg_hashmap_is_empty(map)) {
        fprintf(stream, "%s%s\n", prefix, suffix);
        return;
    }

    fprintf(stream, "%s", prefix);
    bool first_entry = true;
    for (size_t i = 0; i < map->cap; ++i) {
        AlgHashMapPair *p = map->buckets[i].head;
        if (p == NULL) {
            continue;
        }

        if (first_entry) {
            first_entry = false;
        } else {
            fprintf(stream, "%s", sep);
        }

        if (map->buckets[i].len > 1) {
            fprintf(stream, "%s", prefix);
        }

        while (p != NULL) {
            print_func(stream, p);
            if (p->next != NULL) {
                fprintf(stream, "%s", sep);
            }
            p = p->next;
        }

        if (map->buckets[i].len > 1) {
            fprintf(stream, "%s", suffix);
        }
    }
    fprintf(stream, "%s\n", suffix);
}

static void hashmap_print_pair(FILE *stream, AlgHashMapPair *p) {
    if (p != NULL) {
        fprintf(stream == NULL ? stdout : stream, "\"%s\": %d", p->key,
                p->value);
    }
}

static void hashmap_print_key(FILE *stream, AlgHashMapPair *p) {
    if (p != NULL) {
        fprintf(stream == NULL ? stdout : stream, "\"%s\"", p->key);
    }
}

static void hashmap_print_value(FILE *stream, AlgHashMapPair *p) {
    if (p != NULL) {
        fprintf(stream == NULL ? stdout : stream, "%d", p->value);
    }
}

// 32-bit FNV-1a hash
static uint32_t hashmap_hash_fnv1a_32(const char *str) {
    uint32_t prime        = 16777619U;
    uint32_t offset_basis = 2166136261U;
    uint32_t hash         = offset_basis;

    while (*str != '\0') {
        hash = hash ^ (uint8_t)*str;
        hash = hash * prime;
        str++;
    }

    return hash;
}

// 64-bit FNV-1a hash
static uint64_t hashmap_hash_fnv1a_64(const char *str) {
    uint64_t prime        = 1099511628211ULL;
    uint64_t offset_basis = 14695981039346656037ULL;
    uint64_t hash         = offset_basis;

    while (*str != '\0') {
        hash = hash ^ (uint8_t)*str;
        hash = hash * prime;
        str++;
    }

    return hash;
}

static size_t hashmap_hash(const char *str) {
    return sizeof(size_t) == 8 ? hashmap_hash_fnv1a_64(str)
                               : hashmap_hash_fnv1a_32(str);
}

static bool hashmap_migrate(AlgHashMap *map, size_t new_cap) {
    if (map != NULL && map->cap != 0 && map->cap != new_cap) {
        AlgHashMapBucket *new_buckets =
            (AlgHashMapBucket *)calloc(new_cap, sizeof(AlgHashMapBucket));
        if (new_buckets == NULL) {
            return false;
        }

        for (size_t i = 0; i < map->cap; ++i) {
            AlgHashMapPair *p = map->buckets[i].head;
            while (p != NULL) {
                size_t idx = (size_t)hashmap_hash(p->key) % new_cap;
                if (!hashmap_insert_pair_bucket(&new_buckets[idx], p->key,
                                                p->value)) {
                    for (size_t j = 0; j < new_cap; ++j) {
                        AlgHashMapPair *cur = new_buckets[j].head;
                        while (cur != NULL) {
                            AlgHashMapPair *to_free = cur;
                            cur                     = cur->next;
                            free(to_free);
                        }
                    }
                    free(new_buckets);
                    return false;
                }
                p = p->next;
            }
        }

        free(map->buckets);
        map->buckets = new_buckets;
        map->cap     = new_cap;
    }

    return true;
}

static bool hashmap_shrink(AlgHashMap *map) {
    if (map != NULL && map->cap > ALG_HASHMAP_SHRINK_CAP &&
        map->len < (size_t)(map->cap * ALG_HASHMAP_LOW_FACTOR)) {
        size_t base_cap = ALG_INTERNAL_MAX(
            ALG_HASHMAP_INIT_CAP, map->len * ALG_HASHMAP_GROWTH_FACTOR);
        size_t new_cap = (base_cap + ALG_HASHMAP_INIT_CAP - 1) /
                         ALG_HASHMAP_INIT_CAP * ALG_HASHMAP_INIT_CAP;
        return hashmap_migrate(map, new_cap);
    }

    return false;
}

static bool hashmap_grow(AlgHashMap *map) {
    if (map != NULL && map->len > map->cap * ALG_HASHMAP_LOAD_FACTOR) {
        size_t new_cap = map->cap * ALG_HASHMAP_GROWTH_FACTOR;
        return hashmap_migrate(map, new_cap);
    }

    return false;
}

static void hashmap_clear_bucket(AlgHashMapBucket *bucket) {
    if (bucket != NULL) {
        AlgHashMapPair *p = bucket->head;
        while (p != NULL) {
            AlgHashMapPair *tmp = p;
            p                   = p->next;
            free(tmp);
        }
        bucket->head = NULL;
        bucket->len  = 0;
    }
}

static bool hashmap_is_empty_bucket(AlgHashMapBucket *bucket) {
    return bucket == NULL || bucket->head == NULL || bucket->len == 0;
}

static AlgHashMapPair *hashmap_get_pair_bucket(AlgHashMapBucket *bucket,
                                               alg_hashmap_key_t key) {
    if (hashmap_is_empty_bucket(bucket)) {
        return NULL;
    }

    AlgHashMapPair *p = bucket->head;
    while (p != NULL) {
        if (alg_internal_cmp_str(p->key, key) == 0) {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

static bool hashmap_insert_pair_bucket(AlgHashMapBucket   *bucket,
                                       alg_hashmap_key_t   key,
                                       alg_hashmap_value_t value) {
    if (bucket == NULL || key == NULL) {
        return false;
    }

    AlgHashMapPair *p = hashmap_get_pair_bucket(bucket, key);
    if (p != NULL) {
        p->value = value;
        return true;
    }

    AlgHashMapPair *new_pair = (AlgHashMapPair *)malloc(sizeof(AlgHashMapPair));
    if (new_pair == NULL) {
        return false;
    }

    new_pair->key   = key;
    new_pair->value = value;
    new_pair->next  = bucket->head;
    bucket->head    = new_pair;
    bucket->len++;

    return true;
}

static bool hashmap_del_pair_bucket(AlgHashMapBucket *bucket,
                                    alg_hashmap_key_t key) {
    if (hashmap_is_empty_bucket(bucket) || key == NULL) {
        return false;
    }

    AlgHashMapPair *p = bucket->head;
    if (alg_internal_cmp_str(p->key, key) == 0) {
        bucket->head = p->next;
        free(p);
        bucket->len--;
        return true;
    }

    while (p->next != NULL) {
        if (alg_internal_cmp_str(p->next->key, key) == 0) {
            AlgHashMapPair *tmp = p->next;
            p->next             = p->next->next;
            free(tmp);
            bucket->len--;
            return true;
        }
        p = p->next;
    }

    return false;
}

AlgHashMap alg_hashmap_create(void) {
    return alg_hashmap_create_with(ALG_HASHMAP_INIT_CAP);
}

AlgHashMap alg_hashmap_create_with(size_t cap) {
    if (cap == 0) {
        fprintf(stderr, "\x1b[1;31merror: \x1b[0mcapacity cannot be 0 (exec "
                        "\x1b[33mcreate_with\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    AlgHashMapBucket *buckets =
        (AlgHashMapBucket *)calloc(cap, sizeof(AlgHashMapBucket));
    alg_internal_has_alloc_err(buckets, __func__);

    AlgHashMap map = {.buckets = buckets, .len = 0, .cap = cap};

    return map;
}

AlgHashMap alg_hashmap_init(alg_hashmap_key_t   *keys,
                            alg_hashmap_value_t *values, size_t len) {
    size_t cap =
        keys == NULL || values == NULL ||
                len < (size_t)(ALG_HASHMAP_INIT_CAP * ALG_HASHMAP_LOAD_FACTOR)
            ? ALG_HASHMAP_INIT_CAP
            : (ALG_INTERNAL_MAX(len, ALG_HASHMAP_INIT_CAP) +
               ALG_HASHMAP_INIT_CAP - 1) /
                  ALG_HASHMAP_INIT_CAP * ALG_HASHMAP_INIT_CAP;

    AlgHashMapBucket *buckets =
        (AlgHashMapBucket *)calloc(cap, sizeof(AlgHashMapBucket));
    alg_internal_has_alloc_err(buckets, __func__);

    AlgHashMap map = {.buckets = buckets, .len = 0, .cap = cap};

    if (keys == NULL || values == NULL || len == 0) {
        return map;
    }

    for (size_t i = 0; i < len; i++) {
        size_t idx = (size_t)hashmap_hash(keys[i]) % cap;

        bool has_key = false;
        if (map.buckets[idx].head != NULL) {
            AlgHashMapPair *cur = map.buckets[idx].head;
            while (cur != NULL) {
                if (cur->key == keys[i]) {
                    cur->value = values[i];
                    has_key    = true;
                    break;
                }
                cur = cur->next;
            }
        }

        if (!has_key) {
            AlgHashMapPair *p =
                (AlgHashMapPair *)malloc(sizeof(AlgHashMapPair));
            if (p == NULL) {
                return map;
            }

            p->key                = keys[i];
            p->value              = values[i];
            p->next               = map.buckets[idx].head;
            map.buckets[idx].head = p;
            map.buckets[idx].len++;
            map.len++;
        }
    }

    return map;
}

void alg_hashmap_show(FILE *stream, AlgHashMap *map) {
    hashmap_print(stream, map, hashmap_print_pair, "{", "}", ", ");
}

void alg_hashmap_show_keys(FILE *stream, AlgHashMap *map) {
    hashmap_print(stream, map, hashmap_print_key, "[", "]", ", ");
}

void alg_hashmap_show_values(FILE *stream, AlgHashMap *map) {
    hashmap_print(stream, map, hashmap_print_value, "[", "]", ", ");
}

void alg_hashmap_clear(AlgHashMap *map) {
    if (map == NULL) {
        return;
    }

    for (size_t i = 0; i < map->cap; ++i) {
        AlgHashMapPair *p = map->buckets[i].head;
        while (p != NULL) {
            AlgHashMapPair *tmp = p;
            p                   = p->next;
            free(tmp);
        }
        map->buckets[i].head = NULL;
    }
    map->len = 0;
    hashmap_shrink(map);
}

bool alg_hashmap_is_empty(AlgHashMap *map) {
    return map == NULL || map->len == 0;
}

alg_hashmap_key_t *alg_hashmap_get_keys(AlgHashMap *map) {
    if (map == NULL || map->len == 0) {
        return NULL;
    }

    alg_hashmap_key_t *keys =
        (alg_hashmap_key_t *)malloc(map->len * sizeof(alg_hashmap_key_t));
    if (keys == NULL) {
        return NULL;
    }

    for (size_t i = 0, idx = 0; i < map->cap; ++i) {
        AlgHashMapPair *p = map->buckets[i].head;
        while (p != NULL) {
            keys[idx++] = p->key;
            p           = p->next;
        }
    }

    return keys;
}

alg_hashmap_value_t *alg_hashmap_get_values(AlgHashMap *map) {
    if (map == NULL || map->len == 0) {
        return NULL;
    }

    alg_hashmap_value_t *values =
        (alg_hashmap_value_t *)malloc(map->len * sizeof(alg_hashmap_value_t));
    if (values == NULL) {
        return NULL;
    }

    for (size_t i = 0, idx = 0; i < map->cap; ++i) {
        AlgHashMapPair *p = map->buckets[i].head;
        while (p != NULL) {
            values[idx++] = p->value;
            p             = p->next;
        }
    }

    return values;
}

bool alg_hashmap_get(AlgHashMap *map, alg_hashmap_key_t key,
                     alg_hashmap_value_t *value) {
    if (map == NULL || map->len == 0) {
        return false;
    }

    size_t          idx = (size_t)hashmap_hash(key) % map->cap;
    AlgHashMapPair *p   = map->buckets[idx].head;
    while (p != NULL) {
        if (alg_internal_cmp_str(p->key, key) == 0) {
            if (value != NULL) {
                *value = p->value;
            }
            return true;
        }
        p = p->next;
    }

    return false;
}

bool alg_hashmap_insert(AlgHashMap *map, alg_hashmap_key_t key,
                        alg_hashmap_value_t value) {
    if (map == NULL) {
        return false;
    }

    if (map->len > map->cap * ALG_HASHMAP_LOAD_FACTOR && !hashmap_grow(map)) {
        return false;
    }

    size_t idx = (size_t)hashmap_hash(key) % map->cap;
    if (!hashmap_insert_pair_bucket(&map->buckets[idx], key, value)) {
        return false;
    }
    map->len++;

    if (map->buckets[idx].len > ALG_HASHMAP_BUCKET_CAP) {
        hashmap_grow(map);
    }

    return true;
}

bool alg_hashmap_del(AlgHashMap *map, alg_hashmap_key_t key) {
    if (alg_hashmap_is_empty(map)) {
        return false;
    }

    size_t            idx    = (size_t)hashmap_hash(key) % map->cap;
    AlgHashMapBucket *bucket = &map->buckets[idx];
    if (hashmap_del_pair_bucket(bucket, key)) {
        map->len--;
        hashmap_shrink(map);
        return true;
    }

    return false;
}

void alg_hashmap_drop(AlgHashMap *map) {
    if (map == NULL) {
        return;
    }

    for (size_t i = 0; i < map->cap; ++i) {
        hashmap_clear_bucket(&map->buckets[i]);
    }

    free(map->buckets);
    map->buckets = NULL;
    map->len     = 0;
    map->cap     = 0;
}

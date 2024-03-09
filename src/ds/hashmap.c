#include "hashmap.h"
#include "util.h"
#include <stdint.h>
#include <stdlib.h>

typedef void (*PrintFunc)(FILE *stream, Pair *p);
void     _print(FILE *stream, HashMap *map, PrintFunc print_func,
                const char *prefix, const char *suffix, const char *sep);
void     _print_pair(FILE *stream, Pair *p);
void     _print_key(FILE *stream, Pair *p);
void     _print_value(FILE *stream, Pair *p);
uint32_t _hash_fnv1a_32(const char *str);
uint64_t _hash_fnv1a_64(const char *str);
size_t   _hash(const char *str);
bool     _migrate(HashMap *map, size_t new_cap);
bool     _shrink(HashMap *map);
bool     _grow(HashMap *map);
void     _clear_bucket(Bucket *bucket);
bool     _is_empty_bucket(Bucket *bucket);
Pair    *_get_pair_bucket(Bucket *bucket, key_t key);
bool     _insert_pair_bucket(Bucket *bucket, key_t key, value_t value);
bool     _del_pair_bucket(Bucket *bucket, key_t key);

void _print(FILE *stream, HashMap *map, PrintFunc print_func,
            const char *prefix, const char *suffix, const char *sep) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (is_empty(map)) {
        fprintf(stream, "%s%s\n", prefix, suffix);
        return;
    }

    fprintf(stream, "%s", prefix);
    bool first_entry = true;
    for (size_t i = 0; i < map->cap; ++i) {
        Pair *p = map->buckets[i].head;
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

void _print_pair(FILE *stream, Pair *p) {
    if (p != NULL) {
        fprintf(stream == NULL ? stdout : stream, "\"%s\": %d", p->key,
                p->value);
    }
}

void _print_key(FILE *stream, Pair *p) {
    if (p != NULL) {
        fprintf(stream == NULL ? stdout : stream, "\"%s\"", p->key);
    }
}

void _print_value(FILE *stream, Pair *p) {
    if (p != NULL) {
        fprintf(stream == NULL ? stdout : stream, "%d", p->value);
    }
}

// 32-bit FNV-1a hash
uint32_t _hash_fnv1a_32(const char *str) {
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
uint64_t _hash_fnv1a_64(const char *str) {
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

size_t _hash(const char *str) {
    return sizeof(size_t) == 4 ? _hash_fnv1a_32(str) : _hash_fnv1a_64(str);
}

bool _migrate(HashMap *map, size_t new_cap) {
    if (map != NULL && map->cap != 0 && map->cap != new_cap) {
        Bucket *new_buckets = (Bucket *)calloc(new_cap, sizeof(Bucket));
        if (new_buckets == NULL) {
            return false;
        }

        for (size_t i = 0; i < map->cap; ++i) {
            Pair *p = map->buckets[i].head;
            while (p != NULL) {
                size_t idx = (size_t)_hash(p->key) % new_cap;
                if (!_insert_pair_bucket(&new_buckets[idx], p->key, p->value)) {
                    for (size_t j = 0; j < new_cap; ++j) {
                        Pair *cur = new_buckets[j].head;
                        while (cur != NULL) {
                            Pair *to_free = cur;
                            cur           = cur->next;
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

bool _shrink(HashMap *map) {
    if (map != NULL && map->cap > SHINK_CAP &&
        map->len < (size_t)(map->cap * LOW_FACTOR)) {
        size_t base_cap = MAX(INIT_CAP, map->len * GROWTH_FACTOR);
        size_t new_cap  = (base_cap + INIT_CAP - 1) / INIT_CAP * INIT_CAP;
        return _migrate(map, new_cap);
    }

    return false;
}

bool _grow(HashMap *map) {
    if (map != NULL && map->len > map->cap * LOAD_FACTOR) {
        size_t new_cap = map->cap * GROWTH_FACTOR;
        return _migrate(map, new_cap);
    }

    return false;
}

void _clear_bucket(Bucket *bucket) {
    if (bucket != NULL) {
        Pair *p = bucket->head;
        while (p != NULL) {
            Pair *tmp = p;
            p         = p->next;
            free(tmp);
        }
        bucket->head = NULL;
        bucket->len  = 0;
    }
}

bool _is_empty_bucket(Bucket *bucket) {
    return bucket == NULL || bucket->head == NULL || bucket->len == 0;
}

Pair *_get_pair_bucket(Bucket *bucket, key_t key) {
    if (_is_empty_bucket(bucket)) {
        return NULL;
    }

    Pair *p = bucket->head;
    while (p != NULL) {
        if (_cmp_str(p->key, key) == 0) {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

bool _insert_pair_bucket(Bucket *bucket, key_t key, value_t value) {
    if (bucket == NULL || key == NULL) {
        return false;
    }

    Pair *p = _get_pair_bucket(bucket, key);
    if (p != NULL) {
        p->value = value;
        return true;
    }

    Pair *new_pair = (Pair *)malloc(sizeof(Pair));
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

bool _del_pair_bucket(Bucket *bucket, key_t key) {
    if (_is_empty_bucket(bucket) || key == NULL) {
        return false;
    }

    Pair *p = bucket->head;
    if (_cmp_str(p->key, key) == 0) {
        bucket->head = p->next;
        free(p);
        bucket->len--;
        return true;
    }

    while (p->next != NULL) {
        if (_cmp_str(p->next->key, key) == 0) {
            Pair *tmp = p->next;
            p->next   = p->next->next;
            free(tmp);
            bucket->len--;
            return true;
        }
        p = p->next;
    }

    return false;
}

HashMap create(void) {
    return create_with(INIT_CAP);
}

HashMap create_with(size_t cap) {
    if (cap == 0) {
        fprintf(stderr, "\x1b[1;31merror: \x1b[0mcapacity cannot be 0 (exec "
                        "\x1b[33mcreate_with\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    Bucket *buckets = (Bucket *)calloc(cap, sizeof(Bucket));
    if (buckets == NULL) {
        fprintf(stderr,
                "\x1b[1;31merror: \x1b[0mfailed to allocate memory (exec "
                "\x1b[33mcreate_with\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    HashMap map = {.buckets = buckets, .len = 0, .cap = cap};

    return map;
}

HashMap init(key_t *keys, value_t *values, size_t len) {
    size_t cap =
        keys == NULL || values == NULL || len < (size_t)(INIT_CAP * LOAD_FACTOR)
            ? INIT_CAP
            : (MAX(len, INIT_CAP) + INIT_CAP - 1) / INIT_CAP * INIT_CAP;

    Bucket *buckets = (Bucket *)calloc(cap, sizeof(Bucket));
    if (buckets == NULL) {
        fprintf(stderr,
                "\x1b[1;31merror: \x1b[0mfailed to allocate memory (exec "
                "\x1b[33minit\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    HashMap map = {.buckets = buckets, .len = 0, .cap = cap};

    if (keys == NULL || values == NULL || len == 0) {
        return map;
    }

    for (size_t i = 0; i < len; i++) {
        size_t idx = (size_t)_hash(keys[i]) % cap;

        bool has_key = false;
        if (map.buckets[idx].head != NULL) {
            Pair *cur = map.buckets[idx].head;
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
            Pair *p = (Pair *)malloc(sizeof(Pair));
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

void show(FILE *stream, HashMap *map) {
    _print(stream, map, _print_pair, "{", "}", ", ");
}

void show_keys(FILE *stream, HashMap *map) {
    _print(stream, map, _print_key, "[", "]", ", ");
}

void show_values(FILE *stream, HashMap *map) {
    _print(stream, map, _print_value, "[", "]", ", ");
}

void clear(HashMap *map) {
    if (map == NULL) {
        return;
    }

    for (size_t i = 0; i < map->cap; ++i) {
        Pair *p = map->buckets[i].head;
        while (p != NULL) {
            Pair *tmp = p;
            p         = p->next;
            free(tmp);
        }
        map->buckets[i].head = NULL;
    }
    map->len = 0;
}

bool is_empty(HashMap *map) {
    return map == NULL || map->len == 0;
}

key_t *get_keys(HashMap *map) {
    if (map == NULL || map->len == 0) {
        return NULL;
    }

    key_t *keys = (key_t *)malloc(map->len * sizeof(key_t));
    if (keys == NULL) {
        return NULL;
    }

    for (size_t i = 0, idx = 0; i < map->cap; ++i) {
        Pair *p = map->buckets[i].head;
        while (p != NULL) {
            keys[idx++] = p->key;
            p           = p->next;
        }
    }

    return keys;
}

value_t *get_values(HashMap *map) {
    if (map == NULL || map->len == 0) {
        return NULL;
    }

    value_t *values = (value_t *)malloc(map->len * sizeof(value_t));
    if (values == NULL) {
        return NULL;
    }

    for (size_t i = 0, idx = 0; i < map->cap; ++i) {
        Pair *p = map->buckets[i].head;
        while (p != NULL) {
            values[idx++] = p->value;
            p             = p->next;
        }
    }

    return values;
}

bool get(HashMap *map, key_t key, value_t *value) {
    if (map == NULL || map->len == 0) {
        return false;
    }

    size_t idx = (size_t)_hash(key) % map->cap;
    Pair  *p   = map->buckets[idx].head;
    while (p != NULL) {
        if (_cmp_str(p->key, key) == 0) {
            if (value != NULL) {
                *value = p->value;
            }
            return true;
        }
        p = p->next;
    }

    return false;
}

bool insert(HashMap *map, key_t key, value_t value) {
    if (map == NULL) {
        return false;
    }

    if (map->len > map->cap * LOAD_FACTOR && !_grow(map)) {
        return false;
    }

    size_t idx = (size_t)_hash(key) % map->cap;
    if (map->buckets[idx].len > BUCKET_CAP && !_grow(map)) {
        return false;
    }

    if (!_insert_pair_bucket(&map->buckets[idx], key, value)) {
        return false;
    }

    map->len++;

    return true;
}

bool del(HashMap *map, key_t key) {
    if (is_empty(map)) {
        return false;
    }

    size_t  idx    = (size_t)_hash(key) % map->cap;
    Bucket *bucket = &map->buckets[idx];
    if (_del_pair_bucket(bucket, key)) {
        map->len--;
        _shrink(map);
        return true;
    }

    return false;
}

void drop(HashMap *map) {
    if (map == NULL) {
        return;
    }

    for (size_t i = 0; i < map->cap; ++i) {
        _clear_bucket(&map->buckets[i]);
    }

    free(map->buckets);
    map->buckets = NULL;
    map->len     = 0;
    map->cap     = 0;
}

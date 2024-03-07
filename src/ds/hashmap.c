#include "hashmap.h"
#include <stdlib.h>

typedef void (*PrintFunc)(FILE *stream, Pair *p);
void _print(FILE *stream, HashMap *map, PrintFunc print_func,
            const char *prefix, const char *suffix, const char *sep) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (map == NULL || map->len == 0) {
        fprintf(stream, "%s%s\n", prefix, suffix);
        return;
    }

    fprintf(stream, "%s", prefix);
    bool is_first = true;
    for (size_t i = 0; i < map->cap; ++i) {
        Pair *p             = map->bucket[i];
        bool  has_conflict  = false;
        bool  is_turn_first = true;
        while (p != NULL) {
            if (is_first) {
                is_first = false;
            } else {
                fprintf(stream, "%s", sep);
            }

            if (is_turn_first) {
                is_turn_first = false;
                has_conflict  = p->next != NULL;
                if (has_conflict) {
                    fprintf(stream, "%s", prefix);
                }
            } else {
                has_conflict = true;
            }

            print_func(stream, p);
            p = p->next;
        }
        if (has_conflict) {
            fprintf(stream, "%s", suffix);
        }
    }
    fprintf(stream, "%s\n", suffix);
}

void _print_pair(FILE *stream, Pair *p) {
    fprintf(stream, "\"%s\": %d", p->key, p->value);
}

void _print_key(FILE *stream, Pair *p) {
    fprintf(stream, "\"%s\"", p->key);
}

void _print_value(FILE *stream, Pair *p) {
    fprintf(stream, "%d", p->value);
}

// FNV-1a hash
uint64_t _hash(const char *str) {
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

HashMap create(void) {
    return init(NULL, NULL, 0);
}

HashMap init(key_t *keys, value_t *values, size_t len) {
    size_t cap =
        keys == NULL || values == NULL || len < (size_t)(INIT_CAP * LOAD_FACTOR)
            ? INIT_CAP
            : len * GROWTH_FACTOR;
    Pair **buckets = (Pair **)calloc(cap, sizeof(Pair *));

    if (buckets == NULL) {
        fprintf(stderr,
                "\x1b[1;31merror: \x1b[0mfailed to allocate memory (exec "
                "\x1b[33minit\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    HashMap map = {.bucket = buckets, .len = 0, .cap = cap};

    if (keys == NULL || values == NULL || len == 0) {
        return map;
    }

    for (size_t i = 0; i < len; i++) {
        size_t idx = (size_t)_hash(keys[i]) % cap;

        bool has_key = false;
        if (map.bucket[idx] != NULL) {
            Pair *tmp = map.bucket[idx];
            while (tmp != NULL) {
                if (tmp->key == keys[i]) {
                    tmp->value = values[i];
                    has_key    = true;
                    break;
                }
                tmp = tmp->next;
            }
        }

        if (!has_key) {
            Pair *p = (Pair *)malloc(sizeof(Pair));
            if (p == NULL) {
                return map;
            }

            p->key          = keys[i];
            p->value        = values[i];
            p->next         = map.bucket[idx];
            map.bucket[idx] = p;
            map.len++;
        }
    }

    return map;
}

key_t *keys(HashMap *map);

value_t *values(HashMap *map);

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
        Pair *p = map->bucket[i];
        while (p != NULL) {
            Pair *tmp = p;
            p         = p->next;
            free(tmp);
        }
        map->bucket[i] = NULL;
    }
    map->len = 0;
}

bool is_empty(HashMap *map) {
    return map == NULL || map->len == 0;
}

bool get(HashMap *map, key_t key, value_t *value);

bool insert(HashMap *map, key_t key, value_t value);

bool del(HashMap *map, key_t key);

void drop(HashMap *map);

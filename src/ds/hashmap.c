#include "hashmap.h"
#include <stdlib.h>

typedef void (*PrintFunc)(FILE *stream, Pair *p);
void _print(FILE *stream, HashMap *map, PrintFunc print_func, const char *start,
            const char *end, const char *sep) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (map == NULL || map->len == 0) {
        fprintf(stream, "%s%s\n", start, end);
        return;
    }

    fprintf(stream, "%s", start);
    bool is_first = false;
    for (size_t i = 0; i < map->cap; ++i) {
        Pair *p = map->bucket[i];
        while (p != NULL) {
            if (is_first) {
                fprintf(stream, "%s", sep);
            } else {
                is_first = true;
            }

            print_func(stream, p);
            p = p->next;
        }
    }
    fprintf(stream, "%s\n", end);
}

void _print_pair(FILE *stream, Pair *p) {
    fprintf(stream, "\"%zu\": %d", p->key, p->value);
}

void _print_key(FILE *stream, Pair *p) {
    fprintf(stream, "\"%zu\"", p->key);
}

void _print_value(FILE *stream, Pair *p) {
    fprintf(stream, "%d", p->value);
}

// 32-bit multiplication
key_t _hash(key_t key) {
    return key * 0x61c88647; // Magic number
}

HashMap create(void) {
    return init(NULL, NULL, 0);
}

HashMap init(key_t *keys, value_t *values, size_t len) {
    size_t cap = keys == NULL || values == NULL || len < INIT_CAP * LOAD_FACTOR
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
        key_t slot = _hash(keys[i]) % cap;

        bool has_key = false;
        if (map.bucket[slot] != NULL) {
            Pair *tmp = map.bucket[slot];
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

            p->key           = keys[i];
            p->value         = values[i];
            p->next          = map.bucket[slot];
            map.bucket[slot] = p;
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

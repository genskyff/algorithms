#include "hashmap.h"
#include <stdlib.h>

// 32-bit multiplication
key_t _hash(key_t key) {
    return key * 0x61c88647;
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

void show(FILE *stream, HashMap *map) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (map == NULL || map->len == 0) {
        fprintf(stream, "{}\n");
        return;
    }

    fprintf(stream, "{");
    int firstItemPrinted = 0;
    for (size_t i = 0; i < map->cap; ++i) {
        Pair *p = map->bucket[i];
        if (p != NULL) {
            if (firstItemPrinted) {
                fprintf(stream, ", ");
            } else {
                firstItemPrinted = 1;
            }

            if (p->next != NULL) {
                fprintf(stream, "{");
            }

            while (p != NULL) {
                fprintf(stream, "\"%zu\": %d", p->key, p->value);
                if (p->next != NULL) {
                    fprintf(stream, ", ");
                }
                p = p->next;
            }

            if (map->bucket[i]->next != NULL) {
                fprintf(stream, "}");
            }
        }
    }
    fprintf(stream, "}\n");
}

void show_keys(FILE *stream, HashMap *map);

void show_values(FILE *stream, HashMap *map);

void clear(HashMap *map);

bool is_empty(HashMap *map);

bool get(HashMap *map, key_t key, value_t *value);

bool insert(HashMap *map, key_t key, value_t value);

bool del(HashMap *map, key_t key);

void drop(HashMap *map);

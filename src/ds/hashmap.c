#include "hashmap.h"
#include <stdlib.h>

key_t _hash(key_t key, size_t cap) {
    return key % cap;
}

HashMap create(void) {
    return init(NULL, NULL, 0);
}

HashMap init(key_t *keys, value_t *values, size_t len) {
    size_t cap  = keys == NULL || values == NULL || len < INIT_CAP * LOAD_FACTOR
                      ? INIT_CAP
                      : len * GROWTH_FACTOR;
    Pair  *data = (Pair *)malloc(cap * sizeof(Pair));

    if (data == NULL) {
        fprintf(stderr,
                "\x1b[1;31merror: \x1b[0mfailed to allocate memory (exec "
                "\x1b[33minit\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    HashMap map = {.bucket = data, .len = 0, .cap = cap};

    if (keys == NULL || values == NULL || len == 0) {
        return map;
    }

    for (size_t i = 0; i < len; i++) {
        key_t key       = _hash(keys[i], cap);
        map.bucket[key] = (Pair){keys[i], values[i]};
        map.len++;
    }

    return map;
}

void show_key_value(FILE *stream, HashMap *map) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (map == NULL || map->len == 0) {
        fprintf(stream, "{}\n");
        return;
    }

    fprintf(stream, "{");
    for (size_t i = 0; i < map->cap; i++) {
        if (map->bucket[i].key != 0) {
            fprintf(stream, "%zu\t%d\n", map->bucket[i].key,
                    map->bucket[i].value);
        }
    }
}

void show_key(FILE *stream, HashMap *map);

void show_value(FILE *stream, HashMap *map);

void clear(HashMap *map);

bool is_empty(HashMap *map);

bool get(HashMap *map, key_t key, value_t *value);

bool set(HashMap *map, key_t key, value_t value);

bool insert(HashMap *map, key_t key, value_t value);

bool del(HashMap *map, key_t key);

void drop(HashMap *map);

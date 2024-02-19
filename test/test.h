#ifndef TEST_H
#define TEST_H

#include "type.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    elem_t *unsorted;
    elem_t *sorted;
    size_t  len;
} TestSortData;

typedef bool (*TestFunc)(void);

void init_sort_data(TestSortData *data);
void run_test(TestFunc test, const char *prefix, const char *test_name);
bool assert_array_eq(elem_t *left, size_t l_len, elem_t *right, size_t r_len);

#define SORT_DATA_LEN 7

#endif

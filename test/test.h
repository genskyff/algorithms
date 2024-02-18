#ifndef TEST_H
#define TEST_H

#include "array.h"
#include <stdbool.h>

typedef struct {
    Array unsorted;
    Array sorted;
} TestData;

typedef bool (*TestFunc)(void);

void init_data(TestData *data);
void run_test(TestFunc test, char *test_name);
bool assert_array_eq(Array left, Array right);

#define DATA_LEN 7

#endif

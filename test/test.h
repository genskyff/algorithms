#ifndef TEST_H
#define TEST_H

#include "type.h"
#include <stdbool.h>

typedef struct {
    Array unsorted;
    Array sorted;
} TestData;

typedef bool (*TestFunc)(void);

void init_data(TestData *data);
void run_test(TestFunc test, const char *test_name);

#define DATA_LEN 7

#endif

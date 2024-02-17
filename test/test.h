#ifndef TEST_H
#define TEST_H

#include "type.h"
#include <stdbool.h>

typedef struct {
    const Array unsorted;
    const Array sorted;
} TestData;

typedef bool (*TestFunc)(void);

void init_data(const TestData *data);
void run_test(const TestFunc test, const char *test_name);

#define DATA_LEN 7

#endif

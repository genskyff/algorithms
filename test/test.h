#ifndef TEST_H
#define TEST_H

#include "type.h"
#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunc)(void);

typedef struct {
    const Array unsorted;
    const Array sorted;
} TestData;

const Array EMPTY          = ARRAY();
const Array ONE            = ARRAY(0);
const Array UNSORTED_2     = ARRAY(5, -2);
const Array SORTED_2       = ARRAY(-2, 5);
const Array UNSORTED_3     = ARRAY(3, -1, 0);
const Array SORTED_3       = ARRAY(-1, 0, 3);
const Array UNSORTED       = ARRAY(-3, -5, 2, 1, 4, 3, 0, 5, 1, -1, -2, -4);
const Array SORTED         = ARRAY(-5, -4, -3, -2, -1, 0, 1, 1, 2, 3, 4, 5);
const Array SORTED_REVERSE = ARRAY(5, 4, 3, 2, 1, 1, 0, -1, -2, -3, -4, -5);

const TestData DATA[] = {{EMPTY, EMPTY},          {ONE, ONE},
                         {UNSORTED_2, SORTED_2},  {UNSORTED_3, SORTED_3},
                         {UNSORTED, SORTED},      {SORTED, SORTED},
                         {SORTED_REVERSE, SORTED}};

const elem_t DATA_LEN = sizeof(DATA) / sizeof(TestData);

#define ARR_LEN           11
#define ARR_SLICE_4_7_LEN 3

const Array ARR                = ARRAY(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
const Array ARR_SLICE_4_7      = ARRAY(4, 5, 6);
const Array ARR_SWAP_0_10      = ARRAY(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0);
const Array ARR_ROTATE_LEFT_2  = ARRAY(2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 1);
const Array ARR_ROTATE_RIGHT_2 = ARRAY(9, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8);
const Array ARR_ROTATE_LEFT_SLICE_4_7_2 =
    ARRAY(0, 1, 2, 3, 6, 4, 5, 7, 8, 9, 10);
const Array ARR_ROTATE_RIGHT_SLICE_4_7_2 =
    ARRAY(0, 1, 2, 3, 5, 6, 4, 7, 8, 9, 10);

void run_test(TestFunc test, const char *test_name) {
    printf("test %s\t", test_name);

    if (test()) {
        printf("\033[1;32m...OK\033[0m\n");
    }
}

#endif

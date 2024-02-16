#ifndef DATA_H
#define DATA_H

typedef struct {
    const int *unsorted;
    const int *sorted;
    int        len;
} TestData;

const int empty[]          = {};
const int one[]            = {0};
const int unsorted_2[]     = {5, -2};
const int sorted_2[]       = {-2, 5};
const int unsorted_3[]     = {3, -1, 0};
const int sorted_3[]       = {-1, 0, 3};
const int unsorted[]       = {-3, -5, 2, 1, 4, 3, 0, 5, 1, -1, -2, -4};
const int sorted[]         = {-5, -4, -3, -2, -1, 0, 1, 1, 2, 3, 4, 5};
const int sorted_reverse[] = {5, 4, 3, 2, 1, 1, 0, -1, -2, -3, -4, -5};

const TestData DATA[] = {
    {empty, empty, sizeof(empty) / sizeof(int)},
    {one, one, sizeof(one) / sizeof(int)},
    {unsorted_2, sorted_2, sizeof(unsorted_2) / sizeof(int)},
    {unsorted_3, sorted_3, sizeof(unsorted_3) / sizeof(int)},
    {unsorted, sorted, sizeof(unsorted) / sizeof(int)},
    {sorted, sorted, sizeof(sorted) / sizeof(int)},
    {sorted_reverse, sorted, sizeof(sorted_reverse) / sizeof(int)}};

const int DATA_LEN = sizeof(DATA) / sizeof(TestData);
#endif

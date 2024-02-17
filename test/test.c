#include "test.h"
#include "utils.h"
#include <stdio.h>

void init_data(const TestData *data) {
    const Array empty          = ARRAY();
    const Array one            = ARRAY(0);
    const Array unsorted_2     = ARRAY(5, -2);
    const Array sorted_2       = ARRAY(-2, 5);
    const Array unsorted_3     = ARRAY(3, -1, 0);
    const Array sorted_3       = ARRAY(-1, 0, 3);
    const Array unsorted       = ARRAY(-3, -5, 2, 1, 4, 3, 0, 5, 1, -1, -2, -4);
    const Array sorted         = ARRAY(-5, -4, -3, -2, -1, 0, 1, 1, 2, 3, 4, 5);
    const Array sorted_reverse = ARRAY(5, 4, 3, 2, 1, 1, 0, -1, -2, -3, -4, -5);

    copy(&data[0].unsorted, &empty);
    copy(&data[0].sorted, &empty);

    copy(&data[1].unsorted, &one);
    copy(&data[1].sorted, &one);

    copy(&data[2].unsorted, &unsorted_2);
    copy(&data[2].sorted, &sorted_2);

    copy(&data[3].unsorted, &unsorted_3);
    copy(&data[3].sorted, &sorted_3);

    copy(&data[4].unsorted, &unsorted);
    copy(&data[4].sorted, &sorted);

    copy(&data[5].unsorted, &sorted);
    copy(&data[5].sorted, &sorted);

    copy(&data[6].unsorted, &sorted_reverse);
    copy(&data[6].sorted, &sorted);
}

void run_test(const TestFunc test, const char *test_name) {
    printf("test %s\t", test_name);

    if (test()) {
        printf("\033[1;32m...OK\033[0m\n");
    }
}

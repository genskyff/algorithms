#include "test.h"
#include <stdio.h>
#include <stdlib.h>

void init_data(TestData *data) {
    Array empty          = ARRAY();
    Array one            = ARRAY(0);
    Array unsorted_2     = ARRAY(5, -2);
    Array sorted_2       = ARRAY(-2, 5);
    Array unsorted_3     = ARRAY(3, -1, 0);
    Array sorted_3       = ARRAY(-1, 0, 3);
    Array unsorted       = ARRAY(-3, -5, 2, 1, 4, 3, 0, 5, 1, -1, -2, -4);
    Array sorted         = ARRAY(-5, -4, -3, -2, -1, 0, 1, 1, 2, 3, 4, 5);
    Array sorted_reverse = ARRAY(5, 4, 3, 2, 1, 1, 0, -1, -2, -3, -4, -5);

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

void run_test(TestFunc test, char *test_name) {
    printf("test %s\t", test_name);

    if (test()) {
        printf("\x1b[1;32m...OK\x1b[0m\n");
    }
}

bool assert_eq(Array left, Array right) {
    bool is_eq = true;

    if (left.len != right.len) {
        is_eq = false;
    } else {
        for (size_t i = 0; i < left.len; i++) {
            if (left.data[i] != right.data[i]) {
                is_eq = false;
                break;
            }
        }
    }

    if (!is_eq) {
        printf("\x1b[1;31m...FAILED\x1b[0m\n");
        printf("  |-- left\t");
        show(left);
        printf("  |-- right\t");
        show(right);
        printf("\n");
        exit(1);
    }

    return is_eq;
}

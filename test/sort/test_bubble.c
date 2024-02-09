#include "bubble.h"
#include "data.h"
#include "utils.h"
#include <stdio.h>

int main(void) {
    printf("\n---- test_bubble ----\n");
    bubble_sort(UNSTORED, LEN);
    assert_eq(UNSTORED, STORED, LEN);

    return 0;
}

#include "bubble.h"
#include "data.h"
#include "utils.h"
#include <stdio.h>

int main(void) {
    printf("\n---- test_bubble ----\n");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    bubble_sort(arr, LEN);
    assert_eq(arr, STORED, LEN);

    return 0;
}

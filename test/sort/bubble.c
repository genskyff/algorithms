#include "bubble.h"
#include "utils.h"
#include <stdio.h>

int main(void) {
    int a[] = {6, 5, 3, 1, 8, 7, 2, 4};
    int len = sizeof(a) / sizeof(int);

    printf("排序前:\n");
    show(a, len);

    bubble_sort(a, len);

    printf("排序后:\n");
    show(a, len);

    return 0;
}

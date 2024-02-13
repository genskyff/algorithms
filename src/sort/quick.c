#include "quick.h"

#ifdef DEBUG_PRINT
#include "utils.h"
#include <stdio.h>
#endif

void qsort(int *arr, int left, int right);
int  partition(int *arr, int left, int right);
void move_pivot_to_right(int *arr, int left, int right);

void quick_sort(int *arr, int len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len < 2) {
        return;
    }

    qsort(arr, 0, len - 1);
}

void qsort(int *arr, int left, int right) {
    // todo
}

int partition(int *arr, int left, int right) {
    // todo
    return 0;
}

void move_pivot_to_right(int *arr, int left, int right) {
    // todo
}

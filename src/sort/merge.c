#include "merge.h"
#include <stdlib.h>

#ifdef DEBUG_PRINT
#include "utils.h"
#include <stdio.h>
#endif

void entry_recu(int *arr, int len);
void entry_iter(int *arr, int len);
void divide_recu(int *arr, int *tmp, int left, int right);
void divide_iter(int *arr, int *tmp, int len);
void conquer(int *arr, int *tmp, int left, int mid, int right);

void merge_sort_recu(int *arr, int len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len < 2) {
        return;
    }

    entry_recu(arr, len);
}

void merge_sort_iter(int *arr, int len) {
#ifdef DEBUG_PRINT
    printf("\nbegin:\t");
    show(arr, len);
#endif

    if (len < 2) {
        return;
    }

    entry_iter(arr, len);
}

void entry_recu(int *arr, int len) {
    int *tmp = (int *)malloc(len * sizeof(int));
    divide_recu(arr, tmp, 0, len - 1);
}

void entry_iter(int *arr, int len) {
    int *tmp = (int *)malloc(len * sizeof(int));
    divide_iter(arr, tmp, len);
}

void divide_recu(int *arr, int *tmp, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        divide_recu(arr, tmp, left, mid);
        divide_recu(arr, tmp, mid + 1, right);
        conquer(arr, tmp, left, mid, right);
    }
}

void divide_iter(int *arr, int *tmp, int len) {
    int left, mid, right;

    for (int i = 1; i < len; i *= 2) {
        left = 0;
        while (left + i < len) {
            mid   = left + i - 1;
            right = mid + i < len ? mid + i : len - 1;
            conquer(arr, tmp, left, mid, right);
            left = right + 1;

#ifdef DEBUG_PRINT
            printf("next:\t");
            show(arr, len);
#endif
        }
    }
}

void conquer(int *arr, int *tmp, int left, int mid, int right) {
    int l_pos = left, r_pos = mid + 1, t_pos = left;

    while (l_pos <= mid && r_pos <= right) {
        if (arr[l_pos] < arr[r_pos]) {
            tmp[t_pos++] = arr[l_pos++];
        } else {
            tmp[t_pos++] = arr[r_pos++];
        }
    }

    while (l_pos <= mid) {
        tmp[t_pos++] = arr[l_pos++];
    }

    while (r_pos <= right) {
        tmp[t_pos++] = arr[r_pos++];
    }

    for (int i = left; i < t_pos; i++) {
        arr[i] = tmp[i];
    }
}

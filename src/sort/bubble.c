#include "bubble.h"
#include "utils.h"
#include <stdbool.h>

void bubble_sort(int *arr, int len) {
    if (len < 2) {
        return;
    }

    bool flag;
    for (int i = 0; i < len; i++) {
        flag = false;

        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
                flag = true;
            }
        }

        if (!flag) {
            break;
        }
    }
}

void cocktail_sort(int *arr, int len) {
    if (len < 2) {
        return;
    }

    int start = 0;
    int end   = len - 1;

    while (start < end) {
        bool flag = false;

        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr, i, i + 1);
                flag = true;
            }
        }

        if (!flag) {
            break;
        }

        end--;
        flag = false;
        
        for (int i = end; i > start; i--) {
            if (arr[i] < arr[i - 1]) {
                swap(arr, i, i - 1);
                flag = true;
            }
        }

        if (!flag) {
            break;
        }

        start++;
    }
}

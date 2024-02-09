#include "bubble.h"
#include "utils.h"
#include <stdbool.h>

void bubble_sort(int a[], int len) {
    if (len < 2) {
        return;
    }

    bool flag;
    for (int i = 0; i < len; i++) {
        flag = false;

        for (int j = 0; j < len - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a, j, j + 1);
                flag = true;
            }
        }

        if (!flag) {
            break;
        }
    }
}

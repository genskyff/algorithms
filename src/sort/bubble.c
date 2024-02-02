#include "../../include/sort/bubble_sort.h"
#include <stdio.h>

// 交换数组 a 中索引为 i、j 的元素值
void swap(int a[], int i, int j) {
  int t = a[i];
  a[i] = a[j];
  a[j] = t;
}

// 列出数组 a 的所有元素
void display(int a[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

// 冒泡排序
void bubble_sort(int a[], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (a[j] > a[j + 1]) {
        swap(a, j, j + 1);
      }
    }
  }
}

int main(void) {
  int a[] = {6, 5, 3, 1, 8, 7, 2, 4};
  int n = sizeof(a) / sizeof(int);

  printf("排序前:\n");
  display(a, n);

  bubble_sort(a, n);

  printf("排序后:\n");
  display(a, n);

  return 0;
}

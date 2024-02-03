#include "utils.h"
#include <stdio.h>

// 交换数组 a 中索引为 i、j 的元素值
void swap(int a[], int i, int j) {
  int t = a[i];
  a[i] = a[j];
  a[j] = t;
}

// 列出数组 a 的所有元素
void show(int a[], int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

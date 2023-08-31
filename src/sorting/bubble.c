#include <stdio.h>
#include "bubble.h"

// 交换数组 a 中索引为 i、j 的元素值
void swap(int a[], int i, int j)
{
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

// 列出数组 a 的所有元素
void display(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// 冒泡排序
void bubble_sort(int a[], int n)
{
    for (int j = 0; j < n - 1; j++)         // 每次最大元素像气泡一样"浮"到数组最后
        for (int i = 0; i < n - 1 - j; i++) // 依次比较相邻的两个元素, 使较大的向后移
            if (a[i] > a[i + 1])
                swap(a, i, i + 1);
}

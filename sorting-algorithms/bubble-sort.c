#include <stdio.h>

// 交换数组a中下标为i, j两个位置的元素值
void swap(int a[], int i, int j)
{
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}

// 列出数组a的所有元素
void display(int a[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

// 冒泡排序
void bubble_sort(int a[], int n)
{
	for (int j = 0; j < n - 1; j++)			// 每次最大元素像气泡一样"浮"到数组最后
		for (int i = 0; i < n - 1 - j; i++) // 依次比较相邻的两个元素, 使较大的向后移
			if (a[i] > a[i + 1])
				swap(a, i, i + 1);
}

int main(void)
{
	int a[] = {6, 5, 3, 1, 8, 7, 2, 4};
	int n = sizeof(a) / sizeof(int);

	printf("排序前:\n");
	display(a, n);

	bubble_sort(a, n);

	printf("排序后:\n");
	display(a, n);

	return 0;
}

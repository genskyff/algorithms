#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
void swap(int *arr, int i, int j);
void copy(int *src, int *dest, int len);
void show(int *arr, int len);
void assert_eq(int *left, int *right, int len);
#endif

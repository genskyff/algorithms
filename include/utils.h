#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
#include <stddef.h>
void swap(int *arr, const size_t i, const size_t j);
void copy(const int *src, int *dest, const size_t len);
void rotate_left(int *arr, const size_t begin, const size_t end,
                 const size_t k);
void rotate_right(int *arr, const size_t begin, const size_t end,
                  const size_t k);
void show(const int *arr, const size_t len);
void assert_eq(const int *left, const int *right, const size_t len);
#endif

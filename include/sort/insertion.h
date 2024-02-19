#ifndef INSERTION_H
#define INSERTION_H

#include "type.h"
#include <stddef.h>

void insertion_sort(elem_t *arr, size_t len);
void binary_insertion_sort(elem_t *arr, size_t len);
void shell_sort(elem_t *arr, size_t len);

#endif

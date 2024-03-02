#ifndef HELPER_H
#define HELPER_H

#include "type.h"
#include <stdbool.h>

typedef void (*TestFunc)(void);
void run_test(TestFunc test, char *prefix, char *test_name);

void assert(bool cond, char *msg);
void assert_not(bool cond, char *msg);

void assert_eq(elem_t left, elem_t right, char *msg);
void assert_ne(elem_t left, elem_t right, char *msg);

void assert_arr_eq(elem_t *left, size_t l_len, elem_t *right, size_t r_len,
                   char *msg);
void assert_arr_ne(elem_t *left, size_t l_len, elem_t *right, size_t r_len,
                   char *msg);

void assert_list_eq(Node *left, Node *right, Direction dir, char *msg);
void assert_list_ne(Node *left, Node *right, Direction dir, char *msg);

void assert_list_arr_eq(Node *node, Direction dir, elem_t *arr, size_t len,
                        char *msg);
void assert_list_arr_ne(Node *node, Direction dir, elem_t *arr, size_t len,
                        char *msg);

#define SORT_DATA_LEN 7

typedef struct {
    elem_t *unsorted;
    elem_t *sorted;
    size_t  len;
} TestSortData;

void init_sort_data(TestSortData *data);

#endif

#ifndef ALG_HELPER_H
#define ALG_HELPER_H

#include "alg/type.h"
#include <stdbool.h>

typedef void (*TestFunc)(void);
void run_test(TestFunc test, const char *mod, const char *target,
              const char *test_name);

void assert(bool cond, const char *msg);
void assert_not(bool cond, const char *msg);

void assert_null(void *ptr, const char *msg);
void assert_not_null(void *ptr, const char *msg);

void assert_eq(elem_t left, elem_t right, const char *msg);
void assert_ne(elem_t left, elem_t right, const char *msg);

void assert_str_eq(const char *left, const char *right, const char *msg);
void assert_str_ne(const char *left, const char *right, const char *msg);

void assert_arr_eq(elem_t *left, size_t l_len, elem_t *right, size_t r_len,
                   const char *msg);
void assert_arr_ne(elem_t *left, size_t l_len, elem_t *right, size_t r_len,
                   const char *msg);

void assert_list_eq(Node *left, Node *right, Direction dir, const char *msg);
void assert_list_ne(Node *left, Node *right, Direction dir, const char *msg);

void assert_list_arr_eq(Node *node, Direction dir, elem_t *arr, size_t len,
                        const char *msg);
void assert_list_arr_ne(Node *node, Direction dir, elem_t *arr, size_t len,
                        const char *msg);

#define SORT_DATA_LEN 7

typedef struct {
    elem_t *unsorted;
    elem_t *sorted;
    size_t  len;
} TestSortData;

void init_sort_data(TestSortData *data);

#endif

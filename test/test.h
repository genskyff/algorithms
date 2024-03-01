#ifndef TEST_H
#define TEST_H

#include "type.h"
#include <stdbool.h>

typedef bool (*TestFunc)(void);
void run_test(TestFunc test, char *prefix, char *test_name);

bool assert(bool cond, char *msg);
bool assert_not(bool cond, char *msg);

bool is_eq(elem_t left, elem_t right);
void err_msg(elem_t left, elem_t right, char *msg);
bool assert_eq(elem_t left, elem_t right, char *msg);
bool assert_ne(elem_t left, elem_t right, char *msg);

bool is_arr_eq(elem_t *left, size_t l_len, elem_t *right, size_t r_len);
void arr_err_msg(elem_t *left, size_t l_len, elem_t *right,
                 size_t r_len, char *msg);
bool assert_arr_eq(elem_t *left, size_t l_len, elem_t *right, size_t r_len,
                   char *msg);
bool assert_arr_ne(elem_t *left, size_t l_len, elem_t *right, size_t r_len,
                   char *msg);

bool is_list_eq(Node *left, Node *right);
void list_err_msg(Node *left, Node *right, char *msg);
bool assert_list_eq(Node *left, Node *right, char *msg);
bool assert_list_ne(Node *left, Node *right, char *msg);

#define SORT_DATA_LEN 7

typedef struct {
    elem_t *unsorted;
    elem_t *sorted;
    size_t  len;
} TestSortData;

void init_sort_data(TestSortData *data);

#endif

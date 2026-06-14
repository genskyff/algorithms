#ifndef ALG_TEST_SUPPORT_HELPER_H
#define ALG_TEST_SUPPORT_HELPER_H

#include "alg/ds/node.h"
#include <stdbool.h>
#include <stddef.h>

typedef void (*TestFunc)(void);
void run_test(TestFunc test, const char *mod, const char *target,
              const char *test_name);

void assert_at(bool cond, const char *msg, const char *file, size_t line);
void assert_not_at(bool cond, const char *msg, const char *file, size_t line);

void assert_null_at(const void *ptr, const char *msg, const char *file,
                    size_t line);
void assert_not_null_at(const void *ptr, const char *msg, const char *file,
                        size_t line);

void assert_eq_at(alg_elem_t left, alg_elem_t right, const char *msg,
                  const char *file, size_t line);
void assert_ne_at(alg_elem_t left, alg_elem_t right, const char *msg,
                  const char *file, size_t line);

void assert_str_eq_at(const char *left, const char *right, const char *msg,
                      const char *file, size_t line);
void assert_str_ne_at(const char *left, const char *right, const char *msg,
                      const char *file, size_t line);

void assert_arr_eq_at(alg_elem_t *left, size_t l_len, alg_elem_t *right,
                      size_t r_len, const char *msg, const char *file,
                      size_t line);
void assert_arr_ne_at(alg_elem_t *left, size_t l_len, alg_elem_t *right,
                      size_t r_len, const char *msg, const char *file,
                      size_t line);

void assert_list_eq_at(AlgNode *left, AlgNode *right, AlgDirection dir,
                       const char *msg, const char *file, size_t line);
void assert_list_ne_at(AlgNode *left, AlgNode *right, AlgDirection dir,
                       const char *msg, const char *file, size_t line);

void assert_list_arr_eq_at(AlgNode *node, AlgDirection dir, alg_elem_t *arr,
                           size_t len, const char *msg, const char *file,
                           size_t line);
void assert_list_arr_ne_at(AlgNode *node, AlgDirection dir, alg_elem_t *arr,
                           size_t len, const char *msg, const char *file,
                           size_t line);

#define assert(cond, msg)     assert_at((cond), (msg), __FILE__, __LINE__)
#define assert_not(cond, msg) assert_not_at((cond), (msg), __FILE__, __LINE__)
#define assert_null(ptr, msg) assert_null_at((ptr), (msg), __FILE__, __LINE__)
#define assert_not_null(ptr, msg)                                              \
    assert_not_null_at((ptr), (msg), __FILE__, __LINE__)
#define assert_eq(left, right, msg)                                            \
    assert_eq_at((left), (right), (msg), __FILE__, __LINE__)
#define assert_ne(left, right, msg)                                            \
    assert_ne_at((left), (right), (msg), __FILE__, __LINE__)
#define assert_str_eq(left, right, msg)                                        \
    assert_str_eq_at((left), (right), (msg), __FILE__, __LINE__)
#define assert_str_ne(left, right, msg)                                        \
    assert_str_ne_at((left), (right), (msg), __FILE__, __LINE__)
#define assert_arr_eq(left, l_len, right, r_len, msg)                          \
    assert_arr_eq_at((left), (l_len), (right), (r_len), (msg), __FILE__,       \
                     __LINE__)
#define assert_arr_ne(left, l_len, right, r_len, msg)                          \
    assert_arr_ne_at((left), (l_len), (right), (r_len), (msg), __FILE__,       \
                     __LINE__)
#define assert_list_eq(left, right, dir, msg)                                  \
    assert_list_eq_at((left), (right), (dir), (msg), __FILE__, __LINE__)
#define assert_list_ne(left, right, dir, msg)                                  \
    assert_list_ne_at((left), (right), (dir), (msg), __FILE__, __LINE__)
#define assert_list_arr_eq(node, dir, arr, len, msg)                           \
    assert_list_arr_eq_at((node), (dir), (arr), (len), (msg), __FILE__,        \
                          __LINE__)
#define assert_list_arr_ne(node, dir, arr, len, msg)                           \
    assert_list_arr_ne_at((node), (dir), (arr), (len), (msg), __FILE__,        \
                          __LINE__)

#define SORT_DATA_LEN 7

typedef struct {
    alg_elem_t *unsorted;
    alg_elem_t *sorted;
    size_t      len;
} TestSortData;

void init_sort_data(TestSortData *data);

#endif

#include "support/helper.h"
#include "internal/utils.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *mod;
    const char *target;
    const char *name;
} FailedTest;

static jmp_buf     helper_test_env;
static bool        helper_test_running;
static size_t      helper_passed_count;
static size_t      helper_failed_count;
static FailedTest *helper_failed_tests;

static bool helper_is_eq(alg_elem_t left, alg_elem_t right);
static void helper_abort_test(void);
static void helper_record_failure(const char *mod, const char *target,
                                  const char *test_name);
static void helper_report_results(void);
static void helper_failure_header(const char *msg, const char *file,
                                  size_t line);
static void helper_err_msg(alg_elem_t left, alg_elem_t right, const char *msg,
                           const char *file, size_t line);
static bool helper_is_str_eq(const char *left, const char *right);
static void helper_str_err_msg(const char *left, const char *right,
                               const char *msg, const char *file, size_t line);
static bool helper_is_arr_eq(alg_elem_t *left, size_t l_len, alg_elem_t *right,
                             size_t r_len);
static void helper_arr_err_msg(alg_elem_t *left, size_t l_len,
                               alg_elem_t *right, size_t r_len, const char *msg,
                               const char *file, size_t line);
static bool helper_is_list_eq(AlgNode *left, AlgNode *right, AlgDirection dir);
static void helper_list_err_msg(AlgNode *left, AlgNode *right, AlgDirection dir,
                                const char *msg, const char *file, size_t line);
static bool helper_is_list_arr_eq(AlgNode *node, AlgDirection dir,
                                  alg_elem_t *arr, size_t len);
static void helper_list_arr_err_msg(AlgNode *node, AlgDirection dir,
                                    alg_elem_t *arr, size_t len,
                                    const char *msg, const char *file,
                                    size_t line);

static bool helper_is_eq(alg_elem_t left, alg_elem_t right) {
    return left == right;
}

static void helper_abort_test(void) {
    if (helper_test_running) {
        longjmp(helper_test_env, 1);
    }

    exit(EXIT_FAILURE);
}

static void helper_record_failure(const char *mod, const char *target,
                                  const char *test_name) {
    helper_failed_count++;
    helper_failed_tests =
        realloc(helper_failed_tests, helper_failed_count * sizeof(FailedTest));
    helper_failed_tests[helper_failed_count - 1] =
        (FailedTest){.mod = mod, .target = target, .name = test_name};
}

static void helper_report_results(void) {
    if (helper_failed_count == 0) {
        return;
    }

    fprintf(stderr, "\nfailures:\n");
    for (size_t i = 0; i < helper_failed_count; i++) {
        FailedTest failed     = helper_failed_tests[i];
        bool       has_mod    = failed.mod != NULL && *failed.mod != '\0';
        bool       has_target = failed.target != NULL && *failed.target != '\0';

        fprintf(stderr, "    %s%s%s%s%s\n", has_mod ? failed.mod : "",
                has_mod ? " " : "", has_target ? failed.target : "",
                has_target ? " " : "", failed.name != NULL ? failed.name : "");
    }

    fprintf(stderr,
            "\ntest result: \x1b[1;31mFAILED\x1b[0m. %zu passed; %zu "
            "failed\n",
            helper_passed_count, helper_failed_count);
    free(helper_failed_tests);
    fflush(stdout);
    fflush(stderr);
    _Exit(EXIT_FAILURE);
}

static void helper_failure_header(const char *msg, const char *file,
                                  size_t line) {
    const char *message_text = (msg == NULL || *msg == '\0') ? "\"\"" : msg;
    printf("\x1b[1;31m ... FAILED\x1b[0m\n");
    fflush(stdout);
    fprintf(stderr, "\x1b[33m|-- location: \x1b[0m%s:%zu\n", file, line);
    fprintf(stderr, "\x1b[33m|-- message:  \x1b[0m%s\n", message_text);
}

static void helper_err_msg(alg_elem_t left, alg_elem_t right, const char *msg,
                           const char *file, size_t line) {
    helper_failure_header(msg, file, line);
    fprintf(stderr, "\x1b[33m|-- left:    \x1b[0m");
    fprintf(stderr, "%d\n", left);
    fprintf(stderr, "\x1b[33m|-- right:   \x1b[0m");
    fprintf(stderr, "%d\n\n", right);
    helper_abort_test();
}

static bool helper_is_str_eq(const char *left, const char *right) {
    return alg_internal_cmp_str(left, right) == 0;
}

static void helper_str_err_msg(const char *left, const char *right,
                               const char *msg, const char *file, size_t line) {
    helper_failure_header(msg, file, line);
    fprintf(stderr, "\x1b[33m|-- left:    \x1b[0m");
    fprintf(stderr, "\"%s\"\n", left);
    fprintf(stderr, "\x1b[33m|-- right:   \x1b[0m");
    fprintf(stderr, "\"%s\"\n\n", right);
    helper_abort_test();
}

static bool helper_is_arr_eq(alg_elem_t *left, size_t l_len, alg_elem_t *right,
                             size_t r_len) {
    if (left == NULL && right == NULL) {
        return true;
    }

    if (left == NULL || right == NULL || l_len != r_len) {
        return false;
    }

    for (size_t i = 0; i < l_len; i++) {
        if (left[i] != right[i]) {
            return false;
        }
    }

    return true;
}

static void helper_arr_err_msg(alg_elem_t *left, size_t l_len,
                               alg_elem_t *right, size_t r_len, const char *msg,
                               const char *file, size_t line) {
    helper_failure_header(msg, file, line);
    fprintf(stderr, "\x1b[33m|-- left:    \x1b[0m");
    alg_internal_show(stderr, left, l_len, NULL);
    fprintf(stderr, "\x1b[33m|-- right:   \x1b[0m");
    alg_internal_show(stderr, right, r_len, NULL);
    fprintf(stderr, "\n");
    helper_abort_test();
}

static bool helper_is_list_eq(AlgNode *left, AlgNode *right, AlgDirection dir) {
    while (left != NULL && right != NULL) {
        if (left->data != right->data) {
            return false;
        }
        left  = dir == ALG_FORWARD ? left->next : left->prev;
        right = dir == ALG_FORWARD ? right->next : right->prev;
    }

    return left == NULL && right == NULL;
}

static void helper_list_err_msg(AlgNode *left, AlgNode *right, AlgDirection dir,
                                const char *msg, const char *file,
                                size_t line) {
    helper_failure_header(msg, file, line);
    fprintf(stderr, "\x1b[33m|-- left:    \x1b[0m");
    alg_internal_show_list(stderr, left, dir, NULL);
    fprintf(stderr, "\x1b[33m|-- right:   \x1b[0m");
    alg_internal_show_list(stderr, right, dir, NULL);
    fprintf(stderr, "\n");
    helper_abort_test();
}

static bool helper_is_list_arr_eq(AlgNode *node, AlgDirection dir,
                                  alg_elem_t *arr, size_t len) {
    if (node == NULL && arr == NULL) {
        return true;
    }

    if (node == NULL || arr == NULL) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        size_t idx = dir == ALG_FORWARD ? i : len - i - 1;
        if (node == NULL || node->data != arr[idx]) {
            return false;
        }
        node = dir == ALG_FORWARD ? node->next : node->prev;
    }

    return node == NULL;
}

static void helper_list_arr_err_msg(AlgNode *node, AlgDirection dir,
                                    alg_elem_t *arr, size_t len,
                                    const char *msg, const char *file,
                                    size_t line) {
    helper_failure_header(msg, file, line);
    fprintf(stderr, "\x1b[33m|-- list:    \x1b[0m");
    alg_internal_show_list(stderr, node, dir, ", ");
    fprintf(stderr, "\x1b[33m|-- arr:     \x1b[0m");
    alg_internal_show(stderr, arr, len, NULL);
    fprintf(stderr, "\n");
    helper_abort_test();
}

void run_test(TestFunc test, const char *mod, const char *target,
              const char *test_name) {
    static bool report_registered;

    bool has_mod       = mod != NULL && *mod != '\0';
    bool has_target    = target != NULL && *target != '\0';
    bool has_test_name = test_name != NULL && *test_name != '\0';

    if (!report_registered) {
        atexit(helper_report_results);
        report_registered = true;
    }

    printf("test %s%s%s%s%s%s", has_mod ? mod : "", has_mod ? " " : "",
           has_target ? target : "", has_target ? " " : "",
           has_test_name ? test_name : "", has_test_name ? " " : "");
    fflush(stdout);

    helper_test_running = true;
    if (setjmp(helper_test_env) == 0) {
        test();
        helper_test_running = false;
        helper_passed_count++;
        printf("\x1b[1;32m ... OK\x1b[0m\n");
    } else {
        helper_test_running = false;
        helper_record_failure(mod, target, test_name);
    }
}

void assert_at(bool cond, const char *msg, const char *file, size_t line) {
    if (!cond) {
        helper_failure_header(msg, file, line);
        fprintf(stderr, "\x1b[33m|-- expect:  \x1b[0mtrue\n");
        fprintf(stderr, "\x1b[33m|-- actual:  \x1b[0mfalse\n\n");
        helper_abort_test();
    }
}

void assert_not_at(bool cond, const char *msg, const char *file, size_t line) {
    if (cond) {
        helper_failure_header(msg, file, line);
        fprintf(stderr, "\x1b[33m|-- expect:  \x1b[0mfalse\n");
        fprintf(stderr, "\x1b[33m|-- actual:  \x1b[0mtrue\n\n");
        helper_abort_test();
    }
}

void assert_null_at(const void *ptr, const char *msg, const char *file,
                    size_t line) {
    if (ptr != NULL) {
        helper_failure_header(msg, file, line);
        fprintf(stderr, "\x1b[33m|-- expect:  \x1b[0mNULL\n");
        fprintf(stderr, "\x1b[33m|-- actual:  \x1b[0mNot NULL\n\n");
        helper_abort_test();
    }
}

void assert_not_null_at(const void *ptr, const char *msg, const char *file,
                        size_t line) {
    if (ptr == NULL) {
        helper_failure_header(msg, file, line);
        fprintf(stderr, "\x1b[33m|-- expect:  \x1b[0mNot NULL\n");
        fprintf(stderr, "\x1b[33m|-- actual:  \x1b[0mNULL\n\n");
        helper_abort_test();
    }
}

void assert_eq_at(alg_elem_t left, alg_elem_t right, const char *msg,
                  const char *file, size_t line) {
    if (!helper_is_eq(left, right)) {
        helper_err_msg(left, right, msg, file, line);
    }
}

void assert_ne_at(alg_elem_t left, alg_elem_t right, const char *msg,
                  const char *file, size_t line) {
    if (helper_is_eq(left, right)) {
        helper_err_msg(left, right, msg, file, line);
    }
}

void assert_str_eq_at(const char *left, const char *right, const char *msg,
                      const char *file, size_t line) {
    if (!helper_is_str_eq(left, right)) {
        helper_str_err_msg(left, right, msg, file, line);
    }
}

void assert_str_ne_at(const char *left, const char *right, const char *msg,
                      const char *file, size_t line) {
    if (helper_is_str_eq(left, right)) {
        helper_str_err_msg(left, right, msg, file, line);
    }
}

void assert_arr_eq_at(alg_elem_t *left, size_t l_len, alg_elem_t *right,
                      size_t r_len, const char *msg, const char *file,
                      size_t line) {
    if (!helper_is_arr_eq(left, l_len, right, r_len)) {
        helper_arr_err_msg(left, l_len, right, r_len, msg, file, line);
    }
}

void assert_arr_ne_at(alg_elem_t *left, size_t l_len, alg_elem_t *right,
                      size_t r_len, const char *msg, const char *file,
                      size_t line) {
    if (helper_is_arr_eq(left, l_len, right, r_len)) {
        helper_arr_err_msg(left, l_len, right, r_len, msg, file, line);
    }
}

void assert_list_eq_at(AlgNode *left, AlgNode *right, AlgDirection dir,
                       const char *msg, const char *file, size_t line) {
    if (!helper_is_list_eq(left, right, dir)) {
        helper_list_err_msg(left, right, dir, msg, file, line);
    }
}

void assert_list_ne_at(AlgNode *left, AlgNode *right, AlgDirection dir,
                       const char *msg, const char *file, size_t line) {
    if (helper_is_list_eq(left, right, dir)) {
        helper_list_err_msg(left, right, dir, msg, file, line);
    }
}

void assert_list_arr_eq_at(AlgNode *node, AlgDirection dir, alg_elem_t *arr,
                           size_t len, const char *msg, const char *file,
                           size_t line) {
    if (!helper_is_list_arr_eq(node, dir, arr, len)) {
        helper_list_arr_err_msg(node, dir, arr, len, msg, file, line);
    }
}

void assert_list_arr_ne_at(AlgNode *node, AlgDirection dir, alg_elem_t *arr,
                           size_t len, const char *msg, const char *file,
                           size_t line) {
    if (helper_is_list_arr_eq(node, dir, arr, len)) {
        helper_list_arr_err_msg(node, dir, arr, len, msg, file, line);
    }
}

void init_sort_data(TestSortData *data) {
    if (data == NULL) {
        fprintf(stderr, "\x1b[1;31merror: \x1b[0mdata is NULL (exec "
                        "\x1b[33minit_sort_data\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    alg_elem_t *none             = NULL;
    alg_elem_t  one[1]           = {0};
    alg_elem_t  unsorted_2[2]    = {5, -2};
    alg_elem_t  sorted_2[2]      = {-2, 5};
    alg_elem_t  unsorted_3[3]    = {3, -1, 0};
    alg_elem_t  sorted_3[3]      = {-1, 0, 3};
    alg_elem_t  unsorted[]       = {-3, -5, 2, 1, 4, 3, 0, 5, 1, -1, -2, -4};
    alg_elem_t  sorted[]         = {-5, -4, -3, -2, -1, 0, 1, 1, 2, 3, 4, 5};
    alg_elem_t  sorted_reverse[] = {5, 4, 3, 2, 1, 1, 0, -1, -2, -3, -4, -5};

    // none element
    data[0].unsorted = none;
    data[0].sorted   = none;
    data[0].len      = 0;

    // one element
    alg_elem_t *tmp = (alg_elem_t *)malloc(2 * sizeof(one));
    size_t      len = sizeof(one) / sizeof(alg_elem_t);
    alg_internal_copy(tmp, len, one, len);
    data[1].unsorted = tmp;
    alg_internal_copy(tmp + len, len, one, len);
    data[1].sorted = tmp + len;
    data[1].len    = len;

    // two unsorted elements
    tmp = (alg_elem_t *)malloc(2 * sizeof(unsorted_2));
    len = sizeof(unsorted_2) / sizeof(alg_elem_t);
    alg_internal_copy(tmp, len, unsorted_2, len);
    data[2].unsorted = tmp;
    alg_internal_copy(tmp + len, len, sorted_2, len);
    data[2].sorted = tmp + len;
    data[2].len    = len;

    // three  unsorted elements
    tmp = (alg_elem_t *)malloc(2 * sizeof(unsorted_3));
    len = sizeof(unsorted_3) / sizeof(alg_elem_t);
    alg_internal_copy(tmp, len, unsorted_3, len);
    data[3].unsorted = tmp;
    alg_internal_copy(tmp + len, len, sorted_3, len);
    data[3].sorted = tmp + len;
    data[3].len    = len;

    // more than three unsorted elements
    tmp = (alg_elem_t *)malloc(2 * sizeof(unsorted));
    len = sizeof(unsorted) / sizeof(alg_elem_t);
    alg_internal_copy(tmp, len, unsorted, len);
    data[4].unsorted = tmp;
    alg_internal_copy(tmp + len, len, sorted, len);
    data[4].sorted = tmp + len;
    data[4].len    = len;

    // sorted reverse elements
    tmp = (alg_elem_t *)malloc(2 * sizeof(sorted_reverse));
    len = sizeof(sorted_reverse) / sizeof(alg_elem_t);
    alg_internal_copy(tmp, len, sorted_reverse, len);
    data[5].unsorted = tmp;
    alg_internal_copy(tmp + len, len, sorted, len);
    data[5].sorted = tmp + len;
    data[5].len    = len;

    // sorted elements
    tmp = (alg_elem_t *)malloc(2 * sizeof(sorted));
    len = sizeof(sorted) / sizeof(alg_elem_t);
    alg_internal_copy(tmp, len, sorted, len);
    data[6].unsorted = tmp;
    alg_internal_copy(tmp + len, len, sorted, len);
    data[6].sorted = tmp + len;
    data[6].len    = len;
}

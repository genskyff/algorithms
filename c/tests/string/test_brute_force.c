#include "alg/string/brute_force.h"
#include "support/helper.h"
#include <string.h>

#define LEN 5

void test_brute_force(void) {
    const char *s   = "AABAACAADAABAABA";
    const char *pat = "AABA";
    size_t      indices[LEN];
    size_t      count;
    char       *msg;

    msg   = "should return 0 when s is NULL";
    count = alg_brute_force(NULL, pat, indices, LEN);
    assert_eq(count, 0, msg);

    msg   = "should return 0 when pat is NULL";
    count = alg_brute_force(s, NULL, indices, LEN);
    assert_eq(count, 0, msg);

    msg   = "should return 0 when m is 0";
    count = alg_brute_force(s, "", indices, LEN);
    assert_eq(count, 0, msg);

    msg   = "should return 0 when n < m";
    count = alg_brute_force("AA", pat, indices, LEN);
    assert_eq(count, 0, msg);

    msg               = "should match 3 times";
    count             = alg_brute_force(s, pat, indices, LEN);
    size_t expected[] = {0, 9, 12};
    assert_eq(count, 3, msg);
    assert_arr_eq((alg_elem_t *)indices, 3, (alg_elem_t *)expected, 3, msg);

    msg                = "should match over 5 times, but only return 5 indices";
    count              = alg_brute_force(s, "A", indices, LEN);
    size_t expected2[] = {0, 1, 3, 6, 8};
    assert_eq(count, 11, msg);
    assert_arr_eq((alg_elem_t *)indices, 5, (alg_elem_t *)expected2, 5, msg);

    msg                = "should return 1 when s == pat";
    count              = alg_brute_force("AABA", pat, indices, LEN);
    size_t expected3[] = {0};
    assert_eq(count, 1, msg);
    assert_arr_eq((alg_elem_t *)indices, 1, (alg_elem_t *)expected3, 1, msg);
}

int main(void) {
    char *mod    = "string";
    char *target = NULL;

    run_test(test_brute_force, mod, target, "brute_force");

    return 0;
}

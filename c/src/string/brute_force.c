#include "alg/string/brute_force.h"
#include <string.h>

size_t brute_force(char *s, char *pat, size_t *indices, size_t len) {
    if (s == NULL || pat == NULL) {
        return 0;
    }

    size_t n = strlen(s);
    size_t m = strlen(pat);
    if (m == 0 || n < m) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < n - m + 1; i++) {
        size_t j;
        for (j = 0; j < m; j++) {
            if (s[i + j] != pat[j]) {
                break;
            }
        }

        if (j == m) {
            if (indices != NULL && count < len) {
                indices[count] = i;
            }
            count++;
        }
    }

    return count;
}

#ifndef ALG_BRUTE_FORCE_H
#define ALG_BRUTE_FORCE_H

#include "alg/core.h"
#include <stddef.h>

size_t alg_brute_force(const char *s, const char *pat, size_t *indices,
                       size_t len);

#endif

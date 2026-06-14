#include "alg/alg.h"
#include "support/helper.h"

void test_public_api(void) {
    alg_elem_t data[] = {3, 1, 2};
    AlgVec     v      = alg_vec_from_array(data, 3);
    AlgHashMap map    = alg_hashmap_create();
    size_t     indices[1];
    char      *msg = "should use public APIs from the alg library";

    alg_quick_sort(v.data, v.len);
    alg_elem_t sorted[] = {1, 2, 3};
    assert_arr_eq(v.data, v.len, sorted, 3, msg);

    assert(alg_hashmap_insert(&map, "last", v.data[2]), msg);
    alg_hashmap_value_t value;
    assert(alg_hashmap_get(&map, "last", &value), msg);
    assert_eq(value, 3, msg);

    assert_eq(alg_brute_force("algorithm", "i", indices, 1), 1, msg);
    assert_eq(indices[0], 5, msg);

    alg_hashmap_drop(&map);
    alg_vec_drop(&v);
}

int main(void) {
    run_test(test_public_api, "integration", "alg", "public_api");

    return 0;
}

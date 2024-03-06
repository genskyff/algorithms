#include "hashmap.h"
#include "helper.h"

#define LEN 6
HashMap test_data() {
    key_t   keys[LEN]   = {1, 2, 3, 4, 5, 6};
    value_t values[LEN] = {1, 2, 3, 4, 5, 6};
    return init(keys, values, LEN);
}

int main(void) {
    HashMap map = test_data();
    show(stdout, &map);
    show(NULL, NULL);

    return 0;
}

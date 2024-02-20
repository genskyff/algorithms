#include "sqlist.h"
#include "test.h"
#include "type.h"
#include "utils.h"


#define LEN 6
SqList list = {.data = {0, 1, 2, 3, 4, 5}, .len = LEN};

bool test_is_empty(void) { return true; }

bool test_get(void) { return true; }

int main(void) {
    char *prefix = "ds";
    run_test(test_is_empty, prefix, "sqlist_is_empty");

    return 0;
}

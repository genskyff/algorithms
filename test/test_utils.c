#include "data.h"
#include "utils.h"
#include <stdio.h>

void test_show(void);

int main(void) {
    test_show();

    return 0;
}

void test_show(void) {
    printf("\n---- test_show ----\n");
    printf("show:\n");
    show(UNSTORED, LEN);
}

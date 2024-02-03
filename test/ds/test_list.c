#include "../src/data_structure/linear_list.h"

int main(void) {
    LinearList L;
    int        i, e;

    clear(&L);

    for (int j = 0; j < MAXSIZE; j++)
        insert(&L, j, j + 1);
    show(L);

    for (int j = 0; j < MAXSIZE; j += 2)
        update(&L, j, 10);
    show(L);

    while (get_index(L, 10, i))
        delete (&L, i, &e);
    show(L);

    return 0;
}

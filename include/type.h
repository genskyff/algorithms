#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#define MAXLEN 100

typedef int elem_t;

typedef struct {
    elem_t data[MAXLEN];
    size_t len;
} SqList;

typedef struct Node {
    elem_t       data;
    struct Node *next;
} Node;

#endif

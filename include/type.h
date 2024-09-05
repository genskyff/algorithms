#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#define MAXLEN 100

typedef int elem_t;

typedef struct Node {
    elem_t       data;
    size_t       height;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct TreeNode {
    elem_t           data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef enum { FORWARD, BACKWARD } Direction;
typedef enum { LEVEL_ORDER, PRE_ORDER, IN_ORDER, POST_ORDER } Order;

#endif

#ifndef ALG_TYPE_H
#define ALG_TYPE_H

#include <stdio.h>
#define MAXLEN 100

typedef int elem_t;

typedef struct Node {
    elem_t       data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct TreeNode {
    elem_t           data;
    size_t           level;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef enum { FORWARD, BACKWARD } Direction;
typedef enum { LEVEL_ORDER, PRE_ORDER, IN_ORDER, POST_ORDER } Order;

#endif

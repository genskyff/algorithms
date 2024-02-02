#include <stdio.h>
#include <stdbool.h>
#define MAXSIZE 20

// 定义线性表元素类型
typedef int ElemType;

void clear(struct LinearList *);
void show(struct LinearList);
bool is_empty(struct LinearList);
bool get_index(struct LinearList, ElemType, size_t *);
bool get(struct LinearList, size_t, ElemType *);
bool insert(struct LinearList *, size_t, ElemType);
bool update(struct LinearList *, size_t, ElemType);
bool remove(struct LinearList *, size_t, ElemType *);


// 定义线性表结构
typedef struct LinearList
{
    // 线性表长度
    ElemType data[MAXSIZE];
    // 数据长度
    size_t len;

    void (*clear)(struct LinearList *);
    void (*show)(struct LinearList);
    bool (*is_empty)(struct LinearList);
    bool (*get_index)(struct LinearList, ElemType, size_t *);
    bool (*get)(struct LinearList, size_t, ElemType *);
    bool (*insert)(struct LinearList *, size_t, ElemType);
    bool (*update)(struct LinearList *, size_t, ElemType);
    bool (*remove)(struct LinearList *, size_t, ElemType *);
} LinearList;

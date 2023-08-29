#include <stdio.h>
#include <stdbool.h>
#define MAXSIZE 20

// 定义线性表元素类型
typedef int ElemType;

// 定义线性表结构
typedef struct LinearList
{
    // 线性表长度
    ElemType data[MAXSIZE];
    // 数据长度
    int length;

    void (*clear)(struct LinearList *);
    void (*show)(struct LinearList);
    bool (*is_empty)(struct LinearList);
    bool (*get_index)(struct LinearList, ElemType, int *);
    bool (*get)(struct LinearList, int, ElemType *);
    bool (*insert)(struct LinearList *, int, ElemType);
    bool (*update)(struct LinearList *, int, ElemType);
    bool (*remove)(struct LinearList *, int i, ElemType *);
} LinearList;

// 初始化
void clear(LinearList *L)
{
    L->length = 0;
}

// 打印
void show(LinearList L)
{
    for (int i = 0; i < L.length; i++)
        printf("%d ", L.data[i]);
    printf("\n");
}

// 是否为空
bool is_empty(LinearList L)
{
    return L.length == 0 ? true : false;
}

// 获取值为e的元素下标i
bool get_index(LinearList L, ElemType e, int *i)
{
    if (L.length == 0)
        return false;

    for (int j = 0; j < L.length; j++)
        if (e == L.data[j])
            *i = j;

    return true;
}

// 获取下标为i的元素值e
bool get(LinearList L, int i, ElemType *e)
{
    if (L.length == 0 || i < 0 || i > L.length - 1)
        return false;

    *e = L.data[i];

    return true;
}

// 下标i处插入值为e的元素
bool insert(LinearList *L, int i, ElemType e)
{
    if (L->length == MAXSIZE || i < 0 || i > L->length)
        return false;

    if (i < L->length)
        for (int j = L->length - 1; j >= i; j--)
            L->data[j + 1] = L->data[j];

    L->data[i] = e;
    L->length++;

    return true;
}

// 修改下标i处的元素值为e
bool update(LinearList *L, int i, ElemType e)
{
    if (L->length == 0 || i < 0 || i > L->length - 1)
        return false;

    L->data[i] = e;

    return true;
}

// 删除下标i处的元素并获取其值
bool delete(LinearList *L, int i, ElemType *e)
{
    if (L->length == 0 || i < 0 || i > L->length - 1)
        return false;

    *e = L->data[i];

    if (i < L->length - 1)
        for (int j = i; j < L->length - 1; j++)
            L->data[j] = L->data[j + 1];

    L->length--;

    return true;
}

int main(void)
{
    LinearList L;
    int i, e;

    clear(&L);

    for (int j = 0; j < MAXSIZE; j++)
        insert(&L, j, j + 1);
    show(L);

    for (int j = 0; j < MAXSIZE; j += 2)
        update(&L, j, 10);
    show(L);

    while (get_index(L, 10, &i))
        delete(&L, i, &e);
    show(L);

    return 0;
}

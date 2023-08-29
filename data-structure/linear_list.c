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

// 清空
void clear(LinearList *L)
{
    L->len = 0;
}

// 打印
void show(LinearList L)
{
    for (size_t i = 0; i < L.len; i++)
        printf("%d ", L.data[i]);
    printf("\n");
}

// 是否为空
bool is_empty(LinearList L)
{
    return L.len == 0 ? true : false;
}

// 获取值为e的元素下标i
bool get_index(LinearList L, ElemType e, size_t *i)
{
    if (L.len == 0)
        return false;

    for (size_t j = 0; j < L.len; j++)
        if (e == L.data[j])
            *i = j;

    return true;
}

// 获取下标为i的元素值e
bool get(LinearList L, size_t i, ElemType *e)
{
    if (L.len == 0 || i < 0 || i > L.len - 1)
        return false;

    *e = L.data[i];

    return true;
}

// 下标i处插入值为e的元素
bool insert(LinearList *L, size_t i, ElemType e)
{
    if (L->len == MAXSIZE || i < 0 || i > L->len)
        return false;

    if (i < L->len)
        for (size_t j = L->len - 1; j >= i; j--)
            L->data[j + 1] = L->data[j];

    L->data[i] = e;
    L->len++;

    return true;
}

// 修改下标i处的元素值为e
bool update(LinearList *L, size_t i, ElemType e)
{
    if (L->len == 0 || i < 0 || i > L->len - 1)
        return false;

    L->data[i] = e;

    return true;
}

// 删除下标i处的元素并获取其值
bool delete(LinearList *L, size_t i, ElemType *e)
{
    if (L->len == 0 || i < 0 || i > L->len - 1)
        return false;

    *e = L->data[i];

    if (i < L->len - 1)
        for (size_t j = i; j < L->len - 1; j++)
            L->data[j] = L->data[j + 1];

    L->len--;

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

    while (get_index(L, 10, i))
        delete (&L, i, &e);
    show(L);

    return 0;
}

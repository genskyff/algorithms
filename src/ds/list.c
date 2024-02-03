#include "linear_list.h"

// 清空
void clear(LinearList *L) { L->len = 0; }

// 打印
void show(LinearList L) {
    for (size_t i = 0; i < L.len; i++)
        printf("%d ", L.data[i]);
    printf("\n");
}

// 是否为空
bool is_empty(LinearList L) { return L.len == 0 ? true : false; }

// 获取值为 e 的元素的索引值
bool get_index(LinearList L, ElemType e, size_t *i) {
    if (L.len == 0)
        return false;

    for (size_t j = 0; j < L.len; j++)
        if (e == L.data[j])
            *i = j;

    return true;
}

// 获取索引 i 的元素值 e
bool get(LinearList L, size_t i, ElemType *e) {
    if (L.len == 0 || i < 0 || i > L.len - 1)
        return false;

    *e = L.data[i];

    return true;
}

// 在索引 i 处插入值为 e 的元素
bool insert(LinearList *L, size_t i, ElemType e) {
    if (L->len == MAXSIZE || i < 0 || i > L->len)
        return false;

    if (i < L->len)
        for (size_t j = L->len - 1; j >= i; j--)
            L->data[j + 1] = L->data[j];

    L->data[i] = e;
    L->len++;

    return true;
}

// 修改索引 i 处的元素值为 e
bool update(LinearList *L, size_t i, ElemType e) {
    if (L->len == 0 || i < 0 || i > L->len - 1)
        return false;

    L->data[i] = e;

    return true;
}

// 删除索引 i 处的元素并获取其值
bool delete(LinearList *L, size_t i, ElemType *e) {
    if (L->len == 0 || i < 0 || i > L->len - 1)
        return false;

    *e = L->data[i];

    if (i < L->len - 1)
        for (size_t j = i; j < L->len - 1; j++)
            L->data[j] = L->data[j + 1];

    L->len--;

    return true;
}

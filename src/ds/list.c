#include "list.h"
#define _CRT_DIRECTORY_DEFINED
#include <stdio.h>

// 清空
void clear(List *L) { L->len = 0; }

// 打印
void show(List L) {
    for (size_t i = 0; i < L.len; i++)
        printf("%d ", L.data[i]);
    printf("\n");
}

// 是否为空
bool is_empty(List L) { return L.len == 0 ? true : false; }

// 获取值为 e 的元素的索引值
bool get_index(List L, elem_t e, size_t *i) {
    if (L.len == 0)
        return false;

    for (size_t j = 0; j < L.len; j++)
        if (e == L.data[j])
            *i = j;

    return true;
}

// 获取索引 i 的元素值 e
bool get(List L, size_t i, elem_t *e) {
    if (L.len == 0 || i < 0 || i > L.len - 1)
        return false;

    *e = L.data[i];

    return true;
}

// 在索引 i 处插入值为 e 的元素
bool insert(List *L, size_t i, elem_t e) {
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
bool update(List *L, size_t i, elem_t e) {
    if (L->len == 0 || i < 0 || i > L->len - 1)
        return false;

    L->data[i] = e;

    return true;
}

// 删除索引 i 处的元素并获取其值
bool delete(List *L, size_t i, elem_t *e) {
    if (L->len == 0 || i < 0 || i > L->len - 1)
        return false;

    *e = L->data[i];

    if (i < L->len - 1)
        for (size_t j = i; j < L->len - 1; j++)
            L->data[j] = L->data[j + 1];

    L->len--;

    return true;
}

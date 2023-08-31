

int main(void)
{
    int a[] = {6, 5, 3, 1, 8, 7, 2, 4};
    int n = sizeof(a) / sizeof(int);

    printf("排序前:\n");
    display(a, n);

    bubble_sort(a, n);

    printf("排序后:\n");
    display(a, n);

    return 0;
}

#include "QuickSort.h"

int arr[10] = {0};
int start = 0;
int end = 9;

int main()
{
    int arr[10] = {0};
    int start = 0;
    int end = 9;

    printf("enter ten number");
    for (int i = 0; i <= 9; i++)
        scanf("%d", &arr[i]);
    ShowArr(arr);
    QuickSort(arr, start, end);
    ShowArr(arr);
    return 0;
}

void QuickSortShow()
{
    /*Init a Stack to save the End & Start;
    */
    int arr[10] = {0};
    int start = 0;
    int end = 9;

    printf("enter ten number");
    for (int i = 0; i <= 9; i++)
        scanf("%d", &arr[i]);
//    ShowArr(arr);
    QuickSort(arr, start, end);
//    ShowArr(arr);
}

int Quick(int *arr, int start, int end)
{
    int pivot = arr[start];
    // 倒序查找较大的,end游标存储倒序信息
    while (start < end)
    {
        while (start < end)
        {
            if (arr[end] < pivot)
                break;
            end--;
        }
        arr[start] = arr[end];
        // 顺序查找比pivot小的
        while (start < end)
        {
            if (arr[start] > pivot)
                break;
            start++;
        }
        arr[end] = arr[start];
    }
    arr[start] = pivot;
    return start;
}

void QuickSort(int *arr, int start, int end)
{
    int mod = 0;
    mod = Quick(arr, start, end);
    for (int i = 0; i < 10; i++)
        printf("%d\t", arr[i]);
    printf("\n");
    // 如果左侧不为空，对左侧排序
    if (mod - start > 1)
        QuickSort(arr, start, mod - 1);
    // 如果右侧不为空，对右侧排序
    if (end - mod > 1)
        QuickSort(arr, mod + 1, end);
}

// a function swap_Node a & b;
// swap_Node is working
// swap sample arr[0] = 1; arr[1] = 2; swap_Node(&arr[1],&arr[0]);
void swap(int *a, int *b)
{
    int temp = (*b);
    *b = *a;
    *a = temp;
}

void getMod(int *arr, int start, int end)
{
    int mod = (end - start + 1) / 2 + start;
    if (arr[mod] > arr[end])
        swap(&arr[mod], &arr[end]);
    if (arr[start] > arr[end])
        swap(&arr[end], &arr[start]);
    if (arr[start] > arr[mod])
        swap(&arr[start], &arr[mod]);
}
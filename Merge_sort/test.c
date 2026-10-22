#include <stdio.h>
#include "merge.h"

int main()
{
    int arr[] = {6, 3, 8, 2, 7, 1, 5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before sorting: ");
    printArray(arr, n);

    mergeSort(arr, 0, n - 1);

    printf("After sorting:  ");
    printArray(arr, n);

    return 0;
}
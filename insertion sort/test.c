#include <stdio.h>
#include "insertion.h"

int main()
{
    int arr[] = {7, 3, 8, 2, 6, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before sorting: ");
    printArray(arr, n);

    insertionSort(arr, n);

    printf("After sorting:  ");
    printArray(arr, n);

    return 0;
}
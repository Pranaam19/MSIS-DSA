#include <stdio.h>
#include "insertion.h"

void insertionSort(int arr[], int n)
{
    int i, j, key;
  
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        // Shift elements greater than key to the right
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        // Insert key at the correct position
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}
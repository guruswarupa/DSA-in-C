// selection_sort.c
#include <stdio.h>
#include <stdlib.h>

// Function to perform Selection Sort
void selectionSort(int *arr, int n) {
    int i, j, minIdx;

    // One by one move the boundary of the unsorted subarray
    for (i = 0; i < n - 1; i++) {
        minIdx = i; // Find the minimum element in unsorted array

        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j; // Update the index of the minimum element
            }
        }

        // Swap the found minimum element with the first element of unsorted subarray
        int temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

// Function to print the array
void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function
int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Dynamically allocate memory for n elements
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1; // Exit if memory allocation fails
    }

    // Input elements
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Original array: \n");
    printArray(arr, n);

    selectionSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);

    // Free allocated memory
    free(arr);
    
    return 0;
}

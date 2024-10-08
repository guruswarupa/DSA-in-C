#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void binarySearch(int arr[], int size, int key);
void sortArray(int arr[], int size);
void printArray(int arr[], int size);

int main() {
    int size, key;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);

    int *arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;  // Exit the program if memory allocation fails
    }

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array before binary search
    sortArray(arr, size);
    printf("Sorted array: ");
    printArray(arr, size);

    printf("Enter the element to search for: ");
    scanf("%d", &key);

    binarySearch(arr, size, key);

    free(arr); // Free the allocated memory
    return 0;
}

void binarySearch(int arr[], int size, int key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;   //to prevent Integer/Datatype overflow 

        if (arr[mid] == key) {
            printf("Element %d found at index %d (Binary Search)\n", key, mid);
            return;
        }
        
        if (arr[mid] < key) {
            left = mid + 1;
        } 

        else {
            right = mid - 1;
        }
    }
    printf("Element %d not found in the array (Binary Search)\n", key);
}

// Function to sort the array using Bubble Sort
void sortArray(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

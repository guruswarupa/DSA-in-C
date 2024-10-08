#include <stdio.h>
#include <stdlib.h>

void linearSearch(int arr[], int size, int key);

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

    printf("Enter the element to search for: ");
    scanf("%d", &key);

    linearSearch(arr, size, key);

    free(arr); // Free the allocated memory
    return 0;
}

// Linear Search Implementation
void linearSearch(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            printf("Element %d found at index %d (Linear Search)\n", key, i);
            return;
        }
    }
    printf("Element %d not found in the array (Linear Search)\n", key);
}

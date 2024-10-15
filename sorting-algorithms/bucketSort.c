#include <stdio.h>
#include <stdlib.h>

// Function to perform insertion sort on individual buckets
void insertionSort(float* bucket, int size) {
    for (int i = 1; i < size; ++i) {
        float key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

// Function to sort arr[] of size n using bucket sort
void bucketSort(float arr[], int n) {
    // Create n empty buckets
    float** b = (float**)malloc(n * sizeof(float*));
    int* bucketSize = (int*)malloc(n * sizeof(int)); // To track sizes of each bucket
    for (int i = 0; i < n; i++) {
        b[i] = (float*)malloc(n * sizeof(float)); // Allocate space for each bucket
        bucketSize[i] = 0; // Initialize the size of each bucket
    }

    // Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i]; // Index in bucket
        b[bi][bucketSize[bi]] = arr[i]; // Place the element in the bucket
        bucketSize[bi]++; // Increment the size of the bucket
    }

    // Sort individual buckets using insertion sort
    for (int i = 0; i < n; i++) {
        insertionSort(b[i], bucketSize[i]); // Sort each bucket
    }

    // Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bucketSize[i]; j++) {
            arr[index++] = b[i][j];
        }
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(b[i]); // Free each bucket
    }
    free(b); // Free the bucket array
    free(bucketSize); // Free the bucket size array
}

// Driver program to test above function
int main() {
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);
    bucketSort(arr, n);

    printf("Sorted array is:\n");
    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");

    return 0;
}

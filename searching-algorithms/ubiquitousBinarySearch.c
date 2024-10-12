#include <stdio.h>

// Returns location of key, or -1 if not found
int BinarySearch(int A[], int l, int r, int key) {
    int m;

    while (l <= r) {
        m = l + (r - l) / 2; // Calculate mid index

        if (A[m] == key) // First comparison
            return m; // Key found

        if (A[m] < key) // Second comparison
            l = m + 1; // Search in the right half
        else
            r = m - 1; // Search in the left half
    }

    return -1; // Key not found
}

// Driver code to test the BinarySearch function
int main() {
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Sample sorted array
    int n = sizeof(A) / sizeof(A[0]); // Size of the array
    int key = 7; // Key to search for
    int result = BinarySearch(A, 0, n - 1, key); // Call the BinarySearch function

    if (result != -1) {
        printf("Element %d found at index %d.\n", key, result);
    } else {
        printf("Element %d not found in the array.\n", key);
    }

    return 0; // Return success
}

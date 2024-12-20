#include <stdio.h>

// Function to search x in the given array
void sentinelSearch(int arr[], int n, int key) {
    // Last element of the array
    int last = arr[n - 1];

    // Element to be searched is placed at the last index
    arr[n - 1] = key;
    int i = 0;

    while (arr[i] != key) {
        i++;
    }

    // Put the last element back
    arr[n - 1] = last;

    if ((i < n - 1) || (arr[n - 1] == key)) {
        printf("%d is present at index %d\n", key, i);
    } else {
        printf("Element Not found\n");
    }
}

// Driver code
int main() {
    int arr[] = { 10, 20, 180, 30, 60, 50, 110, 100, 70 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 180;

    sentinelSearch(arr, n, key);

    return 0;
}

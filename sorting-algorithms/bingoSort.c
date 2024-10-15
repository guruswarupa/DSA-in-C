#include <stdio.h>
#include <stdlib.h>

// Function for finding the maximum and minimum element of the array
void maxMin(int arr[], int n, int* bingo, int* nextBingo) {
    *bingo = arr[0];
    *nextBingo = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < *bingo) {
            *bingo = arr[i];
        }
        if (arr[i] > *nextBingo) {
            *nextBingo = arr[i];
        }
    }
}

// Function to sort the array
void bingoSort(int arr[], int n) {
    int bingo, nextBingo;
    maxMin(arr, n, &bingo, &nextBingo);
    int largestEle = nextBingo;
    int nextElePos = 0;

    while (bingo < nextBingo) {
        // Will keep track of the element position to be shifted to their correct position
        int startPos = nextElePos;

        for (int i = startPos; i < n; i++) {
            if (arr[i] == bingo) {
                // Swap the elements
                int temp = arr[i];
                arr[i] = arr[nextElePos];
                arr[nextElePos] = temp;
                nextElePos++;
            } else if (arr[i] < nextBingo) {
                nextBingo = arr[i];
            }
        }
        bingo = nextBingo;
        nextBingo = largestEle;
    }
}

// Function to print the array
void printArray(int arr[], int n) {
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Driver Code
int main() {
    int arr1[] = {5, 4, 8, 5, 4, 8, 5, 4, 4, 4};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    bingoSort(arr1, size1);
    printArray(arr1, size1);

    int arr2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    bingoSort(arr2, size2);
    printArray(arr2, size2);

    int arr3[] = {0, 1, 0, 1, 0, 1};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    bingoSort(arr3, size3);
    printArray(arr3, size3);

    return 0;
}

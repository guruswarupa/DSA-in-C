#include <stdio.h>
#include <math.h>

// 'gcc metaBinarySearch.c -o metaBinarySearch -lm' to compile

// Function to show the working of Meta binary search
int bsearch(int A[], int n, int key_to_search) {
    // Set number of bits to represent largest array index
    int lg = (int)(log2(n - 1)) + 1; 

    int pos = 0;
    for (int i = lg; i >= 0; i--) {
        if (A[pos] == key_to_search) {
            return pos;
        }

        // Incrementally construct the index of the target value
        int new_pos = pos | (1 << i);

        // find the element in one direction and update position
        if ((new_pos < n) && (A[new_pos] <= key_to_search)) {
            pos = new_pos;
        }
    }

    // if element found return pos otherwise -1
    return ((A[pos] == key_to_search) ? pos : -1);
}

// Driver code
int main(void) {
    int A[] = { -2, 10, 100, 250, 32315 };
    int n = sizeof(A) / sizeof(A[0]);

    printf("%d\n", bsearch(A, n, 10));

    return 0;
}
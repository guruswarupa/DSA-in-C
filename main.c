#include <stdio.h>
#include <string.h>

void computeLPSArray(char* pattern, int M, int* lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMP(char* text, char* pattern) {
    int N = strlen(text);
    int M = strlen(pattern);
    int lps[M];
    computeLPSArray(pattern, M, lps);

    int i = 0, j = 0;
    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
        } else if (pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    char text[] = "ABABDABACDABABCABABCADAB";
    char pattern[] = "CADAB";
    KMP(text, pattern);
    return 0;
}

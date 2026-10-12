#include <stdio.h>
#include <stdlib.h>

void aiPrime(int n, int m) {
    int i, j, k, nm = (m - n) + 1;
    int *p = (int*)malloc((m + 1) * sizeof(int));
    for (i = 1; i <= m; i++) {
        p[i] = i;
    }
    p[0] = nm;
    for (i = 1; i <= m; i++) {
        if (p[i] == 0) {
            continue;
        }
        for (j = 2; j * j <= m; j++) {
            for (k = j * j; k <= m; k += j) {
                if (p[k] == 0) {
                    continue;
                }
                p[k] = 0;
                p[0]--;
            }
        }
    }
    printf("%d\n", p[0]);
    for (i = n; i <= m; i++) {
        if (p[i] != 0) {
            printf("%d ", p[i]);
        }
    }
    putchar('\n');
    free(p);
}

void swap(int *a, int *b) {
    int tmp = *a;
    if (*a > *b) {
        *a = *b;
        *b = tmp;
    }
}

int main() {
    int n = 20, m = 2;
    swap(&n, &m);
    aiPrime(n, m);
    return 0;
}
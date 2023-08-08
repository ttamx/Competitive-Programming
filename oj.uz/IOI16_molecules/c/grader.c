#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "molecules_c.h"

int main() {
    int n, l, u;
    assert(3 == scanf("%d %d %d", &n, &l, &u));
    int* w = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        assert(1 == scanf("%d", &w[i]));
    int* result = (int*)malloc(n * sizeof(int));
    int result_len = find_subset(l, u, w, n, result);


    // Intended behavior is that contestant gets WA if he returns an incorrect array length.
    printf("%d\n", result_len);
    if (0 <= result_len && result_len <= n) {
        for (int i = 0; i < result_len; i++)
            printf("%d%c", result[i], " \n"[i == result_len - 1]);
        printf("\n");
    } else {
        printf("incorrect array length\n");
    }
}


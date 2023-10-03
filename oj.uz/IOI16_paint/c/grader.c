#include "paint_c.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define S_MAX_LEN (200 * 1000)
char s[S_MAX_LEN + 1];

int main() {
    assert(1 == scanf("%s", s));
    int n = strlen(s);
    int k;
    assert(1 == scanf("%d", &k));
    int* c = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        assert(1 == scanf("%d", &c[i]));
    }
    char* result = (char*)malloc((n + 1) * sizeof(char));
    solve_puzzle(n, s, k, c, result);
    result[n] = 0;

    
    printf("%s\n", result);
    return 0;
}

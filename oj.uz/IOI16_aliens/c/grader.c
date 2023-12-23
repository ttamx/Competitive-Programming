#include "aliens_c.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int n, m, k;
    assert(3 == scanf("%d %d %d", &n, &m, &k));
    int* r = (int*)malloc(n * sizeof(int));
    int* c = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        assert(2 == scanf("%d %d", &r[i], &c[i]));
    }
    long long ans = take_photos(n, m, k, r, c);
    
    
    printf("%lld\n", ans);
    return 0;
}

#include "railroad_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int n, i, *s, *t;
    assert(1 == scanf("%d", &n));
    s = malloc(n * sizeof(int)), t = malloc(n * sizeof(int));
    for (i = 0; i < n; ++i)
        assert(2 == scanf("%d %d", &s[i], &t[i]));
    long long answer = plan_roller_coaster(n, s, t);
    printf("%lld\n", answer);
    free(s), free(t);
    return 0;
}

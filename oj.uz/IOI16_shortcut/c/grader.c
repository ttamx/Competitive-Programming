#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "shortcut_c.h"

int main()
{
    int n, c;
    assert(2 == scanf("%d%d", &n, &c));
    int *l = (int *)malloc((n - 1) * sizeof(int)); // N > 1
    int *d = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        assert(1 == scanf("%d", &l[i]));
    }
    for (int i = 0; i < n; i++) {
        assert(1 == scanf("%d", &d[i]));
    }
    long long t = find_shortcut(n, l, d, c);
    
    
    printf("%lld\n", t);
    
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

signed main() {
    int a, b;
    scanf("%d %d", &a, &b);
    if(a == b) {
        printf("1\n%d\n", b);
    }
    else {
        printf("3\n%d %d %d\n", b, b, 3 * a - 2 * b);
    }
    return 0;
}
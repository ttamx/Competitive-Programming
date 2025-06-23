#include "pizza.cpp"
#include <cstdio>

void get(int &x) {
    int c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    x = c - '0';
    c = getchar();
    while (c >= '0' && c <= '9') {
        x *= 10;
        x += c - '0';
        c = getchar();
    }
}
int main() {
    int M;
    std::vector<int> n;
    std::vector<int> a;
    int tmp;

    get(M);
    n.resize(M);
    a.resize(M);
    for (int i = 0; i < M; ++i) {
        get(n[i]);
        get(a[i]);
    }

    int result = countangles(M, n, a);
    printf("%d\n", result);

    return 0;
}
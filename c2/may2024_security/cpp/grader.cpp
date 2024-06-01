#include "security.cpp"
#include <cassert>
#include <cstdio>
#include <vector>

int main() {
    int n, m, q;
    assert(scanf("%d%d%d", &n, &m, &q));
    std::vector<int> s;
    s.reserve(n);
    for (int i = 0; i < n; i++) {
        int s_i;
        assert(scanf("%d", &s_i));
        s.push_back(s_i);
    }
    std::vector<int> u, v;
    u.reserve(m);
    v.reserve(m);
    for (int j = 0; j < m; j++) {
        int u_i, v_i;
        assert(scanf("%d%d", &u_i, &v_i));
        u.push_back(u_i);
        v.push_back(v_i);
    }
    std::vector<int> a;
    a.reserve(q);
    for (int k = 0; k < q; k++) {
        int a_i;
        assert(scanf("%d", &a_i));
        a.push_back(a_i);
    }
    kingdom(n, m, q, u, v, s);
    for (int k = 0; k < q; k++) {
        printf("%lld\n", answer_query(a[k]));
    }
    return 0;
}
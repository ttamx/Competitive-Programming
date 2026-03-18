#include <bits/stdc++.h>

using namespace std;

struct deg_pair {
    int u, d;
    bool operator < (const deg_pair& o) const {
        if(d != o.d) {
            return d > o.d;
        }
        return u < o.u;
    }
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> deg(n + 1);
    for(int i=1, u, v; i<=m; ++i) {
        cin >> u >> v;
        deg[u]++, deg[v]++;
    }
    // max size
    vector<deg_pair> sorting(n + 1);
    for(int i=1; i<=n; ++i) {
        sorting[i] = {i, deg[i]};
    }
    sort(sorting.begin() + 1, sorting.end());
    int sz = 0;
    vector<bool> used(n + 1, false);
    for(int i=1; i<=n; ++i) {
        int ii = sorting[i].u;
        if(deg[ii] >= sz) {
            sz++;
            used[ii] = true;
        }
    }
    int max_cnt = 1;
    for(int i=1; i<=n; ++i) {
        if(deg[i] == sz - 1 && !used[i]) {
            max_cnt++;
        }
    }
    cout << max_cnt << " ";
    // min size
    array<int, 2> bro = {0, 1};
    for(int i=1; i<=n; ++i) {
        if(!used[i]) {
            continue;
        }
        if(deg[i] == sz - 1) {
            bro[0]++;
        }
        if(deg[i] == sz) {
            bro[1]++;
        }
    }
    cout << (bro[0] ? bro[0]: bro[1]) << "\n";
}

signed main(int argc, char *argv[]) {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int q;
    cin >> q;
    while(q--) {
        solve();
    }
    return 0;
}
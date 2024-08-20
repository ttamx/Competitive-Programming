#include <bits/stdc++.h>

using namespace std;

const int MxN = 200020;

vector<int> adj[MxN];
int k, sz[MxN], cnt[MxN];
vector<int> path;
bool used[MxN];
long long answer = 0ll;

auto find_size(int u, int p) -> int {
    sz[u] = 1;
    for(auto v: adj[u]) {
        if(v == p || used[v]) {
            continue;
        }
        sz[u] += find_size(v, u);
    }
    return sz[u];
}

auto find_centroid(int u, int tot, int p) -> int {
    for(auto v: adj[u]) {
        if(v == p || used[v]) {
            continue;
        }
        if(sz[v] * 2 > tot) {
            return find_centroid(v, tot, u);
        }
    }
    return u;
}

auto dfs(int u, int p, int d) -> void {
    path.emplace_back(d);
    for(auto v: adj[u]) {
        if(v == p || used[v]) {
            continue;
        }
        dfs(v, u, d + 1);
    }
}

auto decom(int u) -> void {
    u = find_centroid(u, find_size(u, 0), 0);
    used[u] = true;
    cnt[0] = 1;
    vector<int> all_path;
    for(auto v: adj[u]) {
        if(used[v]) {
            continue;
        }
        dfs(v, u, 1);
        for(auto x: path) {
            if(k - x < 0) {
                continue;
            }
            answer += cnt[k - x];
        }
        for(auto x: path) {
            if(x > k) {
                continue;
            }
            cnt[x]++;
        }
        for(auto x: path) {
            all_path.emplace_back(x);
        }
        path.clear();
    }
    for(auto x: all_path) {
        cnt[x]--;
    }
    for(auto v: adj[u]) {
        if(used[v]) {
            continue;
        }
        decom(v);
    }
}

auto main(int argc, char *argv[]) -> signed {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int n;
    cin >> n >> k;
    for(int i=2, u, v; i<=n; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    decom(1);
    cout << answer << "\n";
    return 0;
}
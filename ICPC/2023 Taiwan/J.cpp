#include <bits/stdc++.h>

using namespace std;

const int nx=105;

int n, m, u, v, t[nx], deg[nx], back[nx], cnt[nx], dp[nx];
vector<int> d[nx];


void solve()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>t[i], d[i].clear(), deg[i]=0;
    for (int i=1; i<=m; i++) cin>>u>>v, d[u].push_back(v), deg[v]++;
    queue<int> q;
    for (int i=0;i <n; i++) if (!deg[i]) q.push(i);
    while (!q.empty())
    {
        auto u=q.front();
        q.pop();
        
    }
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int _t; cin>>_t;
    while (_t--) solve();

}
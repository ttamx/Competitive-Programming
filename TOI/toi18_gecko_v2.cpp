#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k,p;
    cin >> n >> m >> k >> p;
    vector<int> g(k),eu(m),ev(m),w(m),pa(n,-1),dp(n,2e9),deg(m);
    vector<bool> vis(m);
    vector<vector<int>> adj(n),adj2(m);
    for(auto &x:g)cin >> x;
    for(int i=0;i<m;i++){
        cin >> eu[i] >> ev[i] >> w[i];
        adj[eu[i]].emplace_back(i);
        adj[ev[i]].emplace_back(i);
    }
    auto go=[&](int x,int i){
        return x^eu[i]^ev[i];
    };
    multiset<pair<int,int>> ms;
    dp[p]=0;
    ms.emplace(0,p);
    while(!ms.empty()){
        auto [d,u]=*ms.begin();
        ms.erase(ms.begin());
        for(auto i:adj[u]){
            int v=go(u,i);
            if(d+w[i]>=dp[v])continue;
            dp[v]=d+w[i];
            pa[v]=i;
            ms.emplace(dp[v],v);
        }
    }
    int cnt=0;
    for(auto &u:g){
        cout << dp[u] << ' ';
        while(pa[u]!=-1&&!vis[pa[u]]){
            vis[pa[u]]=true;
            cnt++;
            int v=go(u,pa[u]);
            if(pa[v]!=-1){
                adj2[pa[u]].emplace_back(pa[v]);
                deg[pa[v]]++;
            }
            u=v;
        }
    }
    cout << '\n';
    cout << cnt << '\n';
    queue<int> q;
    for(int i=0;i<m;i++)if(vis[i]&&!deg[i])q.emplace(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cout << eu[u] << ' ' << ev[u] << '\n';
        for(auto v:adj2[u])if(!(--deg[v]))q.emplace(v);
    }
}
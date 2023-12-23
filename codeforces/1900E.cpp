#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<vector<int>> adj(n+2),rev(n+2),adj2(n+2);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        rev[v].emplace_back(u);
    }
    stack<int> s;
    vector<bool> vis(n+2);
    function<void(int)> dfs=[&](int u){
        if(vis[u])return;
        vis[u]=true;
        for(auto v:adj[u])dfs(v);
        s.emplace(u);
    };
    for(int i=1;i<=n;i++)dfs(i);
    for(int i=1;i<=n;i++)vis[i]=false;
    vector<int> scc(n+2),sz(n+2);
    function<void(int,int)> dfs2=[&](int u,int rt){
        if(vis[u])return;
        vis[u]=true;
        scc[u]=rt;
        sz[rt]++;
        for(auto v:rev[u])dfs2(v,rt);
        s.emplace(u);
    };
    while(!s.empty()){
        int u=s.top();
        s.pop();
        dfs2(u,u);
    }
    vector<int> deg(n+2);
    for(int i=1;i<=n;i++)for(auto j:adj[i])if(scc[i]!=scc[j])adj2[scc[i]].emplace_back(scc[j]),deg[scc[j]]++;
    queue<int> q;
    vector<pair<int,ll>> dp(n+2);
    vector<ll> b(n+2);
    for(int i=1;i<=n;i++)b[scc[i]]+=a[i];
    for(int i=1;i<=n;i++)if(scc[i]==i&&deg[i]==0)q.emplace(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        dp[u].first+=sz[u];
        dp[u].second-=b[u];
        for(auto v:adj2[u]){
            dp[v]=max(dp[v],dp[u]);
            if(--deg[v]==0)q.emplace(v);
        }
    }
    auto [x,y]=*max_element(dp.begin(),dp.end());
    cout << x << " " << -y << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
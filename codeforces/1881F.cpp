#include<bits/stdc++.h>

using namespace std;

const int inf=1e9;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<bool> b(n);
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        x--;
        b[x]=true;
    }
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> dp(n,-inf);
    function<void(int,int)> dfs=[&](int u,int p){
        if(b[u])dp[u]=0;
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            dp[u]=max(dp[u],dp[v]+1);
        }
    };
    int ans=inf;
    function<void(int,int,int)> dfs2=[&](int u,int p,int d){
        d++;
        if(b[u])d=max(d,0);
        ans=min(ans,max({0,dp[u],d}));
        pair<int,int> mx(-inf,-inf);
        for(auto v:adj[u]){
            if(v==p)continue;
            mx.second=max(mx.second,dp[v]);
            if(mx.second>mx.first)swap(mx.second,mx.first);
        }
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs2(v,u,max(d,(dp[v]==mx.first?mx.second:mx.first)+1));
        }
    };
    dfs(0,-1);
    dfs2(0,-1,-inf);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
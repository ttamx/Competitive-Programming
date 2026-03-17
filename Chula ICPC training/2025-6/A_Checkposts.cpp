#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;
const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int m;
    cin >> m;
    vector<vector<int>> adj(n),rev(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        rev[v].emplace_back(u);
    }
    vector<bool> vis(n);
    vector<int> ord;
    function<void(int)> dfs=[&](int u){
        if(vis[u])return;
        vis[u]=true;
        for(auto v:adj[u])dfs(v);
        ord.emplace_back(u);
    };
    for(int i=0;i<n;i++)dfs(i);
    vis.assign(n,false);
    reverse(ord.begin(),ord.end());
    int mn=INF,cnt=0;
    function<void(int)> dfs2=[&](int u){
        vis[u]=true;
        if(a[u]<mn)mn=a[u],cnt=1;
        else if(a[u]==mn)cnt++;
        for(auto v:rev[u])if(!vis[v])dfs2(v);
    };
    long long ans=0,ways=1;
    for(auto i:ord)if(!vis[i]){
        mn=INF,cnt=0;
        dfs2(i);
        ans+=mn;
        ways=ways*cnt%MOD;
    }
    cout << ans << " " << ways << "\n";
}
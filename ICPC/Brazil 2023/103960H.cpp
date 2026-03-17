#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> edges(m);
    vector<vector<int>> adj(n),rev(n);
    for(auto &[u,v]:edges){
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        rev[v].emplace_back(u);
    }
    vector<int> ord(n);
    vector<bool> vis(n);
    function<void(int)> dfs=[&](int u){
        if(vis[u])return;
        vis[u]=true;
        for(auto v:adj[u]){
            dfs(v);
        }
        ord.emplace_back(u);
    };
    int buf=0;
    vector<int> lab(n,-1);
    function<void(int)> dfs2=[&](int u){
        if(lab[u]!=-1)return;
        lab[u]=buf;
        for(auto v:rev[u]){
            dfs2(v);
        }
    };
    for(int i=0;i<n;i++)dfs(i);
    reverse(ord.begin(),ord.end());
    for(auto i:ord){
        if(lab[i]!=-1)continue;
        dfs2(i);
        buf++;
    }
    int ans=0;
    vector<int> deg_in(buf),deg_out(buf);
    for(auto [u,v]:edges){
        u=lab[u],v=lab[v];
        if(u==v)continue;
        deg_out[u]++;
        deg_in[v]++;
    }
    if(buf==1){
        cout << 0 << "\n";
        exit(0);
    }
    int c_in=count(deg_in.begin(),deg_in.end(),0);
    int c_out=count(deg_out.begin(),deg_out.end(),0);
    cout << max(c_in,c_out) << "\n";
}
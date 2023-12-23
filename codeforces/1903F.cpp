#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> edge(m);
    for(auto &[u,v]:edge)cin >> u >> v,u--,v--;
    auto check=[&](int d){
        vector<vector<int>> adj(6*n),rev(6*n);
        vector<bool> vis(6*n);
        vector<int> disc,scc(6*n);
        auto link=[&](int u,int v){
            adj[u].emplace_back(v);
            rev[v].emplace_back(u);
        };
        auto build=[&](auto &self,int l,int r,int i){
            if(l==r)return void(link(2*n+i,l+n));
            int m=(l+r)/2;
            self(self,l,m,i*2);
            self(self,m+1,r,i*2+1);
            link(2*n+i,2*n+i*2);
            link(2*n+i,2*n+i*2+1);
        };
        auto connect=[&](auto &self,int l,int r,int i,int x,int y,int u){
            if(y<l||r<x)return;
            if(x<=l&&r<=y)return void(link(u,2*n+i));
            int m=(l+r)/2;
            self(self,l,m,i*2,x,y,u);
            self(self,m+1,r,i*2+1,x,y,u);
        };
        build(build,0,n-1,1);
        for(int i=0;i<n;i++){
            connect(connect,0,n-1,1,i-d+1,i-1,i);
            connect(connect,0,n-1,1,i+1,i+d-1,i);
        }
        for(auto [u,v]:edge)link(u+n,v),link(v+n,u);
        auto dfs=[&](auto &self,int u){
            if(vis[u])return;
            vis[u]=true;
            for(auto v:adj[u])self(self,v);
            disc.emplace_back(u);
        };
        auto dfs2=[&](auto &self,int u,int id){
            if(vis[u])return;
            vis[u]=true;
            scc[u]=id;
            for(auto v:rev[u])self(self,v,id);
        };
        for(int i=0;i<6*n;i++)dfs(dfs,i);
        for(int i=0;i<6*n;i++)vis[i]=false;
        reverse(disc.begin(),disc.end());
        for(auto i:disc)dfs2(dfs2,i,i);
        for(int i=0;i<n;i++)if(scc[i]==scc[i+n])return false;
        return true;
    };
    int l=0,r=n;
    while(l<r){
        int m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
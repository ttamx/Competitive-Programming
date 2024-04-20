#include<bits/stdc++.h>

using namespace std;

struct Kosaraju{
    int n;
    vector<vector<int>> adj,rev;
    vector<int> scc;
    Kosaraju(){}
    Kosaraju(int _n){
        init(_n);
    }
    void init(int _n){
        n=_n;
        adj.assign(n,vector<int>{});
        rev.assign(n,vector<int>{});
        scc.clear();
    }
    void add(int u,int v){
        adj[u].emplace_back(v);
        rev[v].emplace_back(u);
    }
    vector<int> work(){
        if(!scc.empty())return scc;
        scc.assign(n,-1);
        vector<bool> vis(n,false);
        vector<int> ord;
        function<void(int)> dfs=[&](int u){
            if(vis[u])return;
            vis[u]=true;
            for(auto v:adj[u])dfs(v);
            ord.emplace_back(u);
        };
        int cur=0;
        function<void(int)> dfs2=[&](int u){
            scc[u]=cur;
            for(auto v:rev[u])if(scc[v]==-1)dfs2(v);
        };
        for(int i=0;i<n;i++)dfs(i);
        reverse(ord.begin(),ord.end());
        for(auto u:ord)if(scc[u]==-1){
            dfs2(u);
            cur++;
        }
        return scc;
    }
};

struct TwoSAT{
    int n;
    Kosaraju g;
    int state;
    TwoSAT(){}
    TwoSAT(int _n){
        init(_n);
    }
    void init(int _n){
        n=_n;
        g.init(2*n);
        state=-1;
    }
    void add(int u,int v,bool p,bool q){
        g.add(p?u+n:u,q?v+n:v);
    }
    bool work(){
        if(state!=-1)return state;
        state=1;
        auto scc=g.work();
        for(int i=0;i<n;i++)state&=scc[i]!=scc[i+n];
        return state;
    }
};

void solve(){
    int n,m;
    cin >> n >> m;
    TwoSAT g(m);
    for(int i=0;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        g.add(u,v,false,true);
        g.add(v,u,false,true);
    }
    for(int i=0;i<m;i+=2){
        int u,v;
        cin >> u >> v;
        u--,v--;
        g.add(u,v,true,false);
        g.add(v,u,true,false);
    }
    cout << "NY"[g.work()];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(5);
    while(t--)solve();
}
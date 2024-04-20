#include<bits/stdc++.h>

using namespace std;

struct Tarjan{
    int n;
    vector<vector<int>> adj;
    vector<int> disc,low,scc;
    Tarjan(){}
    Tarjan(int _n){
        init(_n);
    }
    void init(int _n){
        n=_n;
        adj.assign(n,vector<int>{});
        disc.assign(n,-1);
        low.assign(n,-1);
        scc.clear();
    }
    void add(int u,int v){
        adj[u].emplace_back(v);
    }
    vector<int> work(){
        if(!scc.empty())return scc;
        scc.assign(n,-1);
        vector<bool> inpath(n);
        stack<int> path;
        int timer=-1,cur=0;
        function<void(int)> dfs=[&](int u){
            disc[u]=low[u]=++timer;
            path.emplace(u);
            inpath[u]=true;
            for(auto v:adj[u]){
                if(disc[v]==-1){
                    dfs(v);
                    low[u]=min(low[u],low[v]);
                }else if(inpath[v]){
                    low[u]=min(low[u],disc[v]);
                }
            }
            if(low[u]==disc[u]){
                int v;
                do{
                    v=path.top();
                    path.pop();
                    inpath[v]=false;
                    scc[v]=cur;
                }while(v!=u);
                scc[u]=cur++;
            }
        };
        for(int i=0;i<n;i++)if(disc[i]==-1)dfs(i);
        return scc;
    }
};

struct TwoSAT{
    int n;
    Tarjan g;
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
    void add(int p,int q){
        g.add(p<0?~p+n:p,q<0?~q+n:q);
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
        g.add(~u,v);
        g.add(~v,u);
    }
    for(int i=0;i<m;i+=2){
        int u,v;
        cin >> u >> v;
        u--,v--;
        g.add(u,~v);
        g.add(v,~u);
    }
    cout << "NY"[g.work()];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(5);
    while(t--)solve();
}
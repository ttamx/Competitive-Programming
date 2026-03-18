#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    multiset<int> ms;
    vector<int> cnt(n+1);
    vector<ll> f(n+1),ans(n);
    vector<int> sz(n),hv(n,-1),tin(n),pos(n);
    int timer=-1;
    function<void(int,int)> dfs=[&](int u,int p){
        tin[u]=++timer;
        pos[timer]=u;
        sz[u]=1;
        for(auto v:adj[u]){
            if(v!=p){
                dfs(v,u);
                sz[u]+=sz[v];
                if(hv[u]==-1||sz[v]>sz[hv[u]]){
                    hv[u]=v;
                }
            }
        }
    };
    auto upd=[&](int c,int v){
        auto &x=cnt[c];
        if(x){
            ms.extract(x);
            f[x]-=c;
        }
        x+=v;
        if(x){
            ms.emplace(x);
            f[x]+=c;
        }
    };
    function<void(int,int,bool)> sack=[&](int u,int p,bool del){
        for(auto v:adj[u]){
            if(v!=p&&v!=hv[u]){
                sack(v,u,true);
            }
        }
        if(hv[u]!=-1)sack(hv[u],u,false);
        upd(a[u],+1);
        for(auto v:adj[u]){
            if(v!=p&&v!=hv[u]){
                for(int i=tin[v];i<tin[v]+sz[v];i++){
                    upd(a[pos[i]],+1);
                }
            }
        }
        ans[u]=f[*ms.rbegin()];
        if(del){
            for(int i=tin[u];i<tin[u]+sz[u];i++){
                upd(a[pos[i]],-1);
            }
        }
    };
    dfs(0,-1);
    sack(0,-1,false);
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}
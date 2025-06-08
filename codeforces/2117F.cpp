#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> par(n,-1),dep(n);
    function<void(int)> dfs=[&](int u){
        for(auto v:adj[u]){
            if(v!=par[u]){
                par[v]=u;
                dep[v]=dep[u]+1;
                dfs(v);
            }
        }
    };
    dfs(0);
    vector<int> a;
    for(int i=1;i<n;i++){
        if(adj[i].size()==1){
            a.emplace_back(i);
        }
    }
    if(a.size()>2){
        cout << 0 << "\n";
    }else if(a.size()==1){
        mint ans=1;
        for(int i=0;i<n;i++)ans*=2;
        cout << ans << "\n";
    }else{
        int u=a[0],v=a[1];
        int uu=u,vv=v;
        while(uu!=vv){
            if(dep[uu]>dep[vv])uu=par[uu];
            else vv=par[vv];
        }
        int du=dep[u]-dep[uu];
        int dv=dep[v]-dep[vv];
        if(du>dv)swap(du,dv);
        mint ans=0;
        if(du==dv){
            ans=2;
            for(int i=0;i<dep[uu]+1;i++)ans*=2;
        }else{
            ans=3;
            int d=du*2+1;
            for(int i=0;i<n-d;i++)ans*=2;
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
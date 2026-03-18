#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> sz(n),rt(n),par(n);
    function<void(int,int,int)> dfs=[&](int u,int p,int r){
        par[u]=p;
        rt[u]=r;
        sz[u]=1;
        for(auto v:adj[u])if(v!=p){
            dfs(v,u,r);
            sz[u]+=sz[v];
        }
    };
    mint W=mint(n).inv()*mint(n).inv();
    for(int i=n-1;i>=0;i--){
        if(!sz[i]){
            dfs(i,-1,i);
            W*=mint(n)*mint(sz[i]);
        }
    }
    vector<mint> ans(n-1);
    if(rt[n-2]==n-1){
        int u=n-2;
        while(par[u]!=n-1)u=par[u];
        ans[u]=W;
    }else{
        for(auto v:adj[n-1]){
            ans[v]=W/mint(sz[n-1])*mint(sz[v]);
        }
        mint W2=W*mint(sz[n-1]+sz[n-2])/mint(sz[n-1])/mint(sz[n-2])/mint(n);
        for(int i=n-2;i>=0;i--){
            if(rt[i]==n-1)continue;
            if(rt[i]==n-2){
                ans[i]=W2;
                continue;
            }
            int r=rt[i];
            ans[i]=W*mint(sz[r])/mint(sz[n-1])/mint(sz[r])/mint(n);
        }
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
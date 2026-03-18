#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "data-structure/dsu.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    mint V;
    cin >> n >> m >> V;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<pair<int,int>> edges(m);
    vector<vector<int>> adj(n);
    for(auto &[u,v]:edges){
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    DSU dsu(n);
    vector<int> disc(n),low(n);
    int timer=-1;
    function<void(int,int)> dfs=[&](int u,int p){
        disc[u]=low[u]=++timer;
        for(auto v:adj[u]){
            if(v==p)continue;
            if(!disc[v]){
                dfs(v,u);
                low[u]=min(low[u],low[v]);
                if(low[v]<=disc[u]){
                    dsu.merge(u,v);
                }
            }else{
                low[u]=min(low[u],disc[v]);
            }
        }
    };
    dfs(0,-1);
    vector<vector<int>> adj2(n);
    for(auto [u,v]:edges){
        if(dsu.same(u,v)){
            adj2[u].emplace_back(v);
            adj2[v].emplace_back(u);
        }
    }
    vector<int> val(n,-1);
    for(int i=0;i<n;i++){
        if(a[i]==-1)continue;
        int j=dsu.find(i);
        if(val[j]==-1)val[j]=a[i];
        if(val[j]!=a[i]){
            cout << 0 << "\n";
            return;
        }
    }
    vector<int> col(n,-1);
    function<bool(int)> dfs2=[&](int u){
        for(auto v:adj2[u]){
            if(col[v]==-1){
                col[v]=col[u]^1;
                if(dfs2(v))return true;
            }else if(col[v]==col[u]){
                return true;
            }
        }
        return false;
    };
    mint ans=1;
    for(int i=0;i<n;i++){
        if(i!=dsu.find(i))continue;
        assert(col[i]==-1);
        col[i]=0;
        bool odd=dfs2(i);
        if(!odd){
            if(val[i]==-1)ans*=V;
        }else if(val[i]!=-1&&val[i]!=0){
            ans=0;
            break;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
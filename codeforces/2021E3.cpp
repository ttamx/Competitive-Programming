#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(k);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<tuple<int,int,int>> edges(m);
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    sort(edges.begin(),edges.end());
    DSU dsu(2*n-1);
    int cur=n;
    vector<int> b(2*n-1),sz(2*n-1);
    vector<vector<int>> adj(2*n-1);
    for(auto [w,u,v]:edges){
        if(dsu.same(u,v))continue;
        int x=cur++;
        b[x]=w;
        adj[x].emplace_back(dsu.find(u));
        adj[x].emplace_back(dsu.find(v));
        dsu.merge(x,u);
        dsu.merge(x,v);
    }
    vector<ll> c;
    for(auto x:a){
        sz[x]=1;
    }
    function<ll(int)> dfs=[&](int u){
        vector<ll> t;
        for(auto v:adj[u]){
            t.emplace_back(dfs(v)+1LL*sz[v]*(b[u]-b[v]));
            sz[u]+=sz[v];
        }
        if(t.empty())return 0LL;;
        if(t[0]>t[1])swap(t[0],t[1]);
        c.emplace_back(t[0]);
        return t[1];
    };
    c.emplace_back(dfs(cur-1));
    sort(c.rbegin(),c.rend());
    c.resize(n,0LL);
    ll ans=1LL*k*b[cur-1];
    for(int i=0;i<n;i++){
        ans-=c[i];
        cout << ans << " \n"[i==n-1];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
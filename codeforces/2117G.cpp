#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int>> edges(m);
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    sort(edges.begin(),edges.end());
    ll ans=LINF;
    DSU dsu(n);
    vector<int> mn(n,INF);
    for(auto [w,u,v]:edges){
        u=dsu.find(u),v=dsu.find(v);
        mn[u]=min({mn[u],mn[v],w});
        dsu.merge(u,v);
        if(dsu.same(0,n-1)){
            ans=min(ans,(ll)w+mn[dsu.find(0)]);
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
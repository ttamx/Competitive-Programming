#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    vector<tuple<ll,int,int>> edges(m);
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    int id=min_element(a.begin(),a.end())-a.begin();
    for(int i=0;i<n;i++)edges.emplace_back(a[i]+a[id],i,id);
    sort(edges.begin(),edges.end());
    ll ans=0;
    DSU dsu(n);
    for(auto [w,u,v]:edges)if(dsu.merge(u,v))ans+=w;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
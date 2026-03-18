#include "template.hpp"
#include "data-structure/dsu.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,mint>> edges(m);
    mint cost=1;
    for(auto &[u,v,w]:edges){
        cin >> u >> v;
        u--,v--;
        cost*=2;
        w=cost;
    }
    mint ans=0;
    int cnt=n;
    DSU dsu(n);
    reverse(edges.begin(),edges.end());
    for(auto [u,v,w]:edges){
        if(dsu.same(u,v))continue;
        if(cnt>2)dsu.merge(u,v),cnt--;
        else ans+=w;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
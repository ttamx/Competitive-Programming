#include "template.hpp"
#include "graph/graph-base.hpp"
#include "graph/strongly-connected-component.hpp"
#include "data-structure/dsu.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;
    using V = vector<tuple<int,int,int>>;
    V edge;
    for(int i=0;i<q;i++){
        int x,y;
        char c;
        cin >> x >> y >> c;
        x--,y--;
        y+=n;
        if(c=='R')edge.emplace_back(i,x,y);
        else edge.emplace_back(i,y,x);
    }
    vector<int> merge_time(q,q),id(n+m,-1);
    function<void(int,int,V)> dnc=[&](int l,int r,V a){
        if(l>r)return;
        int m=(l+r)/2;
        int n=0;
        for(auto [i,u,v]:a){
            if(id[u]==-1)id[u]=n++;
            if(id[v]==-1)id[v]=n++;
        }
        Graph<void,true> G(n);
        for(auto [i,u,v]:a)if(i<=m)G.add_edge(id[u],id[v]);
        auto scc=strongly_connected_component(G).second;
        V b,c;
        for(auto [i,u,v]:a){
            u=id[u],v=id[v];
            if(i<=m&&scc[u]==scc[v]){
                b.emplace_back(i,u,v);
                merge_time[i]=min(merge_time[i],m);
            }else{
                c.emplace_back(i,scc[u],scc[v]);
            }
        }
        for(auto [i,u,v]:a)id[u]=id[v]=-1;
        dnc(l,m-1,b),dnc(m+1,r,c);
    };
    dnc(0,q-1,edge);
    vector<vector<pair<int,int>>> merge_edge(q+1);
    for(auto [i,u,v]:edge)merge_edge[merge_time[i]].emplace_back(u,v);
    DSU dsu(n+m);
    ll ans=0;
    auto calc=[&](int i){
        ll x=dsu.size(i);
        return x>1?x*x:0LL;
    };
    for(int i=0;i<q;i++){
        for(auto [u,v]:merge_edge[i])if(!dsu.same(u,v)){
            ans-=calc(u)+calc(v);
            dsu.merge(u,v);
            ans+=calc(u);
        }
        cout << ans << "\n";
    }
}
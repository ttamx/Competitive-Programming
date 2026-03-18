#include "template.hpp"
#include "tree/hld.hpp"
#include "graph/graph-base.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/max-add.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int>> edges(m),mst,nonmst;
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    Graph g(n);
    DSU dsu(n);
    ll base=0;
    sort(edges.begin(),edges.end());
    ll tot=0;
    int cnt=0;
    bool fail=false;
    for(auto [w,u,v]:edges){
        if(dsu.merge(u,v)){
            base+=w;
            g.add_edge(u,v);
            mst.emplace_back(w,u,v);
        }else{
            fail=true;
            nonmst.emplace_back(w,u,v);
        }
        if(cnt<n-1){
            cnt++;
            tot+=w;
            if(cnt==n-1&&fail){
                cout << tot << "\n";
                return;
            }
        }
    }
    HLD hld(g);
    vector<vector<pair<int,int>>> adj(n);
    for(auto [w,u,v]:nonmst){
        if(hld.dep[u]>hld.dep[v]){
            swap(u,v);
        }
        adj[v].emplace_back(u,w);
    }
    LazySegmentTree<MaxAddAction<ll>> seg(n);
    for(auto [w,u,v]:mst){
        if(hld.dep[u]>hld.dep[v]){
            swap(u,v);
        }
        assert(hld.par[v]==u);
        seg.modify(hld.tin[v],w);
    }
    ll ans=LINF;
    for(auto [w,u,v]:nonmst){
        auto path=hld.get_path(u,v,false,true);
        for(auto [l,r]:path){
            seg.update(l,r,-LINF);
        }
        ans=min(ans,base+w-seg.query(1,n-1));
        for(auto [l,r]:path){
            seg.update(l,r,+LINF);
        }
    }
    if(n>=3&&m>n){
        ans=min(ans,tot-get<0>(edges[n-3])-get<0>(edges[n-2])+get<0>(edges[n-1])+get<0>(edges[n]));
    }
    cout << (ans<LINF?ans:-1LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
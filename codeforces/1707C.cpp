#include "template.hpp"
#include "data-structure/dsu.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> edge;
    DSU dsu(n);
    Graph g(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(dsu.merge(u,v)){
            g.add_edge(u,v);
        }else{
            edge.emplace_back(u,v);
        }
    }
    HLD hld(g);
    vector<int> a(n+1);
    for(auto [u,v]:edge){
        if(hld.dep[u]>hld.dep[v]){
            swap(u,v);
        }
        if(hld.is_ancestor(u,v)){
            int d=hld.dist(u,v);
            int x=hld.jump(v,u,d-1);
            a[hld.tin[x]]++;
            a[hld.tout[x]+1]--;
            a[hld.tin[v]]--;
            a[hld.tout[v]+1]++;
        }else{
            a[0]++;
            a[hld.tin[u]]--; 
            a[hld.tout[u]+1]++;
            a[hld.tin[v]]--;
            a[hld.tout[v]+1]++;
        }
    }
    for(int i=0;i<n;i++){
        a[i+1]+=a[i];
    }
    for(int i=0;i<n;i++){
        cout << (a[hld.tin[i]]>0?0:1);
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
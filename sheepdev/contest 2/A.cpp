#include "template.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"

using namespace std;

const int X=5e5+5;

uint64_t hsh[2*X];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<2*X;i++)hsh[i]=rng64();
    int k,n,q;
    cin >> k >> n >> q;
    vector<Graph<void,false>> g(k);
    vector<HLD<Graph<void,false>>> t;
    vector<vector<uint64_t>> vals;
    vector<vector<uint64_t>> dist;
    for(int i=0;i<k;i++){
        vector<uint64_t> a(n);
        for(auto &x:a){
            int v;
            cin >> v;
            x=hsh[v+X];
        }
        g[i]=read_tree(n);
        HLD hld(g[i]);
        t.emplace_back(hld);
        vals.emplace_back(a);
        function<void(int)> dfs=[&](int u){
            for(auto v:g[i][u])if(v!=hld.par[u]){
                a[v]+=a[u];
                dfs(v);
            }
        };
        dfs(0);
        dist.emplace_back(a);
    }
    while(q--){
        vector<uint64_t> b;
        for(int i=0;i<k;i++){
            int u,v;
            cin >> u >> v;
            u--,v--;
            int x=t[i].lca(u,v);
            b.emplace_back(dist[i][u]+dist[i][v]-2*dist[i][x]+vals[i][x]);
        }
        if(*min_element(b.begin(),b.end())==*max_element(b.begin(),b.end())){
            cout << ":>\n";
        }else{
            cout << ":<\n";
        }
    }
}
#include "template.hpp"
#include "data-structure/dsu.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const mint BASE=mint(3373);

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    Graph g(2*n-1);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        g.add_edge(u,i+n);
        g.add_edge(v,i+n);
    }
    HLD hld(g);
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<pair<int,int>>> b(2*n-1);
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(a[i][j]=='1'){
                int d=hld.dist(i,j);
                assert(d%2==0);
                int u=hld.jump(i,j,d/2);
                b[u].emplace_back(i,j);
            }
        }
    }
    DSU dsu(n);
    vector<vector<bool>> mark(n,vector<bool>(n));
    for(int s=0;s<2*n-1;s++){
        if(b[s].empty())continue;
        vector<int> par(2*n-1,-1);
        vector<int> q{s};
        for(int i=0;i<q.size();i++){
            int u=q[i];
            for(auto v:g[u]){
                if(v!=par[u]){
                    par[v]=u;
                    q.emplace_back(v);
                }
            }
        }
        for(auto [u,v]:b[s]){
            while(u!=v){
                assert((u<n)==(v<n));
                if(u<n){
                    if(mark[u][v])break;
                    mark[u][v]=true;
                    dsu.merge(u,v);
                }
                u=par[u];
                v=par[v];
            }
        }
    }
    vector<mint> label(2*n-1,mint(n));
    for(int i=0;i<n;i++)label[i]=dsu.find(i);
    int ans=0;
    for(int s=0;s<2*n-1;s++){
        vector<map<mint,int>> cnt(n);
        vector<int> dep(2*n-1,-1);
        vector<mint> val(2*n-1);
        dep[s]=0;
        for(auto x:g[s]){
            dep[x]=0;
            vector<int> q{x};
            for(int i=0;i<q.size();i++){
                int u=q[i];
                val[u]=val[u]*BASE+label[u]+1;
                for(auto v:g[u]){
                    if(dep[v]==-1){
                        dep[v]=dep[u]+(v<n);
                        val[v]=val[u];
                        q.emplace_back(v);
                    }
                }
            }
            for(auto u:q)if(u<n)ans+=cnt[dep[u]][val[u]];
            for(auto u:q)if(u<n)cnt[dep[u]][val[u]]++;
        }
    }
    cout << ans*2+n;
}
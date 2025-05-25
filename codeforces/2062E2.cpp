#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    auto g=read_tree(n);
    HLD hld(g);
    set<int> s;
    vector<int> cnt(n);
    auto update=[&](int v,int c){
        if(cnt[v]>0)s.erase(v);
        cnt[v]+=c;
        if(cnt[v]>0)s.emplace(v);
    };
    for(auto x:a){
        cnt[x]++;
        s.emplace(x);
    }
    int ans=-1;
    function<void(int,bool)> sack=[&](int u,int del){
        if(ans!=-1)return;
        for(auto v:g[u]){
            if(v!=hld.par[u]&&v!=hld.hv[u]){
                sack(v,true);
                if(ans!=-1)return;
            }
        }
        if(hld.hv[u]!=-1){
            sack(hld.hv[u],false);
            if(ans!=-1)return;
        }
        update(a[u],-1);
        for(auto v:g[u]){
            if(v!=hld.par[u]&&v!=hld.hv[u]){
                for(int i=hld.tin[v];i<=hld.tout[v];i++){
                    update(a[hld.ord[i]],-1);
                }
            }
        }
        auto it=s.upper_bound(a[u]);
        if(it!=s.end()&&next(it)==s.end()){
            ans=u;
            return;
        }
        if(del){
            for(int i=hld.tin[u];i<=hld.tout[u];i++){
                update(a[hld.ord[i]],+1);
            }
        }
    };
    sack(0,false);
    cout << ans+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
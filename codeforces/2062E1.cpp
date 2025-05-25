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
    vector<vector<int>> pos(n);
    for(int i=0;i<n;i++){
        pos[a[i]].emplace_back(i);
    }
    int mx=n-1;
    while(pos[mx].empty()){
        mx--;
    }
    int lca=-1;
    for(auto u:pos[mx]){
        if(lca==-1){
            lca=u;
        }else{
            lca=hld.lca(lca,u);
        }
    }
    for(int v=mx-1;v>=0;v--){
        if(pos[v].empty()){
            continue;
        }
        for(auto u:pos[v]){
            if(!hld.is_ancestor(u,lca)){
                cout << u+1 << "\n";
                return;
            }
        }
        lca=-1;
        for(auto u:pos[v]){
            if(lca==-1){
                lca=u;
            }else{
                lca=hld.lca(lca,u);
            }
        }
    }
    cout << 0 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
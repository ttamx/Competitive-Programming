#include "template.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"

void runcase(){
    int n,q;
    cin >> n >> q;
    Graph g(n);
    vector<int> p(n,-1);
    for(int i=1;i<n;i++){
        cin >> p[i];
        p[i]--;
        g.add_edge(p[i],i);
    }
    HLD hld(g);
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    int cnt=0;
    auto update=[&](int i,int v){
        if(i<1||i>=n)return;
        cnt+=hld.is_ancestor(p[a[i]],a[i-1])?v:0;
    };
    for(int i=1;i<n;i++){
        update(i,1);
    }
    while(q--){
        int x,y;
        cin >> x >> y;
        x--,y--;
        set<int> s;
        s.emplace(x);
        s.emplace(x+1);
        s.emplace(y);
        s.emplace(y+1);
        for(auto i:s){
            update(i,-1);
        }
        swap(a[x],a[y]);
        for(auto i:s){
            update(i,1);
        }
        cout << (cnt==n-1?"YES":"NO") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
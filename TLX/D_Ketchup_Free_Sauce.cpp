#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n),rev(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        rev[v].emplace_back(u);
    }
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<int> pos(n);
    for(int i=0;i<n;i++)pos[a[i]]=i;
    ll ans=0;
    Fenwick<int> f(n);
    vector<vector<int>> del(n);
    for(int i=0;i<n;i++){
        for(auto j:del[i]){
            f.update(j,-1);
        }
        int l=-1;
        for(auto j:rev[a[i]]){
            l=max(l,pos[j]);
        }
        ans+=f.query(l,i);
        f.update(i,1);
        int r=n;
        for(auto j:adj[a[i]]){
            r=min(r,pos[j]);
        }
        if(r<n){
            del[r].emplace_back(i);
        }
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
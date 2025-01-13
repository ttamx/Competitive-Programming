#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<tuple<int,int,int>> e(m);
    for(auto &[w,u,v]:e){
        cin >> u >> v >> w;
        u--,v--;
    }
    sort(e.begin(),e.end());
    DSU dsu(n);
    vector<int> ca(n),cb(n);
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        x--;
        ca[x]++;
    }
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        x--;
        cb[x]++;
    }
    ll ans=0;
    for(auto [w,u,v]:e){
        u=dsu.find(u);
        v=dsu.find(v);
        if(u==v)continue;
        ca[u]+=ca[v];
        cb[u]+=cb[v];
        dsu.merge(u,v);
        int used=min(ca[u],cb[u]);
        ca[u]-=used;
        cb[u]-=used;
        ans+=1ll*used*w;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    set<pair<int,int>> edges;
    vector<set<int>> adj(n);
    vector<int> deg(n);
    int cnt=0;
    auto upd=[&](int u,int v){
        if(u>v){
            swap(u,v);
        }
        if(edges.find(make_pair(u,v))==edges.end()){
            edges.emplace(u,v);
            adj[u].emplace(v);
            adj[v].emplace(u);
            deg[u]++;
            deg[v]++;
            cnt++;
        }else{
            edges.erase(make_pair(u,v));
            adj[u].erase(v);
            adj[v].erase(u);
            deg[u]--;
            deg[v]--;
            cnt--;
        }
    };
    vector<tuple<int,int,int>> ans;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        upd(u,v);
        for(int t=0;t<2;t++){
            if(deg[u]==2){
                int x=*adj[u].begin();
                int y=*adj[u].rbegin();
                ans.emplace_back(u,x,y);
                upd(u,x);
                upd(u,y);
                upd(x,y);
            }
            swap(u,v);
        }
    }
    set<pair<int,int>> s;
    int rt=-1;
    for(int i=0;i<n;i++){
        if(deg[i]>0){
            rt=i;
            for(auto j:adj[i]){
                s.emplace(i,j);
            }
            break;
        }
    }
    if(rt!=-1){
        DSU dsu(n);
        for(auto &[u,v]:edges){
            dsu.merge(u,v);
        }
        for(int i=0;i<n;i++){
            if(dsu.find(i)!=dsu.find(rt)){
                auto [u,v]=*s.begin();
                ans.emplace_back(u,v,i);
                s.erase(s.begin());
                s.emplace(i,u);
                s.emplace(i,v);
                dsu.merge(rt,i);
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto &[x,y,z]:ans){
        cout << x+1 << " " << y+1 << " " << z+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
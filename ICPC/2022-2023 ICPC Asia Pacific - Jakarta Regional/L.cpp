#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct DSU{
    int n;
    vector<int> p;
    DSU(int _n){init(_n);}
    void init(int _n){
        n=_n;
        p.assign(n,0);
        iota(p.begin(),p.end(),0);
    }
    int find(int u){
        return p[u]=p[u]==u?u:find(p[u]);
    }
    bool merge(int u,int v){
        u=find(u),v=find(v);
        if(u==v)return false;
        p[v]=u;
        return true;
    }
    bool same(int u,int v){
        return find(u)==find(v);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int>> edges(m),mst,nonmst;
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    sort(edges.begin(),edges.end());
    DSU dsu(n);
    for(auto e:edges){
        auto [w,u,v]=e;
        if(dsu.merge(u,v)){
            mst.emplace_back(e);
        }else{
            nonmst.emplace_back(e);
        }
    }
    int si=mst.size();
    int sj=nonmst.size();
    vector<int> l(si,0),r(si,sj);
    vector<vector<int>> event(sj);
    while(true){
        bool done=true;
        for(int i=0;i<si;i++){
            if(l[i]==r[i])continue;
            event[(l[i]+r[i])/2].emplace_back(i);
            done=false;
        }
        if(done)break;
        dsu.init(n);
        for(int i=0;i<sj;i++){
            auto [w,u,v]=nonmst[i];
            dsu.merge(u,v);
            for(auto j:event[i]){
                auto [ww,uu,vv]=mst[j];
                if(dsu.same(uu,vv)){
                    r[j]=i;
                }else{
                    l[j]=i+1;
                }
            }
            event[i].clear();
        }
    }
    ll ans=0;
    for(int i=0;i<si;i++){
        if(l[i]==sj){
            cout << -1;
            exit(0);
        }
        ans+=get<0>(nonmst[l[i]])-get<0>(mst[i])+1;
    }
    cout << ans << "\n";
}
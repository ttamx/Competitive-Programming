#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

struct RollbackDSU{
    int n,comp;
    vector<int> p,sz;
    vector<pair<int,int>> s;
    RollbackDSU(){}
    RollbackDSU(int _n){init(_n);}
    void init(int _n){
        n=_n;
        comp=n;
        p.assign(n,0);
        sz.assign(n,1);
        s.clear();
        iota(p.begin(),p.end(),0);
    }
    int find(int u){
        return u==p[u]?u:find(p[u]);
    }
    pair<bool,int> merge(int u,int v){
        u=find(u),v=find(v);
        if(u==v)return {false,(int)s.size()};
        comp--;
        if(sz[u]<sz[v])swap(u,v);
        s.emplace_back(u,v);
        p[v]=u;
        sz[u]+=sz[v];
        return {true,(int)s.size()};
    }
    void rollback(int t){
        while(s.size()>t){
            auto [u,v]=s.back();
            s.pop_back();
            sz[u]-=sz[v];
            p[v]=v;
            comp++;
        }
    }
};

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    map<ll,vector<pair<int,int>>> mp;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        mp[a[u]^a[v]].emplace_back(u,v);
    }
    vector<mint> pw2(n+1);
    pw2[0]=1;
    for(int i=1;i<=n;i++){
        pw2[i]=pw2[i-1]*2;
    }
    mint ans=(mint(1LL<<k)-(int)mp.size())*pw2[n];
    RollbackDSU dsu(n);
    for(auto &[_,edges]:mp){
        for(auto [u,v]:edges){
            dsu.merge(u,v);
        }
        ans+=pw2[dsu.comp];
        dsu.rollback(0);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
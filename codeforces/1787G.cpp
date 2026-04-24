#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid/add.hpp"
#include "group/monoid/max.hpp"

struct MonoidAction{
    using InfoMonoid = MaxMonoid<pair<int,ll>>;
    using TagMonoid = AddMonoid<int>;
    using Info = typename InfoMonoid::value_type;
    using Tag = typename TagMonoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return mp(a.first+b,a.second);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<ll> a(n);
    vector<set<int>> s(n);
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v,w,c;
        cin >> u >> v >> w >> c;
        u--,v--,c--;
        a[c]+=w;
        adj[u].eb(v,c);
        adj[v].eb(u,c);
        if(!s[c].emplace(u).second)s[c].erase(u);
        if(!s[c].emplace(v).second)s[c].erase(v);
    }
    vector<int> id(n,-1),par(n,-1),up(n,-1),l(n),r(n);
    queue<int> qu;
    qu.emplace(0);
    for(int i=0;i<n;i++){
        int u=qu.front();
        qu.pop();
        if(u){
            if(id[up[u]]==-1)id[up[u]]=i;
            int p=par[u];
            if(!l[p])l[p]=i;
            r[p]=i;
        }
        for(auto [v,c]:adj[u])if(v!=par[u]){
            par[v]=u;
            up[v]=c;
            qu.emplace(v);
        }
    }
    vector<ll> b(n);
    for(int i=0;i<n;i++)if(s[i].size()==2){
        b[id[i]]=a[i];
    }
    LazySegmentTree<MonoidAction> seg(n,[&](int i){return mp(0,b[i]);});
    while(q--){
        int o,x;
        cin >> o >> x;
        x--;
        o=o*2-1;
        if(up[x]!=-1){
            int p=id[up[x]];
            seg.update(p,p,o);
        }
        if(l[x])seg.update(l[x],r[x],o);
        cout << seg.query(0,n-1).second << "\n";
    }
}
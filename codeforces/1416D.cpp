#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/max.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m,q;
    cin >> n >> m >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<pair<int,int>> e(m);
    for(auto &[u,v]:e){
        cin >> u >> v;
        u--,v--;
    }
    vector<pair<int,int>> qr(q);
    vector<bool> used(m);
    for(auto &[op,x]:qr){
        cin >> op >> x;
        x--;
        if(op==2)used[x]=true;
    }
    DSU dsu(2*n);
    vector<int> l(2*n,-1),r(2*n,-1),p(2*n,-1);
    int k=n;
    auto merge=[&](int i){
        auto [u,v]=e[i];
        u=dsu.find(u),v=dsu.find(v);
        if(u==v)return;
        l[k]=u;
        r[k]=v;
        dsu.p[u]=k;
        dsu.p[v]=k;
        k++;
    };
    for(int i=0;i<m;i++)if(!used[i])merge(i);
    for(int i=q-1;i>=0;i--){
        auto &[op,x]=qr[i];
        if(op==1){
            x=dsu.find(x);
        }else{
            merge(x);
        }
    }
    for(int i=0;i<k;i++){
        if(l[i]!=-1)p[l[i]]=i;
        if(r[i]!=-1)p[r[i]]=i;
    }
    vector<int> tin(k),tout(k);
    int timer=-1;
    function<void(int)> dfs=[&](int u){
        if(u==-1)return;
        tin[u]=++timer;
        dfs(l[u]);
        dfs(r[u]);
        tout[u]=timer;
    };
    for(int i=0;i<k;i++)if(p[i]==-1)dfs(i);
    SegmentTree<MaxMonoid<int>> s(k,0);
    for(int i=0;i<n;i++){
        s.modify(tin[i],a[i]);
    }
    for(auto [op,x]:qr){
        if(op==1){
            int v=s.query(tin[x],tout[x]);
            int i=s.findfirst(tin[x],tout[x],[&](int val){return val>=v;});
            s.modify(i,0);
            cout << v << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
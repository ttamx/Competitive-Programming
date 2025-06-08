#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"
#include "data-structure/link-cut-tree/link-cut-tree.hpp"
#include "group/monoid/min.hpp"
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;
    vector<tuple<int,int,int>> edges(m);
    for(auto &[w,u,v]:edges)cin >> u >> v >> w;
    sort(edges.begin(),edges.end());
    vector<vector<pair<int,int>>> qr(m);
    vector<int> ans(q);
    for(int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        l=lower_bound(edges.begin(),edges.end(),make_tuple(l,0,0))-edges.begin();
        r=lower_bound(edges.begin(),edges.end(),make_tuple(r+1,0,0))-edges.begin()-1;
        if(l<=r)qr[r].emplace_back(l,i);
        else ans[i]=n;
    }
    using LCT = LinkCutTree<MinMonoid<int>>;
    using Node = typename LCT::Node;
    using Ptr = typename LCT::Ptr;
    LCT lct;
    vector<Ptr> ptr(n+m);
    for(int i=0;i<n;i++)ptr[i]=new Node(m);
    Fenwick<int> f(m);
    for(int i=0;i<m;i++){
        auto [w,u,v]=edges[i];
        if(u!=v){
            ptr[i+n]=new Node(i);
            if(lct.get_root(ptr[u])==lct.get_root(ptr[v])){
                int j=lct.fold(ptr[u],ptr[v]);
                assert(j<m);
                auto [ww,uu,vv]=edges[j];
                lct.cut(ptr[j+n],ptr[uu]);
                lct.cut(ptr[j+n],ptr[vv]);
                f.update(j,-1);
            }
            lct.link(ptr[i+n],ptr[u]);
            lct.link(ptr[i+n],ptr[v]);
            f.update(i,+1);
        }
        for(auto [l,j]:qr[i]){
            ans[j]=n-f.query(l,i);
        }
    }
    for(auto x:ans)cout << x << "\n";
}
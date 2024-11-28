#include "template.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"
#include "tree/static-top-tree-dp.hpp"

vector<int> a;

ll sq(ll x){
    return x*x;
}

struct TreeDP{
    struct Path{
        ll head,tail,ans;
        bool cut;
        ll calc(){
            return ans+sq(head)+sq(tail);
        }
    };
    struct Point{
        ll head,head2,ans;
    };
    static Path compress(const Path &l,const Path &r){
        if(l.cut&&r.cut){
            return {l.head,r.tail,l.ans+r.ans+sq(l.tail+r.head),true};
        }
        if(l.cut){
            return {l.head,l.tail+r.head,l.ans+r.ans,true};
        }
        if(r.cut){
            return {l.head+r.head,r.tail,l.ans+r.ans,true};
        }
        return {l.head+r.head,0,l.ans+r.ans,false};
    }
    static Point rake(const Point &l,const Point &r){
        return {l.head+r.head,l.head2+r.head2,l.ans+r.ans};
    }
    static Point add_edge(const Path &p){
        return {p.head,sq(p.head),p.ans+sq(p.tail)};
    }
    static Path add_vertex(const Point &p,int u){
        if(a[u]){
            return {0,0,p.ans+p.head2,true};
        }else{
            return {p.head+1,0,p.ans,false};
        }
    }
    static Path vertex(int u){
        if(a[u]){
            return {0,0,0,true};
        }else{
            return {1,0,0,false};
        }
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<int> c(n);
    vector<vector<int>> start(n);
    vector<vector<pair<int,int>>> event(n);
    for(int i=0;i<n;i++){
        cin >> c[i];
        c[i]--;
        start[c[i]].emplace_back(i);
    }
    auto g=read_tree(n);
    HLD hld(g);
    for(int i=1;i<=q;i++){
        int u,x;
        cin >> u >> x;
        u--,x--;
        if(c[u]==x)continue;
        event[c[u]].emplace_back(u,i);
        event[x].emplace_back(u,i);
        c[u]=x;
    }
    vector<ll> ans(q+1);
    a.resize(n);
    StaticTopTreeDP<decltype(hld),TreeDP> dp(hld);
    for(int i=0;i<n;i++){
        for(auto u:start[i]){
            a[u]^=1;
            dp.update(u);
        }
        ll val=dp.query_all().calc();
        ans[0]+=val;
        for(auto [u,j]:event[i]){
            ans[j]-=val;
            a[u]^=1;
            dp.update(u);
            val=dp.query_all().calc();
            ans[j]+=val;
        }
        for(auto [u,j]:event[i]){
            a[u]^=1;
            dp.update(u);
        }
        for(auto u:start[i]){
            a[u]^=1;
            dp.update(u);
        }
    }
    for(int i=1;i<=q;i++){
        ans[i]+=ans[i-1];
    }
    ll base=1LL*n*n*n;
    for(auto x:ans){
        cout << base-x << "\n";
    }
}
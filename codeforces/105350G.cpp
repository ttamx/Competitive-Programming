#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/max-add.hpp"
#include "group/monoid-action/max-idx-add.hpp"

const int N=3e5+5;

int n,q;
vector<int> adj[N];
int tin[N],tout[N];
int timer=-1;
ll a[N];
int par[N];
int pos[N],l[N],r[N],rev[N];
int cur=0;

void dfs(int u,int p=-1){
    par[u]=p;
    tin[u]=++timer;
    vector<int> ch;
    for(auto v:adj[u])if(v!=p){
        ch.emplace_back(v);
        dfs(v,u);
    }
    if(!ch.empty()){
        l[u]=cur;
        for(auto v:ch){
            rev[cur]=v;
            pos[v]=cur;
            cur++;
        }
        r[u]=cur-1;
    }else{
        l[u]=r[u]=-1;
    }
    tout[u]=timer;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0);
    Fenwick<ll> f(n);
    LazySegmentTree<MaxAddAction<ll>> seg(n,0LL);
    LazySegmentTree<MaxAddIdxAction<ll>> seg2(n,[&](int i){return pair<ll,int>(0LL,i);});
    for(int i=0;i<n;i++){
        if(l[i]==-1){
            seg.modify(tin[i],-LINF);
        }
    }
    auto get_val=[&](int x){
        ll val=f.query(tin[x]);
        if(par[x]!=-1){
            val+=a[par[x]];
        }
        return val;
    };
    while(q--){
        int op,x;
        cin >> op >> x;
        x--;
        if(op==1){
            ll v;
            cin >> v;
            f.update(tin[x],tout[x],v);
            seg.update(tin[x],tout[x],v);
            int p=par[x];
            if(p!=-1){
                seg2.update(pos[x],pos[x],v);
                auto [val,idx]=seg2.query(l[p],r[p]);
                seg.modify(tin[p],get_val(rev[idx]));
            }
        }else if(op==2){
            ll v;
            cin >> v;
            a[x]+=v;
            seg.update(tin[x],tin[x],v);
        }else if(op==3){
            cout << max(get_val(x),seg.query(tin[x],tout[x])) << "\n";
        }else if(op==4){
            cout << seg.query(tin[x],tin[x]) << "\n";
        }else{
            assert(false);
        }
    }
}
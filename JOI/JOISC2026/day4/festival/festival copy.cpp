#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

const int N=300005;
const ll INF=2e15;

int n,q;
int d[N],c[N];
vector<int> adj[N];

struct StaticTopTree{
    using P = pair<int,int>;
    enum Type{Compress,Rake,AddEdge,AddVertex,Vertex};
    int root,buf;
    int hv[N],fa[N];
    int lch[3*N],rch[3*N],par[3*N];
    Type type[3*N];
    void build(){
        buf=2*n-1;
        dfs(1);
        root=compress(1).second;
    }
    int dfs(int u){
        int s=1,mx=0;
        for(auto v:adj[u])if(v!=fa[u]){
            fa[v]=u;
            int t=dfs(v);
            s+=t;
            if(t>mx){
                mx=t;
                hv[u]=v;
            }
        }
        return s;
    }
    int add(int i,int l,int r,Type t){
        if(!i)i=++buf;
        lch[i]=l,rch[i]=r,type[i]=t;
        if(l)par[l]=i;
        if(r)par[r]=i;
        return i;
    }
    P compress(int i){
        vector<P> a{add_vertex(i)};
        auto work=[&](){
            auto [sj,j]=a.back();
            a.pop_back();
            auto [si,i]=a.back();
            a.back()={max(si,sj)+1,add(0,i,j,Compress)};
        };
        while(hv[i]){
            a.emplace_back(add_vertex(i=hv[i]));
            while(true){
                if(a.size()>=3&&(a.end()[-3].first==a.end()[-2].first||a.end()[-3].first<=a.back().first)){
                    P tmp=a.back();
                    a.pop_back();
                    work();
                    a.emplace_back(tmp);
                }else if(a.size()>=2&&a.end()[-2].first<=a.back().first){
                    work();
                }else break;
            }
        }
        while(a.size()>=2)work();
        return a[0];
    }
    P rake(int i){
        priority_queue<P,vector<P>,greater<P>> pq;
        for(int j:adj[i])if(j!=fa[i]&&j!=hv[i])pq.emplace(add_edge(j));
        while(pq.size()>=2){
            auto [si,i]=pq.top();pq.pop();
            auto [sj,j]=pq.top();pq.pop();
            pq.emplace(max(si,sj)+1,add(0,i,j,Rake));
        }
        return pq.empty()?make_pair(0,0):pq.top();
    }
    P add_edge(int i){
        auto [sj,j]=compress(i);
        return {sj+1,add(0,j,0,AddEdge)};
    }
    P add_vertex(int i){
        auto [sj,j]=rake(i);
        return {sj+1,add(i,j,0,j?AddVertex:Vertex)};
    }
}stt;


namespace Segtree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        int val;
        Ptr l,r;
        Node():val(0),l(),r(){}
    };
    void update(ll l,ll r,Ptr &t,ll x,int v){
        if(!t)t=new Node();
        t->val+=v;
        if(l==r)return;
        ll m=(l+r)/2;
        if(x<=m)update(l,m,t->l,x,v);
        else update(m+1,r,t->r,x,v);
    }
    void update(Ptr &t,ll x,int v){
        update(0,INF,t,x,v);
    }
    ll query(ll l,ll r,vector<Ptr> t,int k){
        if(l==r)return l;
        ll m=(l+r)/2;
        ll cnt=0;
        for(auto x:t)if(x&&x->l)cnt+=x->l->val;
        if(cnt>=k){
            for(auto &x:t)if(x)x=x->l;
            return query(l,m,t,k);
        }else{
            for(auto &x:t)if(x)x=x->r;
            return query(m+1,r,t,k-cnt);
        }
    }
    ll query(vector<Ptr> t,int k){
        return query(0,INF,t,k);
    }
};

struct Info{
    ll l,r,v;
    Info():l(0),r(INF),v(0){}
    Info(ll l,ll r,ll v):l(l),r(r),v(v){};
    friend Info operator+(Info a,Info b){
        b.l=clamp(b.l+a.v,a.l,a.r);
        b.r=clamp(b.r+a.v,a.l,a.r);
        b.v+=a.v;
        return b;
    }
}dp[3*N],rdp[3*N];

Segtree::Ptr root[3*N];

ll query(int u,int k){
    if(k<1)return 0;
    if(!root[u]||k>root[u]->val)return INF;
    return Segtree::query({root[u]},k);
}

void pull_vertex(int u){
    assert(stt.type[u]==stt.Vertex||stt.type[u]==stt.AddVertex);
    int x=stt.lch[u];
    dp[u]=rdp[u]=Info(query(x,c[u]-1)+d[u],query(x,c[u])+d[u],d[u]);
}

void pull_compress(int u){
    assert(stt.type[u]==stt.Compress);
    dp[u]=dp[stt.lch[u]]+dp[stt.rch[u]];
    rdp[u]=rdp[stt.lch[u]]+rdp[stt.rch[u]];
}

void insert(int u){
    while(true){
        pull_vertex(u);
        while((u=stt.par[u])&&stt.type[u]==stt.Compress)pull_compress(u);
        if(!u)break;
        assert(stt.type[u]==stt.AddEdge);
        int x=stt.lch[u];
        ll val=dp[x].r;
        for(;stt.type[u]!=stt.AddVertex;u=stt.par[u]){
            Segtree::update(root[u],val,+1);
        }
    }
}

void erase(int u){
    while(true){
        while((u=stt.par[u])&&stt.type[u]==stt.Compress);
        if(!u)break;
        assert(stt.type[u]==stt.AddEdge);
        int x=stt.lch[u];
        ll val=dp[x].r;
        for(;stt.type[u]!=stt.AddVertex;u=stt.par[u]){
            Segtree::update(root[u],val,-1);
        }
    }
}

Info rec(int u){
    int p=stt.par[u];
    Info below=Info(),above=Info();
    while(p&&stt.type[p]==stt.Compress){
        int l=stt.lch[p],r=stt.rch[p];
        if(l==u)below=below+dp[r];
        else above=above+dp[l];
        u=p;
        p=stt.par[u];
    }
    if(p){
        u=p;
        p=stt.par[u];
        vector<Segtree::Ptr> t;
        Point sum=Point::unit();
        while(stt.type[p]==stt.Rake){
            int l=stt.lch[p],r=stt.rch[p];
            sum=TreeDP::rake(sum,u==r?point[l]:point[r]);
            u=p;
            p=stt.par[u];
        }
        sum=TreeDP::rake(sum,rec(rec,p));
        above=TreeDP::compress(above,TreeDP::add_vertex(sum,p));
    }
    return TreeDP::rake(TreeDP::add_edge(below),TreeDP::add_edge(above));
}

ll reroot(){
    Point res=rec(rec,u);
    if(stt.type[u]==stt.AddVertex){
        res=TreeDP::rake(res,point[stt.lch[u]]);
    }
    return TreeDP::add_vertex(res,u);
}

vector<ll> dfs(int u){
    if(!u)return {};
    auto vl=dfs(stt.lch[u]);
    auto vr=dfs(stt.rch[u]);
    if(stt.type[u]==stt.Vertex||stt.type[u]==stt.AddVertex){
        pull_vertex(u);
    }else if(stt.type[u]==stt.Compress){
        pull_compress(u);
    }else if(stt.type[u]==stt.AddEdge){
        ll x=dp[stt.lch[u]].r;
        Segtree::update(root[u],x,+1);
        return {x};
    }else{
        vector<ll> res;
        for(auto x:vl){
            Segtree::update(root[u],x,+1);
            res.emplace_back(x);
        }
        for(auto x:vr){
            Segtree::update(root[u],x,+1);
            res.emplace_back(x);
        }
        return res;
    }
    return {};
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v >> d[i+n];
        adj[u].emplace_back(i+n);
        adj[v].emplace_back(i+n);
        adj[i+n].emplace_back(u);
        adj[i+n].emplace_back(v);
        c[i+n]=1;
    }
    for(int i=1;i<=n;i++)cin >> c[i];
    stt.build();
    dfs(stt.root);
    cin >> q;
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int u,x;
            cin >> u >> x;
            erase(u);
            c[u]=x;
            insert(u);
        }else if(op==2){
            int u,x;
            cin >> u >> x;
            u+=n;
            erase(u);
            d[u]=x;
            insert(u);
        }else{
            int u;
            cin >> u;
            ll ans=dp[stt.root].r;
            cout << (ans<INF?ans:-1LL) << "\n";
        }
    }
}
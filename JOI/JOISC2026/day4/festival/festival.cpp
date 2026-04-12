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

struct Info{
    ll l,r,v;
    Info():l(0),r(INF),v(0){}
    Info(ll l,ll r,ll v):l(l),r(r),v(v){};
    friend Info operator+(Info a,Info b){
        b.l=min(max(b.l+a.v,a.l),a.r);
        b.r=min(max(b.r+a.v,a.l),a.r);
        b.v+=a.v;
        return b;
    }
}dp[3*N],rdp[3*N];

ordered_set<pair<ll,int>> ds[4*N];
int buf=6*n;

ll query(int u,int k){
    k--;
    if(k<0)return 0;
    if(k>=ds[u].size())return INF;
    return ds[u].find_by_order(k)->first;
}

void pull_vertex(int u){
    assert(stt.type[u]==stt.Vertex||stt.type[u]==stt.AddVertex);
    int x=stt.lch[u];
    dp[u]=rdp[u]=Info(query(x,c[u]-1)+d[u],query(x,c[u])+d[u],d[u]);
}

void pull_compress(int u){
    assert(stt.type[u]==stt.Compress);
    dp[u]=dp[stt.lch[u]]+dp[stt.rch[u]];
    rdp[u]=rdp[stt.rch[u]]+rdp[stt.lch[u]];
}

void insert(int u){
    while(true){
        pull_vertex(u);
        while((u=stt.par[u])&&stt.type[u]==stt.Compress)pull_compress(u);
        if(!u)break;
        assert(stt.type[u]==stt.AddEdge);
        int x=stt.lch[u];
        pair<ll,int> val(dp[x].r,x);
        for(;stt.type[u]!=stt.AddVertex;u=stt.par[u]){
            ds[u].insert(val);
        }
    }
}

void erase(int u){
    while(true){
        while((u=stt.par[u])&&stt.type[u]==stt.Compress);
        if(!u)break;
        assert(stt.type[u]==stt.AddEdge);
        int x=stt.lch[u];
        pair<ll,int> val(dp[x].r,x);
        for(;stt.type[u]!=stt.AddVertex;u=stt.par[u]){
            auto it=ds[u].find(val);
            assert(it!=ds[u].end());
            ds[u].erase(it);
        }
    }
}

ll query_many(vector<int> a,int k){
    ll l=0,r=INF;
    while(l<r){
        ll m=(l+r)/2;
        int cnt=0;
        for(auto x:a){
            cnt+=ds[x].order_of_key({m,INT_MAX});
        }
        if(cnt>=k)r=m;
        else l=m+1;
    }
    return l;
}

int rec(int u){
    int p=stt.par[u];
    Info below=Info(),above=Info();
    while(p&&stt.type[p]==stt.Compress){
        int l=stt.lch[p],r=stt.rch[p];
        if(l==u)below=below+dp[r];
        else above=above+rdp[l];
        u=p;
        p=stt.par[u];
    }
    if(p){
        u=p;
        p=stt.par[u];
        vector<int> a;
        while(stt.type[p]==stt.Rake){
            int l=stt.lch[p],r=stt.rch[p];
            a.emplace_back(u==r?l:r);
            u=p;
            p=stt.par[u];
        }
        a.emplace_back(rec(p));
        Info tmp(query_many(a,c[p]-1)+d[p],query_many(a,c[p])+d[p],d[p]);
        above=above+tmp;
    }
    buf++;
    ds[buf].clear();
    ds[buf].insert({below.r,-1});
    ds[buf].insert({above.r,-2});
    return buf;
}

ll reroot(int u){
    buf=6*n;
    vector<int> a{rec(u)};
    if(stt.type[u]==stt.AddVertex)a.emplace_back(stt.lch[u]);
    return query_many(a,c[u])+d[u];
}


void dfs(int u){
    if(!u)return;
    dfs(stt.lch[u]);
    dfs(stt.rch[u]);
    if(stt.type[u]==stt.Vertex||stt.type[u]==stt.AddVertex){
        pull_vertex(u);
    }else if(stt.type[u]==stt.Compress){
        pull_compress(u);
    }else if(stt.type[u]==stt.AddEdge){
        int x=stt.lch[u];
        ds[u].insert({dp[x].r,x});
    }else{
        for(auto e:ds[stt.lch[u]])ds[u].insert(e);
        for(auto e:ds[stt.rch[u]])ds[u].insert(e);
    }
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
            ll ans=reroot(u);
            cout << (ans<INF?ans:-1LL) << "\n";
        }
    }
}
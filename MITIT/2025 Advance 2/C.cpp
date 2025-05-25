#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;

using ll = long long;

const int N=2e5+5;
const int K=1<<19;
const ll INF=1e18;

int n;
vector<pair<int,int>> adj[N];
vector<int> node[N];
int dep[N],sz[N],hd[N],hv[N],tin[N],pos[N],par[N];
ll dist[N];
ll dp[N];
int timer=0;

struct SecondMin{
    pair<ll,int> mn,mn2;
    SecondMin():mn(INF,-1),mn2(INF,-2){}
    SecondMin(ll val,int idx):mn(val,idx),mn2(INF,-1){}
    void update(const pair<ll,int> &val){
        if(mn.second==val.second)mn=min(mn,val);
        else mn2=min(mn2,val);
        if(mn2<mn)swap(mn,mn2);
    }
    friend SecondMin operator+(const SecondMin &l,const SecondMin &r){
        SecondMin res=l;
        res.update(r.mn);
        res.update(r.mn2);
        return res;
    }
    SecondMin add(ll val)const{
        SecondMin res=*this;
        res.mn.first+=val;
        res.mn2.first+=val;
        return res;
    }
};

struct Info{
    SecondMin val;
    ll base;
    Info():val(),base(INF){}
    Info(ll _base):val(),base(_base){}
    Info(const SecondMin &_val,ll _base):val(_val),base(_base){}
    friend Info operator+(const Info &l,const Info &r){
        return Info(l.val+r.val,min(l.base,r.base));
    }
};

struct Tag{
    SecondMin val;
    bool reset;
    Tag():val(),reset(false){}
    Tag(const SecondMin &_val,bool _reset):val(_val),reset(_reset){}
    void apply(const Tag &o){
        if(o.reset){
            val=o.val;
            reset=true;
        }else{
            val=val+o.val;
        }
    }
};

struct Segtree{
    Info t[K],def[K];
    Tag lz[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=def[i]=Info(-2*dist[pos[l]]));
        int m=(l+r)/2;
        build(l,m,i<<1);
        build(m+1,r,i<<1|1);
        t[i]=t[i<<1]+t[i<<1|1];
        def[i]=def[i<<1]+def[i<<1|1];
    }
    void build(){
        build(1,n,1);
    }
    void apply(int i,const Tag &v){
        if(v.reset)t[i]=def[i];
        t[i].val=t[i].val+v.val.add(t[i].base);
        lz[i].apply(v);
    }
    void push(int i){
        apply(i<<1,lz[i]);
        apply(i<<1|1,lz[i]);
        lz[i]=Tag();
    }
    // void modify(int l,int r,int i,int x,ll v){
    //     if(l==r)return void(t[i]=Info(v,INF));
    //     push(i);
    //     int m=(l+r)/2;
    //     if(x<=m)modify(l,m,i<<1,x,v);
    //     else modify(l+1,r,i<<1|1,x,v);
    //     t[i]=t[i<<1]+t[i<<1|1];
    // }
    // void modify(int x,int v){
    //     modify(1,n,1,x,v);
    // }
    void update(int l,int r,int i,int x,int y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i<<1,x,y,v);
        update(m+1,r,i<<1|1,x,y,v);
        t[i]=t[i<<1]+t[i<<1|1];
    }
    void update(int x,int y,const Tag &v){
        return update(1,n,1,x,y,v);
    }
    Info query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Info();
        if(x<=l&&r<=y)return t[i];
        push(i);
        int m=(l+r)/2;
        return query(l,m,i<<1,x,y)+query(m+1,r,i<<1|1,x,y);
    }
    Info query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

void dfs(int u){
    sz[u]=1;
    node[dep[u]].emplace_back(u);
    for(auto [v,w]:adj[u]){
        if(v!=par[u]){
            dep[v]=dep[u]+1;
            par[v]=u;
            dist[v]=dist[u]+w;
            dfs(v);
            sz[u]+=sz[v];
            if(sz[v]>sz[hv[u]]){
                hv[u]=v;
            }
        }
    }
}

void hld(int u){
    tin[u]=++timer;
    pos[timer]=u;
    if(!hd[u])hd[u]=u;
    if(hv[u]){
        hd[hv[u]]=hd[u];
        hld(hv[u]);
    }
    for(auto [v,w]:adj[u]){
        if(v!=par[u]&&v!=hv[u]){
            hld(v);
        }
    }
}

inline void update(int u){
    Tag tag(SecondMin(dist[u]+dp[u],u),false);
    while(u){
        seg.update(tin[hd[u]],tin[u],tag);
        u=par[hd[u]];
    }
}

inline void reset(int u){
    while(u){
        seg.update(tin[hd[u]],tin[u],Tag(SecondMin(),true));
        u=par[hd[u]];
    }
}

inline SecondMin query(int u){
    SecondMin res;
    while(u){
        res=res+seg.query(tin[hd[u]],tin[u]).val;
        u=par[hd[u]];
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dfs(1);
    hld(1);
    seg.build();
    ll ans=INF;
    for(auto u:node[1]){
        dp[u]=dist[u];
        ans=min(ans,dp[u]);
    }
    for(int d=2;!node[d].empty();d++){
        ans=INF;
        for(auto u:node[d-1]){
            update(u);
        }
        for(auto u:node[d]){
            auto res=query(u);
            dp[u]=dist[u]+(res.mn.second==par[u]?res.mn2:res.mn).first;
            ans=min(ans,dp[u]);
        }
        for(auto u:node[d-1]){
            reset(u);
        }
    }
    cout << ans;
}
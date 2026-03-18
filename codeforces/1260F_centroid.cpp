#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;
const int MOD=1e9+7;

int n,m;
int l[N],r[N];
vector<int> adj[N];
ll e[N];
ll ans=0,ways=1;
int sz[N];
bool used[N];
vector<pair<int,int>> nodes;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

struct Segtree{
    ll t[K],lz[K];
    void apply(int l,int r,int i,ll v){
        t[i]=(t[i]+(r-l+1)*v)%MOD;
        lz[i]=(lz[i]+v)%MOD;
    }
    void push(int l,int m,int r,int i){
        apply(l,m,i*2,lz[i]);
        apply(m+1,r,i*2+1,lz[i]);
        lz[i]=0LL;
    }
    void update(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,i,v);
        int m=(l+r)/2;
        push(l,m,r,i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=(t[i*2]+t[i*2+1])%MOD;
    }
    void update(int x,int y,ll v){
        update(1,m,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0LL;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        push(l,m,r,i);
        return (query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y))%MOD;
    }
    ll query(int x,int y){
        return query(1,m,1,x,y);
    }
}seg_sum,seg_cnt;

int dfs_sz(int u,int p){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfs_sz(v,u);
    return sz[u];
}

int centroid(int u,int p,int tot){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>tot)return centroid(v,u,tot);
    return u;
}

inline void insert(int u,int d){
    seg_cnt.update(l[u],r[u],e[u]);
    seg_sum.update(l[u],r[u],e[u]*d%MOD);
}

inline void update(int u,int d){
    ans=(ans+seg_cnt.query(l[u],r[u])*e[u]%MOD*d)%MOD;
    ans=(ans+seg_sum.query(l[u],r[u])*e[u])%MOD;
}

inline void erase(int u,int d){
    seg_cnt.update(l[u],r[u],MOD-e[u]);
    seg_sum.update(l[u],r[u],MOD-e[u]*d%MOD);
}

void dfs(int u,int p,int d){
    nodes.emplace_back(u,d);
    for(auto v:adj[u])if(v!=p&&!used[v])dfs(v,u,d+1);
}

void decom(int u){
    u=centroid(u,-1,dfs_sz(u,-1));
    vector<pair<int,int>> all;
    all.emplace_back(u,0);
    insert(u,0);
    for(auto v:adj[u])if(!used[v]){
        dfs(v,u,1);
        for(auto [x,d]:nodes)update(x,d);
        for(auto [x,d]:nodes)insert(x,d);
        all.insert(all.end(),nodes.begin(),nodes.end());
        nodes.clear();
    }
    for(auto [x,d]:all)erase(x,d);
    used[u]=true;
    for(auto v:adj[u])if(!used[v])decom(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> l[i] >> r[i];
        ll s=r[i]-l[i]+1;
        e[i]=binpow(s,MOD-2);
        ways=ways*s%MOD;
        m=max(m,r[i]);
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    decom(1);
    cout << ans*ways%MOD << "\n";
}
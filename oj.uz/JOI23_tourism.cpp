#include<bits/stdc++.h>
#include<queue>

using namespace std;

const int N=1e5+5;
const int M=3e5+5;
const int LG=20;

int n,m,q;
int c[N];
vector<int> adj[N];
int sz[N],hv[N],hd[N],pa[N],lv[N],tin[N],tout[N],pos[M];
int timer;
vector<pair<int,int>> qr[N],chain[N];
int ans[N];

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i;i-=i&-i)res+=t[i];
        return res;
    }
}f;

template<class T,class cmp>
struct RMQ{
    T t[LG][M];
    T get_min(T a,T b){
        return cmp()(a,b)?a:b;
    }
    void build(){
        for(int i=0;i<LG-1;i++){
            for(int j=1;j+(2<<i)-1<M;j++){
                t[i+1][j]=get_min(t[i][j],t[i][j+(1<<i)]);
            }
        }
    }
    T query(int l,int r){
        int k=31-__builtin_clz(r-l+1);
        return get_min(t[k][l],t[k][r-(1<<k)+1]);
    }
};

RMQ<int,less<int>> rtin,rdep;
RMQ<int,greater<int>> rtout;

void dfs(int u,int p=0){
    tin[u]=++timer;
    pos[timer]=u;
    pa[u]=p;
    sz[u]=1;
    for(auto v:adj[u])if(v!=p){
        lv[v]=lv[u]+1;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
        pos[++timer]=u;
    }
    tout[u]=timer;
}

void hld(int u,int p=0){
    if(!hd[u])hd[u]=u;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u],u);
    for(auto v:adj[u])if(v!=p&&v!=hv[u])hld(v,u);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=m;i++)cin >> c[i];
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[r].emplace_back(l,i);
    }
    dfs(1);
    hld(1);
    for(int i=1;i<=timer;i++)rdep.t[0][i]=lv[pos[i]];
    for(int i=1;i<=m;i++){
        rtin.t[0][i]=tin[c[i]];
        rtout.t[0][i]=tout[c[i]];
    }
    rdep.build();
    rtin.build();
    rtout.build();
    for(int r=1;r<=m;r++){
        for(int u=c[r];u;u=pa[hd[u]]){
            int h=hd[u];
            auto &ch=chain[h];
            while(!ch.empty()&&lv[ch.back().first]<=lv[u]){
                auto [v,i]=ch.back();
                ch.pop_back();
                int val=lv[v]-lv[h]+1;
                f.update(i,-val);
                if(!ch.empty())f.update(ch.back().second,val);
            }
            int val=lv[u]-lv[h]+1;
            if(!ch.empty())f.update(ch.back().second,-val);
            ch.emplace_back(u,r);
            f.update(r,lv[u]-lv[h]+1);
        }
        for(auto [l,i]:qr[r]){
            int u=rtin.query(l,r),v=rtout.query(l,r);
            ans[i]=f.query(r)-f.query(l-1)-rdep.query(u,v);
        }
    }
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}
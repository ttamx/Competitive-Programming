#include<bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N=1e5+5;

int n,q;
vector<int> adj[N];
int a[N],u1[N],v1[N],u2[N],v2[N],k[N];
int l[N],r[N];
vector<int> id[N],vec[N];
int sz[N],lv[N],hv[N],hd[N],tin[N],pa[N];
int timer=0;
ull hsh[N];

void dfs(int u,int p=0){
    sz[u]=1;
    pa[u]=p;
    lv[u]=lv[p]+1;
    for(auto v:adj[u])if(v!=p){
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u,int p=0){
    tin[u]=++timer;
    if(!hd[u])hd[u]=u;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u],u);
    for(auto v:adj[u])if(v!=p&&v!=hv[u])hld(v,u);
}

struct Fenwick{
    ull t[N];
    void update(int i,ull v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    ull query(int i){
        ull res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    ull query(int l,int r){
        return query(r)-query(l-1);
    }
    void clear(){
        for(int i=0;i<N;i++)t[i]=0;
    }
}f;

ull query(int u,int v){
    ull res=0;
    while(hd[u]!=hd[v]){
        if(lv[hd[u]]<lv[hd[v]])swap(u,v);
        res+=f.query(tin[hd[u]],tin[u]);
        u=pa[hd[u]];
    }
    if(lv[u]>lv[v])swap(u,v);
    res+=f.query(tin[u],tin[v]);
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<N;i++)hsh[i]=rng();
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        id[a[i]].emplace_back(i);
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    hld(1);
    cin >> q;
    for(int i=1;i<=q;i++)cin >> u1[i] >> v1[i] >> u2[i] >> v2[i] >> k[i];
    for(int i=1;i<=q;i++)l[i]=1,r[i]=N;
    while(true){
        bool done=true;
        for(int i=1;i<=q;i++)if(l[i]<r[i]){
            vec[(l[i]+r[i])/2].emplace_back(i);
            done=false;
        }
        if(done)break;
        for(int i=1;i<N;i++){
            for(auto j:id[i])f.update(tin[j],hsh[a[j]]);
            for(auto j:vec[i]){
                if(query(u1[j],v1[j])!=query(u2[j],v2[j]))r[j]=i;
                else l[j]=i+1;
            }
            vec[i].clear();
        }
        f.clear();
    }
    for(int i=1;i<=q;i++){
        if(l[i]<N)cout << 1 << " " << l[i] << "\n";
        else cout << 0 << "\n";
    }
}
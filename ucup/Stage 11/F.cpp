#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int LG=20;
const ll INF=1e18;

struct SuffixMin{
    map<int,ll> dat;
    void insert(int i,ll v){
        auto it=dat.lower_bound(i);
        if(it!=dat.end()&&it->second<=v)return;
        it=dat.insert(it,{i,v});
        it->second=v;
        while(it!=dat.begin()&&prev(it)->second>=v)dat.erase(prev(it));
    }
    ll query(int i){
        auto it=dat.lower_bound(i);
        return it==dat.end()?INF:it->second;
    }
}ds[N];

int n;
int l[N],r[N];
vector<int> adj[N];
ll dp[N];
int sz[N],par[N];
bool used[N];
int dep[N];
int dist[LG][N];

int dfs_sz(int u,int p){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfs_sz(v,u);
    return sz[u];
}

int centroid(int u,int p,int cnt){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return centroid(v,u,cnt);
    return u;
}

void fill_dist(int u,int p,int d,int lv){
    dist[lv][u]=d;
    for(auto v:adj[u])if(v!=p&&!used[v])fill_dist(v,u,d+1,lv);
}

void decom(int u,int p,int d){
    u=centroid(u,0,dfs_sz(u,0));
    par[u]=p;
    dep[u]=d;
    used[u]=true;
    fill_dist(u,0,0,d);
    for(auto v:adj[u])if(!used[v])decom(v,u,d+1);
}

void update(int u){
    for(int x=u;x;x=par[x])ds[x].insert(r[u],dp[u]+dist[dep[x]][u]);
}

ll query(int u){
    ll res=INF;
    for(int x=u;x;x=par[x])res=min(res,ds[x].query(l[u])+dist[dep[x]][u]);
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++)cin >> l[i] >> r[i];
    if(r[1]>r[n]){
        for(int i=1;i<=n;i++)tie(l[i],r[i])=make_pair(-r[i],-l[i]);
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int i,int j){return r[i]<r[j];});
    for(int i=1;i<=n;i++)dp[i]=INF;
    dp[1]=0;
    decom(1,0,0);
    for(auto i:ord){
        dp[i]=min(dp[i],query(i)+1);
        update(i);
    }
    cout << query(n) << "\n";
}
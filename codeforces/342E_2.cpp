#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=20;
const int inf=1e9;

int n,m;
vector<int> adj[N];
int sz[N];
bool used[N];
int cp[N],clv[N],dist[K][N];
int mn[N];

int dfssz(int u,int p=-1){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfssz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=-1){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return centroid(v,cnt,u);
    return u;
}

void filldist(int u,int l,int d=0,int p=-1){
    dist[l][u]=d;
    for(auto v:adj[u])if(v!=p&&!used[v])filldist(v,l,d+1,u);
}

void decom(int u,int l=0,int p=-1){
    u=centroid(u,dfssz(u));
    used[u]=true;
    cp[u]=p;
    clv[u]=l;
    filldist(u,l);
    for(auto v:adj[u])if(!used[v])decom(v,l+1,u);
}

void update(int st){
    for(int u=st;u!=-1;u=cp[u]){
        int d=dist[clv[u]][st];
        mn[u]=min(mn[u],d);
    }
}

int query(int st){
    int res=inf;
    for(int u=st;u!=-1;u=cp[u]){
        int d=dist[clv[u]][st];
        res=min(res,d+mn[u]);
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin  >> n >> m;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    decom(1);
    for(int i=1;i<=n;i++)mn[i]=inf;
    update(1);
    while(m--){
        int t,u;
        cin >> t >> u;
        if(t==1)update(u);
        else cout << query(u) << "\n";
    }
}
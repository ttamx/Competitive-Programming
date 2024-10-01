#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int W=1e6+5;

int n,m;
int p[N];
ll w[N];
vector<int> adj[N];
bool vis[N];
ll base;
int pa[N],sz[N];
vector<pair<int,int>> event;
ll cnt[W],qs1[W],qs2[W];
bool alive[N];

int fp(int u){
    return pa[u]=u==pa[u]?u:fp(pa[u]);
}

void uni(int u,int v){
    u=fp(u),v=fp(v);
    if(u==v){
        return;
    }
    pa[v]=u;
    sz[u]+=sz[v];
    if(alive[v]){
        alive[u]=true;
    }
}

int dfs(int u){
    vis[u]=true;
    if(w[u]==0){
        return 1;
    }
    int cnt=0;
    for(auto v:adj[u]){
        cnt+=dfs(v);
    }
    return max(cnt,1);
}

void init(vector<int> _p,vector<int> _w){
    n=_p.size();
    for(int i=0;i<n;i++){
        p[i]=_p[i];
        w[i]=_w[i];
        if(i>0){
            adj[p[i]].emplace_back(i);
        }
    }
    for(int i=0;i<n;i++){
        pa[i]=i;
        sz[i]=1;
        if(adj[i].empty()){
            base+=w[i];
        }else{
            event.emplace_back(w[i],i);
        }
    }
    sort(event.rbegin(),event.rend());
    for(auto [t,u]:event){
        vis[u]=true;
        if(alive[fp(u)]){
            cnt[sz[fp(u)]]-=t;
        }
        sz[fp(u)]--;
        for(auto v:adj[u]){
            if(alive[fp(v)]){
                cnt[sz[fp(v)]]-=t;
            }
            uni(u,v);
        }
        cnt[sz[fp(u)]]+=t;
        alive[fp(u)]=true;
    }
    for(int i=1;i<W;i++){
        qs1[i]=qs1[i-1]+cnt[i];
        qs2[i]=qs2[i-1]+cnt[i]*i;
    }
}

ll query(int L,int R){
    ll ans=base*L;
    int k=R/L;
    ans+=(qs2[W-1]-qs2[k])*L;
    ans-=(qs1[W-1]-qs1[k])*R;
    return ans;
}

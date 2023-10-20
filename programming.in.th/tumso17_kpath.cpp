#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n;
ll k;
vector<pair<int,ll>> adj[N];
set<ll> s;
int sz[N],cp[N];
bool used[N];
ll ans=1e18;

void sol(int u,int p,bool add,ll d){
    if(add){
        s.emplace(d);
    }else{
        auto it=s.lower_bound(k-d);
        if(it!=s.end()){
            ans=min(ans,llabs(*it+d-k));
        }
        if(it!=s.begin()){
            ans=min(ans,llabs(d+*prev(it)-k));
        }
    }
    for(auto [v,w]:adj[u]){
        if(v==p||used[v])continue;
        sol(v,u,add,d+w);
    }
}

int dfs(int u,int p=0){
    sz[u]=1;
    for(auto [v,w]:adj[u]){
        if(v==p||used[v])continue;
        sz[u]+=dfs(v,u);
    }
    return sz[u];
}

int centroid(int u,int req,int p=0){
    for(auto [v,w]:adj[u])if(sz[v]*2>req&&!used[v]&&v!=p)return centroid(v,req,u);
    return u;
}

void decom(int u,int p=0){
    u=centroid(u,dfs(u));
    used[u]=true;
    cp[u]=p;
    s.clear();
    s.emplace(0);
    for(auto [v,w]:adj[u]){
        sol(v,u,0,w);
        sol(v,u,1,w);
    }
    for(auto [v,w]:adj[u])if(!used[v])decom(v,u);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<n;i++){
        int u,v;
        ll w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    decom(1);
    cout << ans;
}
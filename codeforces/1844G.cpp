#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int B=40;

using ll = long long;

int n;
vector<pair<int,int>> adj[N];
ll a[N];
int par[N],jump[N],dep[N],id[N];
int lc[N];
int d[N];
int dist[N];
vector<int> ord;
ll ans[N];

void dfs(int u){
    ord.emplace_back(u);
    for(auto [v,i]:adj[u]){
        if(v==par[u])continue;
        id[v]=i;
        par[v]=u;
        jump[v]=(dep[u]-dep[jump[u]]==dep[jump[u]]-dep[jump[jump[u]]]?jump[jump[u]]:u);
        dep[v]=dep[u]+1;
        dfs(v);
    }
}

int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    while(dep[u]>dep[v])u=dep[jump[u]]>=dep[v]?jump[u]:par[u];
    while(u!=v){
        if(jump[u]==jump[v])u=par[u],v=par[v];
        else u=jump[u],v=jump[v];
    }
    return u;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    for(int i=1;i<=n-1;i++){
        cin >> a[i];
    }
    dep[1]=1;
    dfs(1);
    for(int i=1;i<=n-1;i++){
        lc[i]=lca(i,i+1);
    }
    for(int b=0;b<B;b++){
        for(int i=1;i<=n-1;i++){
            d[i+1]=d[i]^(a[i]&1);
        }
        for(int i=2;i<=n;i++){
            dist[i]=d[i]^d[par[i]];
            ans[id[i]]|=ll(dist[i])<<b;
        }
        for(auto i:ord){
            dist[i]+=dist[par[i]];
        }
        for(int i=1;i<=n-1;i++){
            a[i]-=dist[i]+dist[i+1]-2*dist[lc[i]];
            if(a[i]<0){
                cout << -1 << "\n";
                exit(0);
            }
            assert(a[i]%2==0);
            a[i]/=2;
        }
    }
    for(int i=1;i<=n-1;i++){
        if(ans[i]==0){
            cout << -1 << "\n";
            exit(0);
        }
    }
    for(int i=1;i<=n-1;i++){
        cout << ans[i] << "\n";
    }
}
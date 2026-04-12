#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n,k;
vector<int> adj[N];
int sz[N],dep[N];

void dfs(int u,int p){
    sz[u]=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dep[v]=dep[u]+1;
        dfs(v,u);
        sz[u]+=sz[v];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dep[1]=1;
    dfs(1,0);
    vector<int> a;
    for(int i=1;i<=n;i++){
        a.emplace_back(sz[i]-dep[i]);
    }
    sort(a.rbegin(),a.rend());
    ll ans=0;
    for(int i=0;i<n-k;i++){
        ans+=a[i];
    }
    cout << ans << "\n";
}
#include<bits/stdc++.h>

using namespace std;

const bool DBG=false;
const int N=1e5+5;

int n;
int sz[N],pa[N];
vector<pair<int,int>> adj[N];
vector<tuple<int,int,int>> edge;
long long ans;

int dfs(int u=1,int p=0){
    pa[u]=p;
    sz[u]=1;
    for(auto [v,w]:adj[u])if(v!=p)sz[u]+=dfs(v,u);
    return sz[u];
}

void runcase(){
    ans=0;
    cin >> n;
    edge.resize(n-1);
    for(int i=1;i<=n;i++)adj[i].clear();
    for(auto &[u,v,w]:edge){
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dfs();
    if(DBG)for(int i=1;i<=n;i++)cerr << i << ' ' << sz[i] << '\n';
    for(auto [u,v,w]:edge){
        if(pa[v]==u)swap(u,v);
        ans+=2ll*min(sz[u],n-sz[u])*w;
    }
    cout << ans << '\n';
    if(DBG)cerr << "--------------\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    for(int T=1;t--;T++){
        cout << "Case #" << T << ": ";
        runcase();
    }
}
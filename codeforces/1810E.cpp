#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> p(n+1),sz(n+1);
    for(int i=1;i<=n;i++)p[i]=i,sz[i]=1;
    function<int(int)> fp=[&](int u){
        if(u==p[u])return u;
        return p[u]=fp(p[u]);
    };
    vector<bool> ok(n+1),vis(n+1);
    auto uni=[&](int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return;
        p[u]=v;
        sz[v]+=sz[u];
        sz[u]=0;
    };
    vector<int> vec(n+1);
    for(int i=1;i<=n;i++)vec[i]=i;
    sort(vec.begin()+1,vec.end(),[&](int x,int y){
        return a[x]<a[y];
    });
    for(int i=1;i<=n;i++){
        int u=vec[i];
        vis[u]=true;
        if(a[u]==0){
            ok[u]=true;
            for(auto v:adj[u])if(vis[v])uni(v,u);
            continue;
        }
        for(auto v:adj[u]){
            if(!vis[v])continue;
            if(ok[fp(v)]&&sz[fp(v)]>=a[u]){
                ok[u]=true;
                break;
            }
        }
        for(auto v:adj[u])if(vis[v])uni(v,u);
    }
    for(int i=1;i<=n;i++)if(fp(i)!=fp(1)||!ok[fp(i)])return void(cout << "NO\n");
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
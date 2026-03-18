#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n;
int a[N];
vector<int> adj[N];
int tin[N],tout[N],par[N];
int timer=0;
vector<int> col[N];

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}fw;

void dfs(int u){
    tin[u]=++timer;
    for(auto v:adj[u])if(v!=par[u]){
        par[v]=u;
        dfs(v);
    }
    tout[u]=timer;
    col[a[u]].emplace_back(u);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    for(int i=1;i<=n;i++){
        fw.update(i,1);
    }
    for(int c=1;c<=n;c++){
        ll ans=1LL*n*(n+1)/2;
        vector<pair<int,int>> upd;
        for(auto u:col[c]){
            int tot=1;
            for(auto v:adj[u])if(v!=par[u]){
                int sz=fw.query(tout[v])-fw.query(tin[v]-1);
                ans-=1LL*sz*(sz+1)/2;
                tot+=sz;
            }
            fw.update(tin[u],-tot);
            upd.emplace_back(tin[u],tot);
        }
        int sz=fw.query(n);
        ans-=1LL*sz*(sz+1)/2;
        for(auto [i,v]:upd){
            fw.update(i,v);
        }
        cout << ans << "\n";
    }
}
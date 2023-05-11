#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
vector<pair<int,int>> adj[N];
int lv[N],pa[N][20],mx[N][20],mn[N][20];

void dfs(int u,int p){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(int i=1;i<20;i++)mx[u][i]=max(mx[u][i-1],mx[pa[u][i-1]][i-1]);
    for(int i=1;i<20;i++)mn[u][i]=min(mn[u][i-1],mn[pa[u][i-1]][i-1]);
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        mx[v][0]=mn[v][0]=w;
        dfs(v,u);
    }
}

pair<int,int> lca(int u,int v){
    if(lv[u]<lv[v])swap(u,v);
    int res1=0,res2=2e9;
    for(int i=19;i>=0;i--)if(lv[pa[u][i]]>=lv[v]){
        res1=max(res1,mx[u][i]);
        res2=min(res2,mn[u][i]);
        u=pa[u][i];
    }
    if(u==v)return {res1,res2};
    for(int i=19;i>=0;i--)if(pa[u][i]!=pa[v][i]){
        res1=max({res1,mx[u][i],mx[v][i]});
        res2=min({res2,mn[u][i],mn[v][i]});
        u=pa[u][i],v=pa[v][i];
    }
    res1=max({res1,mx[u][0],mx[v][0]});
    res2=min({res2,mn[u][0],mn[v][0]});
    return {res1,res2};
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    for(int i=0;i<20;i++)mn[0][i]=2e9;
    dfs(1,0);
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        auto [x,y]=lca(u,v);
        cout << y << " " << x << "\n";
    }
}
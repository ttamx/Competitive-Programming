#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m,st,ed;
int pa[N][20],lv[N],dist[N],mx[N];
bool vis[N];
vector<int> path,path2;
vector<pair<int,int>> adj[N];

void dfs(int u,int p=0){
    pa[u][0]=p;
    lv[u]=lv[p]+1;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        dist[v]=dist[u]+w;
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
    if(a==b)return a;
    for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
    return pa[a][0];
}

int calc(int u,int v){
    return dist[u]+dist[v]-2*dist[lca(u,v)];
}

int dfsmx(int u){
    vis[u]=true;
    int res=0;
    for(auto [v,w]:adj[u])if(!vis[v])res=max(res,w+dfsmx(v));
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> st >> ed;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dfs(1,0);
    int anc=lca(st,ed);
    for(int u=st;u!=pa[anc][0];u=pa[u][0]){
        path.emplace_back(u);
        vis[u]=true;
    }
    for(int u=ed;u!=anc;u=pa[u][0]){
        path2.emplace_back(u);
        vis[u]=true;
    }
    reverse(path2.begin(),path2.end());
    for(auto x:path2)path.emplace_back(x);
    for(auto u:path){
        vis[u]=false;
        mx[u]=dfsmx(u);
    }
    for(int i=1;i<path.size();i++){
        int d=abs(dist[path[i]]-dist[path[i-1]]);
        mx[i]=max(mx[path[i]],mx[path[i-1]]-d);
    }
    for(int i=path.size()-2;i>=0;i--){
        int d=abs(dist[path[i]]-dist[path[i+1]]);
        mx[i]=max(mx[path[i]],mx[path[i+1]]-d);
    }
    while(m--){
        int u,v;
        cin >> u >> v;
        cout << calc(u,v)+mx[u]+mx[v] << '\n';
    }
}
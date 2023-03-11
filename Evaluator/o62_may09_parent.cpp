#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m;
int pa[N];
int lv[N],dp[N][20];
vector<int> adj[N];
vector<tuple<int,int,int>> in;

void dfs(int u,int p){
    lv[u]=lv[p]+1;
    dp[u][0]=p;
    for(int i=1;i<=17;++i)dp[u][i]=dp[dp[u][i-1]][i-1];
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
    }
}

int fp(int u){
    if(u==pa[u])return u;
    return pa[u]=fp(pa[u]);
}

int lca(int x,int y){
    if(lv[x]<lv[y])swap(x,y);
    for(int i=17;i>=0;--i)if(lv[dp[x][i]]>=lv[y])x=dp[x][i];
    if(x==y)return x;
    for(int i=17;i>=0;--i)if(dp[x][i]!=dp[y][i])x=dp[x][i],y=dp[y][i];
    return dp[x][0];
}

int dist(int x,int y){
    int z=lca(x,y);
    return lv[x]+lv[y]-2*lv[z];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    iota(pa,pa+n+1,0);
    in.resize(m);
    for(auto &[o,u,v]:in){
        cin >> o;
        if(o==1){
            cin >> u >> v;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }else if(o==2)cin >> u;
        else cin >> u >> v;
    }
    for(int i=1;i<=n;++i)if(lv[i]==0)dfs(i,0);
    for(auto &[o,u,v]:in){
        if(o==1){
            u=fp(u),v=fp(v);
            pa[u]=v;
        }else if(o==2){
            pa[fp(u)]=u;
            pa[u]=u;
        }else{
            if(lv[u]<lv[v])swap(u,v);
            if(dist(fp(u),u)<dist(fp(u),v))cout << u << '\n';
            else cout << v << '\n';
        }
    }
}
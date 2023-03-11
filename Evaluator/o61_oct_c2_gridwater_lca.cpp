#include<bits/stdc++.h>

using namespace std;

const int N=160005;

int n,m;
int p[N],lv[N];
int pa[N][20],mx[N][20];
bool vis[N];
vector<pair<int,int>> adj[N];
vector<tuple<int,int,int>> edge,nonmst;

int fp(int u){
    if(u==p[u])return u;
    return p[u]=fp(p[u]);
}

int calc(int x,int y){
    return x*400+y;
}

void dfs(int u,int p,int x){
    vis[u]=true;
    pa[u][0]=p;
    mx[u][0]=x;
    lv[u]=lv[p]+1;
    for(int i=1;i<20;++i){
        pa[u][i]=pa[pa[u][i-1]][i-1];
        mx[u][i]=max(mx[u][i-1],mx[pa[u][i-1]][i-1]);
    }
    for(auto [v,w]:adj[u]){
        if(vis[v])continue;
        dfs(v,u,w);
    }
}

int lca(int x,int y){
    int ret=0;
    if(lv[x]<lv[y])swap(x,y);
    for(int i=19;i>=0;--i){
        if(lv[pa[x][i]]<lv[y])continue;
        ret=max(ret,mx[x][i]);
        x=pa[x][i];
    }
    if(x==y)return ret;
    for(int i=19;i>=0;--i){
        if(pa[x][i]==pa[y][i])continue;
        ret=max(ret,mx[x][i]);
        ret=max(ret,mx[y][i]);
        x=pa[x][i];
        y=pa[y][i];
    }
    return max(ret,mx[x][0]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n;
    for(int i=0;i<m*2-1;++i){
        int x,u,v;
        if(i&1){
            for(int j=0;j<n;++j){
                cin >> x;
                u=calc(i/2,j),v=calc(i/2+1,j);
                edge.emplace_back(x,u,v); 
            }
        }else{
            for(int j=0;j<n-1;++j){
                cin >> x;
                u=calc(i/2,j),v=calc(i/2,j+1);
                edge.emplace_back(x,u,v);
            }
        }
    }
    sort(edge.begin(),edge.end());
    iota(p,p+N,0);
    for(auto [w,u,v]:edge){
        if(fp(u)==fp(v)){
            nonmst.emplace_back(w,u,v);
            continue;
        }
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
        p[fp(u)]=fp(v);
    }
    dfs(0,0,0);
    int ans=2e9;
    for(auto [w,u,v]:nonmst){
        ans=min(ans,w-lca(u,v));
    }
    cout << ans;
}
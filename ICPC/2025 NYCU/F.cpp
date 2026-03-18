#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int LG=18;

int n,q;
vector<int> adj[N];
int dep[N],dp[N],pre[N],suf[N],above[N];
int par[LG][N],id[LG][N];

struct DS{
    pair<int,int> mx1,mx2,mx3;
    void update(int x,int i){
        pair<int,int> v(x,i);
        mx3=max(mx3,v);
        if(mx3>mx2)swap(mx2,mx3);
        if(mx2>mx1)swap(mx1,mx2);
    }
    int get(int i,int j){
        if(mx1.second!=i&&mx1.second!=j)return mx1.first;
        if(mx2.second!=i&&mx2.second!=j)return mx2.first;
        return mx3.first;
    }
}dat[LG][N];

void dfs(int u,int p){
    par[0][u]=p;
    id[0][u]=u;
    dat[0][u].update(1,0);
    dp[u]=1;
    dep[u]=dep[p]+1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        dat[0][u].update(dp[v]+1,v);
        dp[u]=max(dp[u],dp[v]+1);
    }
}

void dfs2(int u,int p){
    for(int t=0;t<2;t++){
        int cur=0;
        for(auto v:adj[u]){
            if(v==p)continue;
            (t?suf:pre)[v]=cur;
            cur=max(cur,dp[v]+1);
        }
        reverse(adj[u].begin(),adj[u].end());
    }
    for(auto v:adj[u]){
        if(v==p)continue;
        above[v]=max({above[u]+1,pre[v],suf[v]});
        dfs2(v,u);
    }
}

int query(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    int pu=-1,pv=-1,res=0;
    for(int i=LG-1;i>=0;i--){
        int x=par[i][u];
        if(dep[x]>=dep[v]){
            res=max(res,dat[i][u].get(pu,-1));
            pu=id[i][u];
            u=x;
        }
    }
    if(u!=v){
        for(int i=LG-1;i>=0;i--){
            int uu=par[i][u];
            int vv=par[i][v];
            if(uu!=vv){
                res=max(res,dat[i][u].get(pu,-1));
                res=max(res,dat[i][v].get(pv,-1));
                pu=id[i][u];
                pv=id[i][v];
                u=uu;
                v=vv;
            }
        }
        res=max(res,dat[0][u].get(pu,-1));
        res=max(res,dat[0][v].get(pv,-1));
        pu=id[0][u];
        pv=id[0][v];
        u=par[0][u];
        v=par[0][v];
    }
    res=max(res,dat[0][u].get(pu,pv));
    return max(res,above[u]+1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,0);
    dfs2(1,0);
    for(int i=1;i<LG;i++){
        for(int u=1;u<=n;u++){
            int v=par[i-1][u];
            par[i][u]=par[i-1][v];
            id[i][u]=id[i-1][v];
            dat[i][u]=dat[i-1][u];
            dat[i][u].update(dat[i-1][v].get(id[i-1][u],-1),0);
        }
    }
    while(q--){
        int u,v;
        cin >> u >> v;
        cout << query(u,v) << "\n";
    }
}
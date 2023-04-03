#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3005;

int n;
int fa[N];
vector<tuple<ll,int,int>> e1,e2;
vector<tuple<int,int,ll>> ans;
vector<pair<int,ll>> adj[N];
ll dp[N][N];

int fp(int u){
    if(u==fa[u])return u;
    return fa[u]=fp(fa[u]);
}

void dfs(int u,int p,int r){
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        dp[r][v]=dp[r][u]+w;
        dfs(v,u,r);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            int x;
            cin >> x;
            if(i<j)e1.emplace_back(x,i,j);
        }
    }
    iota(fa,fa+n+1,0);
    sort(e1.begin(),e1.end());
    for(auto [w,u,v]:e1){
        int pu=fp(u),pv=fp(v);
        if(pu==pv){
            e2.emplace_back(w,u,v);
            continue;
        }
        fa[pu]=pv;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
        ans.emplace_back(u,v,w);
    }
    for(int i=1;i<=n;i++)dfs(i,0,i);
    for(auto [w,u,v]:e2){
        if(w==dp[u][v])continue;
        ans.emplace_back(u,v,w);
        break;
    }
    sort(ans.begin(),ans.end());
    for(auto [u,v,w]:ans)cout << u << ' ' << v << ' ' << w << '\n';
}
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int n,m,k;
vector<int> adj[N];
int d[N],w[N];
map<int,ll> dp[N];

void dfs(int u){
    for(auto v:adj[u]){
        dfs(v);
        if(dp[v].size()>dp[u].size())swap(dp[u],dp[v]);
        for(auto [x,y]:dp[v])dp[u][x]+=y;
        dp[v].clear();
    }
    if(w[u]){
        dp[u][d[u]]+=w[u];
        int tmp=w[u];
        for(auto it=next(dp[u].find(d[u]));it!=dp[u].end();){
            if(tmp>=it->second){
                tmp-=it->second;
                it=dp[u].erase(it);
            }else{
                it->second-=tmp;
                break;
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=2;i<=n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    for(int i=1;i<=m;i++){
        int u;
        cin >> u >> d[u] >> w[u];
    }
    dfs(1);
    ll ans=0;
    for(auto [x,y]:dp[1])ans+=y;
    cout << ans;
}
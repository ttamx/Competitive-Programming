#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

int n;
vector<pair<int,int>> adj[N];
ll dp[N][4];

void dfs(int u,int p=0){
    pair<pair<ll,int>,pair<ll,int>> mx={{-1e18,-1},{-1e18,-1}},mx2={{-1e18,-1},{-1e18,-1}};
    ll c0=-1e18;
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        ll res=max(dp[v][0],dp[v][2]+w);
        dp[u][0]+=res;
        dp[u][1]+=res;
        dp[u][2]+=res;
        dp[u][3]+=res;
        mx.second=max(mx.second,{dp[v][0]+w-res,v});
        if(mx.second>mx.first)swap(mx.first,mx.second);
        mx2.second=max(mx2.second,{dp[v][1]+w-res,v});
        if(mx2.second>mx2.first)swap(mx2.first,mx2.second);
        c0=max(c0,max(dp[v][1],dp[v][3]+w)-res);
    }
    ll c1=mx.first.first+max(mx.second.first,mx.first.second!=mx2.first.second?mx2.first.first:mx2.second.first);
    ll c2=mx2.first.first+(mx2.first.second!=mx.first.second?mx.first.first:mx.second.first);
    dp[u][1]+=max({c0,c1,c2});
    dp[u][2]+=mx.first.first;
    dp[u][3]+=mx2.first.first;
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
    dfs(1);
    cout << max(dp[1][0],dp[1][1]);
}
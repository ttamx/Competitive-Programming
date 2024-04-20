#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=6e5+5;

int n,m;
vector<pair<int,int>> adj[N];
priority_queue<ll> dp[N];
ll ans;

void dfs(int u){
    for(auto [v,w]:adj[u]){
        dfs(v);
        ll x=dp[v].top();
        dp[v].pop();
        ll y=dp[v].top();
        dp[v].pop();
        dp[v].emplace(x+w),dp[v].emplace(y+w);
        if(dp[v].size()>dp[u].size())swap(dp[u],dp[v]);
        while(!dp[v].empty()){
            dp[u].emplace(dp[v].top());
            dp[v].pop();
        }
    }
    for(int i=1;i<adj[u].size();i++)dp[u].pop();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=2;i<=n+m;i++){
        int p,c;
        cin >> p >> c;
        adj[p].emplace_back(i,c);
        ans+=c;
    }
    for(int i=1;i<=m;i++){
        dp[n+i].emplace(0);
        dp[n+i].emplace(0);
    }
    dfs(1);
    dp[1].pop();
    while(!dp[1].empty()){
        ans-=dp[1].top();
        dp[1].pop();
    }
    cout << ans;
}
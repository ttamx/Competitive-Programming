#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const ll INF=LLONG_MAX/2;

int n,q;
int a[N];
vector<pair<int,int>> adj[N];
pair<ll,ll> dp[N];
ll ans[N];

void dfs(int u,int p=-1){
    if(!a[u])dp[u]={-INF,-INF};
    for(auto [v,w]:adj[u])if(v!=p){
        dfs(v,u);
        dp[u].second=max(dp[u].second,dp[v].first+w);
        if(dp[u].first<dp[u].second)swap(dp[u].first,dp[u].second);
    }
    if(a[u])dp[u]={0,0};
}

void dfs2(int u,int p=-1,ll d=-INF){
    if(a[u])d=0;
    ans[u]=max(dp[u].first,d);
    for(auto [v,w]:adj[u])if(v!=p){
        dfs2(v,u,w+(a[u]?0:(max(d,(dp[u].first!=dp[v].first+w)?dp[u].first:dp[u].second))));
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=0;i<n;i++)cin >> a[i];
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dfs(0);
    dfs2(0);
    while(q--){
        int x;
        cin >> x;
        cout << ans[x] << "\n";
    }
}
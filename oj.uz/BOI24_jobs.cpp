#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;

int n;
ll s;
ll a[N];
vector<int> adj[N];

struct DP:map<ll,ll>{
    void pop(ll x){
        auto it=begin();
        ll cur=-x,last=x;
        for(;it!=end()&&cur<0;it=erase(it)){
            if(cur<0)last=max(last,it->first-cur);
            else if(it->first<=last)break;
            cur+=it->second;
        }
        if(cur>0)(*this)[last]+=cur;
    }
}dp[N];

void dfs(int u){
    for(auto v:adj[u]){
        dfs(v);
        if(dp[v].size()>dp[u].size())swap(dp[u],dp[v]);
        for(auto [x,y]:dp[v])dp[u][x]+=y;
    }
    if(a[u]>=0)dp[u][0]+=a[u];
    else dp[u].pop(-a[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> s;
    for(int i=1;i<=n;i++){
        int p;
        cin >> a[i] >> p;
        adj[p].emplace_back(i);
    }
    dfs(0);
    ll ans=0;
    for(auto [x,y]:dp[0])if(x<=s)s+=y,ans+=y;
    cout << ans;
}
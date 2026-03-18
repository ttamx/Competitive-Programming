#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    freopen("time.in","r",stdin);
    freopen("time.out","w",stdout);
    int n,m,c;
    cin >> n >> m >> c;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> pre(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        pre[v].emplace_back(u);
    }
    vector<int> dp(n,-INF);
    dp[0]=0;
    int ans=0;
    for(int t=1;t<=500;t++){
        vector<int> new_dp(n,-INF);
        for(int u=0;u<n;u++){
            for(auto v:pre[u]){
                new_dp[u]=max(new_dp[u],dp[v]-c*((t*t)-(t-1)*(t-1))+a[u]);
            }
        }
        dp=move(new_dp);
        ans=max(ans,dp[0]);
    }
    cout << ans << "\n";
}
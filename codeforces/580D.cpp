#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> b(n,vector<int>(n));
    for(int i=0;i<k;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        b[u][v]=w;
    }
    ll ans=0;
    vector<vector<ll>> dp(1<<n,vector<ll>(n));
    for(int i=0;i<n;i++){
        dp[1<<i][i]=a[i];
    }
    for(int mask=1;mask<1<<n;mask++){
        for(int i=0;i<n;i++){
            if(!(mask>>i&1))continue;
            if(__builtin_popcount(mask)==m){
                ans=max(ans,dp[mask][i]);
            }
            for(int j=0;j<n;j++){
                if(mask>>j&1)continue;
                dp[mask|(1<<j)][j]=max(dp[mask|(1<<j)][j],dp[mask][i]+b[i][j]+a[j]);
            }
        }
    }
    cout << ans << "\n";
}
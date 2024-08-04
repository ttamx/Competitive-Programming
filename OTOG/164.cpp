#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

void solve(){
    int n,s;
    cin >> n >> s;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    vector<vector<array<ll,2>>> dp(n,vector<array<ll,2>>(n,{INF,INF}));
    int p=lower_bound(a.begin(),a.end(),s)-a.begin();
    if(p<n)dp[p][p][0]=dp[p][p][1]=1LL*(a[p]-s)*n;
    if(p>0)dp[p-1][p-1][0]=dp[p-1][p-1][1]=1LL*(s-a[p-1])*n;
    for(int s=2;s<=n;++s){
        for(int l=-0,r=s-1;r<n;l++,r++){
            dp[l][r][0]=min(dp[l+1][r][0]+1LL*(a[l+1]-a[l])*(n-s+1),dp[l+1][r][1]+1LL*(a[r]-a[l])*(n-s+1));
            dp[l][r][1]=min(dp[l][r-1][0]+1LL*(a[r]-a[l])*(n-s+1),dp[l][r-1][1]+1LL*(a[r]-a[r-1])*(n-s+1));
        }
    }
    cout << min(dp[0][n-1][0],dp[0][n-1][1]) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}
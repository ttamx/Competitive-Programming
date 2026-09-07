#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    vector<ll> f(n+1);
    for(int i=0;i<n;i++)f[i+1]=f[i]+a[i];
    auto calc=[&](ll lambda){
        vector<pair<ll,int>> dp(n+1);
        pair<ll,int> opt(0,0);
        for(int i=1;i<=n;i++){
            dp[i]=max(dp[i-1],{opt.first+f[i]-lambda,opt.second+1});
            opt=max(opt,{dp[i].first-f[i],dp[i].second});
        }
        return dp[n];
    };
    ll l=-2e9,r=1e15;
    while(l<r){
        ll m=l+(r-l+1)/2;
        if(calc(m).second>=k)l=m;
        else r=m-1;
    }
    cout << calc(l).first+l*k << "\n";
}
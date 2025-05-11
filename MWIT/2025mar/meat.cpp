#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    ll v;
    cin >> n >> k >> v;
    vector<ll> w(n+1),c(n+1);
    for(int i=1;i<=n;i++)cin >> w[i] >> c[i];
    for(int i=1;i<=n;i++){
        w[i]+=w[i-1];
        c[i]+=c[i-1];
    }
    vector<ll> dp(n+1,0);
    for(int t=0;t<k;t++){
        deque<pair<ll,ll>> dq;
        dq.emplace_back(0,0);
        for(int i=1;i<=n;i++){
            ll val=dp[i]-c[i];
            while(!dq.empty()&&w[i]-dq.front().second>v)dq.pop_front();
            if(!dq.empty())dp[i]=max(dp[i],c[i]+dq.front().first);
            while(!dq.empty()&&dq.back().first<val)dq.pop_back();
            dq.emplace_back(val,w[i]);
            dp[i]=max(dp[i],dp[i-1]);
        }
    }
    cout << dp[n];
}
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=1e9+7;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n+1);
    vector<int> lg(n+1);
    lg[1]=0;
    for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<vector<ll>> dp(20,vector<ll>(n+1));
    for(int i=1;i<=n;i++)dp[0][i]=a[i];
    auto lcm=[&](ll x,ll y){
        return min(mod,x/gcd(x,y)*y);
    };
    for(int i=1;i<20;i++)for(int j=1;j+(1<<i)-1<=n;j++)dp[i][j]=lcm(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);
    auto rmq=[&](int l,int r){
        int sz=lg[r-l+1];
        return lcm(dp[sz][l],dp[sz][r-(1<<sz)+1]);
    };
    auto chk=[&](ll m){
        int idx=1;
        for(int i=1;i<=n;i++){
            while(idx<=i&&rmq(idx,i)>m)idx++;
            if(idx<=i&&rmq(idx,i)==m)return true;
        }
        return false;
    };
    ll l=1,r=mod;
    while(l<r){
        ll m=(l+r)/2;
        if(chk(m))l=m+1;
        else r=m;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
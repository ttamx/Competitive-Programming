#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n,s;
    cin >> n >> s;
    vector<long long> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<pair<long long,long long>> v(n+2);
    v[1]={a[1],a[1]};
    v[n]={a[n],a[n]};
    for(int i=2;i<n;i++){
        long long x,y;
        if(a[i]>=2*s)x=s;
        else x=min(a[i],s);
        y=a[i]-x;
        if(x>y)swap(x,y);
        v[i]={x,y};
    }
    vector<pair<long long,long long>> dp(n+2);
    for(int i=1;i<=n;i++){
        dp[i].first=min(dp[i-1].first+v[i-1].second*v[i].first,dp[i-1].second+v[i-1].first*v[i].first);
        dp[i].second=min(dp[i-1].first+v[i-1].second*v[i].second,dp[i-1].second+v[i-1].first*v[i].second);
    }
    cout << min(dp[n].first,dp[n].second) << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
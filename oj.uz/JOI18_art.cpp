#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e5+5;

int n;
pair<ll,ll> a[N];
ll dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i].first >> a[i].second;
    sort(a+1,a+n+1);
    ll best=-1e18;
    for(int i=1;i<=n;i++){
        dp[i]=max(0ll,best-a[i].first)+a[i].second;
        best=max(best,a[i].first)+a[i].second;
    }
    ll ans=0;
    for(int i=1;i<=n;i++)ans=max(ans,dp[i]);
    cout << ans << "\n";
}
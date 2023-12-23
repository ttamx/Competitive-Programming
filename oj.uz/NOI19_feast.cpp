#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3e5+5;

int n,k;
ll a[N],qs[N];

pair<ll,int> calc(ll cost){
    pair<ll,int> dp(0,0),best(0,0);
    for(int i=1;i<=n;i++){
        dp=max(dp,{qs[i]-cost+best.first,best.second-1});
        best=max(best,{dp.first-qs[i],dp.second});
    }
    dp.second*=-1;
    return dp;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    ll l=0,r=3e14,ans=0;
    while(l<r){
        ll m=(l+r)/2;
        auto [val,cnt]=calc(m);
        if(cnt<=k)r=m,ans=val;
        else l=m+1;
    }
    cout << ans+l*k;
}
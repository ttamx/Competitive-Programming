#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2005;
const int M=2e6+5;

int n,q;
ll a[N];
ll ans,sum;
bitset<M> dp;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    sum=accumulate(a+1,a+n+1,0LL);
    ans=sum*(sum-1);
    for(int i=1;i<=n;i++)ans-=a[i]*(a[i]-1);
    ans/=2;
    if(q){
        dp[0]=1;
        for(int i=1;i<=n;i++)dp|=dp<<a[i];
        ll mx=0;
        for(int i=1;i<=sum;i++)if(dp[i])mx=max(mx,i*(sum-i));
        ans-=mx;
    }
    cout << ans;
}
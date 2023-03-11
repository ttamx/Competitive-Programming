#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
void runcase(){
    ll n,m;
    cin >> n >> m;
    vector<ll> dp(n+1);
    ll ans=0;
    for(int i=n;i>1;i--){
        dp[i]=(n/i)*(n/i-1)/2;
        for(int j=2*i;j<=n;j+=i)dp[i]-=dp[j];
        ans+=min(dp[i],m)/(i-1)*i;
        m-=min(dp[i],m)/(i-1)*(i-1);
    }
    if(m)ans=-1;
    cout << ans << '\n';
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
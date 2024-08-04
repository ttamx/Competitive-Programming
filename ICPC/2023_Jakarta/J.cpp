#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=998244353;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<ll> pw(n+1);
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*2%MOD;
    }
    vector<ll> dp(n);
    dp[0]=1;
    for(int i=2;i<n;i++){
        vector<ll> ndp(n);
        ll sum=0;
        for(int j=0;j<i;j++){
            ndp[j]=sum;
            if(a[i-1]<a[i]){
                ndp[j]+=dp[j];
                ndp[j]%=MOD;
            }
            ndp[j]*=pw[i-j-1];
            ndp[j]%=MOD;
            sum+=dp[j];
            sum%=MOD;
        }
        swap(dp,ndp);
    }
    ll ans=0;
    for(int i=0;i<n;i++){
        ans+=dp[i];
        ans%=MOD;
    }
    cout << ans << "\n";
}
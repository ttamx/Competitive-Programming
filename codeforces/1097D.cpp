#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=1e9+7;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

ll inv[60];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n;
    int k;
    cin >> n >> k;
    for(int i=1;i<60;i++)inv[i]=binpow(i,MOD-2);
    vector<pair<ll,int>> a;
    for(ll i=2;i*i<=n;i++){
        if(n%i)continue;
        int c=0;
        while(n%i==0){
            c++;
            n/=i;
        }
        a.emplace_back(i,c);
    }
    if(n>1)a.emplace_back(n,1);
    ll ans=1;
    for(auto [v,c]:a){
        vector<ll> dp(c+1);
        dp[c]=1;
        for(int i=0;i<k;i++){
            for(int j=0;j<=c;j++)dp[j]=dp[j]*inv[j+1]%MOD;
            for(int j=c-1;j>=0;j--)dp[j]=(dp[j]+dp[j+1])%MOD;
        }
        ll x=1,sum=0;
        for(int i=0;i<=c;i++){
            sum=(sum+dp[i]*x)%MOD;
            x=x*v%MOD;
        }
        ans=ans*sum%MOD;
    }
    cout << ans << "\n";
}
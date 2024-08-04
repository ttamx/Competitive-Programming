#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=998244353;

ll modpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    string a,b;
    cin >> a >> b;
    vector<ll> ca(27),cb(27);
    for(auto x:a)ca[x-'A']++;
    for(auto x:b)cb[x-'A']++;
    vector<ll> fac(n+1),ifac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%MOD;
    ifac[n]=modpow(fac[n],MOD-2);
    for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i%MOD;
    auto C=[&](int n,int r){
        if(n<0||r<0||n<r)return 0LL;
        return fac[n]*ifac[n-r]%MOD*ifac[r]%MOD;
    };
    vector<vector<ll>> dp(27);
    for(int i=0;i<27;i++)dp[i].resize(cb[i]+1);
    dp[0][0]=1;
    for(int i=0;i<26;i++){
        auto &ndp=dp[i+1];
        for(int j=0;j<=cb[i];j++){
            int l=max(0LL,ca[i]-(cb[i]-j));
            int r=ca[i];
            if(l<=cb[i+1]){
                ndp[l]+=dp[i][j];
                ndp[l]%=MOD;
            }
            if(r+1<=cb[i+1]){
                ndp[r+1]+=MOD-dp[i][j];
                ndp[r+1]%=MOD;
            }
        }
        for(int j=1;j<=cb[i+1];j++){
            ndp[j]+=ndp[j-1];
            ndp[j]%=MOD;
        }
        for(int j=0;j<=cb[i+1];j++){
            ndp[j]*=C(ca[i],j);
            ndp[j]%=MOD;
        }
    }
    ll ans=dp[26][0];
    ans*=fac[n];
    ans%=MOD;
    for(int i=0;i<26;i++){
        ans*=ifac[ca[i]];
        ans%=MOD;
    }
    cout << ans << "\n";
}
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=998244353;

ll inv[7];

ll modpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=1;i<=6;i++)inv[i]=modpow(i,MOD-2);
    vector<vector<ll>> dp(n+1);
    function<void(int)> rec=[&](int n){
        if(!dp[n].empty())return;
        dp[n].resize(n);
        if(n==1){
            dp[1][0]=1;
            return;
        }
        if(n%6==0){
            rec(n*5/6);
        }else{
            rec(n-(n/6));
            rec(n-(n/6)-1);
        }
        int cnt=0;
        for(int s=0;s<6;s++){
            int pos=0;
            int sz=n-(n/6);
            if(n%6!=0&&s<n%6)sz--;
            if(sz==n)continue;
            cnt++;
            for(int i=0;i<n;i++){
                if(i%6==s)continue;
                dp[n][i]+=dp[sz][pos];
                if(dp[n][i]>=MOD)dp[n][i]-=MOD;
                pos++;
            }
        }
        for(auto &x:dp[n])x=x*inv[cnt]%MOD;
    };
    rec(n);
    for(auto x:dp[n])cout << x << "\n";
}
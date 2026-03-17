#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int X=1e6+5;
const int MOD=1e9+7;

int n;
int cnt[X],mob[X];
ll pw[N],dp[N],dp2[X];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    mob[1]=1;   
    for(int i=1;i<X;i++){
        for(int j=i*2;j<X;j+=i){
            mob[j]-=mob[i];
            cnt[i]+=cnt[j];
        }
    }
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*2%MOD;
        dp[i]=(dp[i-1]*2+pw[i-1])%MOD;
    }
    for(int i=1;i<X;i++){
        dp2[i]=dp[cnt[i]];
    }
    ll ans=0;
    for(int i=1;i<X;i++){
        for(int j=2;i*j<X;j++){
            dp2[i]=(dp2[i]+dp2[i*j]*mob[j]+MOD)%MOD;
        }
    }
    for(int i=2;i<X;i++){
        ans=(ans+dp2[i]*i)%MOD;
    }
    cout << ans << "\n";
}
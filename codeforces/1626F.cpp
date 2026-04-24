#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,s,x,y,k,mod;
    cin >> n >> s >> x >> y >> k >> mod;
    int d=1;
    for(int i=1;i<=k;i++)d=lcm(d,i);
    vector<mint> pw(k+1);
    pw[0]=1;
    for(int i=1;i<=k;i++)pw[i]=pw[i-1]*n;
    mint ans=0;
    vector<mint> dp(d);
    for(int i=0;i<n;i++){
        int v=s%d;
        dp[v]++;
        ans+=pw[k-1]*k*(s-v);
        s=(1LL*s*x+y)%mod;
    }
    for(int i=1;i<=k;i++){
        auto ndp=dp;
        for(auto &x:ndp)x*=n-1;
        for(int j=0;j<d;j++){
            ans+=dp[j]*pw[k-i]*j;
            ndp[j-j%i]+=dp[j];
        }
        dp=move(ndp);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
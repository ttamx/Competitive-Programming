#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<mint> a(n);
    for(auto &x:a)cin >> x;
    int m=1<<n;
    vector<vector<mint>> p(n,vector<mint>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            p[i][j]=a[i]/(a[i]+a[j]);
        }
    }
    auto calc=[&](int s,int t){
        assert((s&t)==0);
        mint res=1;
        for(int i=0;i<n;i++){
            if(s>>i&1){
                for(int j=0;j<n;j++){
                    if(t>>j&1){
                        res*=p[i][j];
                    }
                }
            }
        }
        return res;
    };
    vector<mint> dp(m);
    for(int mask=0;mask<m;mask++){
        dp[mask]=1;
        for(int mask2=(mask-1)&mask;mask2;mask2=(mask2-1)&mask){
            dp[mask]-=dp[mask2]*calc(mask2,mask^mask2);
        }
    }
    mint ans=0;
    for(int mask=1;mask<m;mask++){
        ans+=__builtin_popcount(mask)*dp[mask]*calc(mask,(m-1)^mask);
    }
    cout << ans << "\n";
}
#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;
Combinatorics<mint> comb;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        a[x-1]=1;
    }
    vector<int> dp{0,1};
    for(int s=2;s<=n;s++){
        int t=(n-s)%2;
        int nn=1<<s;
        vector<int> ndp(nn,t);
        for(int mask=0;mask<nn;mask++){
            int c=0;
            for(int i=0;i<s;i++){
                if(a[i]){
                    int mask2=(mask&((1<<i)-1))|(mask>>(i+1)<<i);
                    if(t){
                        ndp[mask]=min(ndp[mask],dp[mask2]);
                    }else{
                        ndp[mask]=max(ndp[mask],dp[mask2]);
                    }
                }
            }
        }
        dp=move(ndp);
    }
    vector<int> cnt(n+1);
    for(int mask=0;mask<(1<<n);mask++){
        if(dp[mask]){
            cnt[__builtin_popcount(mask)]++;
        }
    }
    mint ans=0;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            mint ways=cnt[j];
            for(int k=0;k<j;k++){
                ways*=m-i+1;
            }
            for(int k=j;k<n;k++){
                ways*=i-1;
            }
            ans+=ways;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
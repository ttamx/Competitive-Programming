#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    mint ans=0;
    for(int d=1;d*(k-1)<=a.back();d++){
        vector<mint> dp(n);
        for(int i=0;i<n;i++)dp[i]=i+1;
        for(int t=0;t<k-1;t++){
            vector<mint> ndp(n);
            mint cur=0;
            for(int i=0,j=0;i<n;i++){
                while(a[i]-a[j]>=d)j++;
                if(j>0)cur+=dp[j-1];
                ndp[i]=cur;
            }
            dp=move(ndp);
        }
        ans+=dp[n-1];
    }
    cout << ans << "\n";
}
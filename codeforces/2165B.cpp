#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a[x-1]++;
    }
    sort(a.rbegin(),a.rend());
    while(a.back()==0){
        a.pop_back();
    }
    int m=a.size();
    vector<vector<mint>> suf(m);
    {
        vector<mint> dp(n+1);
        dp[0]=1;
        for(int i=m-1;i>=0;i--){
            suf[i]=dp;
            for(int j=n;j>=a[i];j--){
                dp[j]+=dp[j-a[i]]*a[i];
            }
        }
    }
    mint ans=0;
    int cnt=0;
    mint ways=1;
    for(int i=0;i<m;i++){
        for(int j=0;j<=n;j++){
            if(cnt+j>=a[i]){
                ans+=suf[i][j]*ways;
            }
        }
        cnt+=a[i];
        ways*=a[i];
    }
    cout << ans+ways << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
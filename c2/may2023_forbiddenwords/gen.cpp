#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128_t;

const int N=60;

int n;
ll dp[N];

int main(){
    cin >> n;
    dp[0]=dp[1]=1;
    ll sum=0;
    for(int i=2;i<=n;i++){
        for(int j=0;j<i-j-1;j++){
            dp[i]+=min(i128(dp[j])*dp[i-j-1],i128(1e18));
            dp[i]=min(dp[i],ll(1e18));
        }
        if(i&1){
            int m=i/2;
            dp[i]+=min(i128(dp[m])*(dp[m]+1)/2,i128(1e18));
            dp[i]=min(dp[i],ll(1e18));
        }
        cout << i << " : " << dp[i] << "\n";
        sum+=dp[i];
        cerr << "XX :" << min(sum,(ll)1e18) << "\n";
    }
    cout << "XX : " << dp[51]+dp[52] << "\n";
}
#include<bits/stdc++.h>

using namespace std;

const int B=17;
const int S=1<<B;
const int MOD=998244353;
const int INV=499122177;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<array<int,2>> dp(S,array<int,2>{0,0});
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        dp[x][0]++;
    }
    for(int j=0;j<B;j++){
        vector<array<int,2>> ndp(S,array<int,2>{0,0});
        for(int i=0;i<S;i++){
            int b=i>>j&1;
            for(int k=0;k<2;k++){
                ndp[i][k]=(dp[b?i^(1<<j):i][k]+dp[i|(1<<j)][k^b])%MOD;
            }
        }
        swap(dp,ndp);
    }
    vector<int> pw(n+1);
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=3LL*pw[i-1]%MOD;
    }
    int ans=0;
    for(int i=0;i<S;i++){
        ans=((ans+(pw[dp[i][0]]*(dp[i][1]%2==0?1:-1)))%MOD+MOD)%MOD;
    }
    for(int i=0;i<B;i++){
        ans=(1LL*ans*INV)%MOD;
    }
    cout << ans << "\n";
}
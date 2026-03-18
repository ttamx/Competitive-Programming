#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    vector<int> a(n+1);
    for(int i=1;i<n;i++){
        a[i]=s[i]!=s[i-1];
    }
    auto cost=[&](int i,int v){
        if(i==0||i==n)return 0;
        return a[i]^v;
    };
    vector<int> dp2(m+1);
    for(int s=0;s<k;s++){
        int sz=(n+1)/k+1;
        vector<array<int,2>> dp(sz,{-INF,-INF});
        dp[0][0]=cost(s,0);
        for(int i=s+k;i<=n;i+=k){
            vector<array<int,2>> ndp(sz,{-INF,-INF});
            for(int j=0;j<sz;j++){
                ndp[j][0]=cost(i,0)+max(dp[j][0],dp[j][1]);
                if(j>0){
                    ndp[j][1]=cost(i,1)+max(dp[j-1][0]-cost(i-k,0)+cost(i-k,1),dp[j-1][1]-cost(i-k,1)+cost(i-k,0));
                }
            }
            dp=move(ndp);
        }
        auto ndp=dp2;
        for(int i=0;i<sz;i++){
            for(int j=i;j<=m;j++){
                ndp[j]=max(ndp[j],dp2[j-i]+max(dp[i][0],dp[i][1]));
            }
        }
        dp2=move(ndp);
    }
    cout << dp2[m]+1 << "\n";
}
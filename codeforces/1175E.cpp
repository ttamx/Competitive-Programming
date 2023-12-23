#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int M=5e5+5;
const int K=20;

int n,m;
int dp[M][K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<M;i++)dp[i][0]=i;
    for(int i=0;i<n;i++){
        int l,r;
        cin >> l >> r;
        dp[l][0]=max(dp[l][0],r);
    }
    for(int i=1;i<M;i++)dp[i][0]=max(dp[i][0],dp[i-1][0]);
    for(int i=1;i<K;i++)for(int j=0;j<M;j++)dp[j][i]=dp[dp[j][i-1]][i-1];
    while(m--){
        int l,r;
        cin >> l >> r;
        if(dp[l][K-1]<r)cout << -1 << "\n";
        else{
            int ans=0;
            for(int i=K-1;i>=0;i--)if(dp[l][i]<r)l=dp[l][i],ans|=1<<i;
            cout << ans+1 << "\n";
        }
    }
}
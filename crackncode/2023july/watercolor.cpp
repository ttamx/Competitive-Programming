#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")

using namespace std;

typedef long long ll;

const int N=10005;
const int mod=1e9+7;

int n,m,p;
ll dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> p;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        dp[x]++;
    }
    for(int i=1;i<=m;i++){
        int b;
        cin >> b;
        for(int j=1;j<b;j++){
            int res=(j+b)>>1;
            if(res==j)continue;
            dp[res]+=dp[j];
            if(dp[res]>=mod)dp[res]-=mod;
        }
        for(int j=p;j>b;j--){
            int res=(j+b)>>1;
            if(res==j)continue;
            dp[res]+=dp[j];
            if(dp[res]>=mod)dp[res]-=mod;
        }
    }
    for(int i=1;i<=p;i++)cout << dp[i] << "\n";
}
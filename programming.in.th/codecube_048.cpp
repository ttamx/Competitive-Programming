#include<bits/stdc++.h>

using namespace std;

const int N=505;
const int M=50005;
const int mod=1e6+7;

int n,m;
int v[N],dp[M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> v[i];
    dp[0]=1;
    for(int i=1;i<=n;i++)for(int j=m;j>=v[i];j--)dp[j]+=dp[j-v[i]],dp[j]%=mod;
    cout << dp[m];
}
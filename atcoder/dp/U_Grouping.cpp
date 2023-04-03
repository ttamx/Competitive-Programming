#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=16;

int n;
ll a[N][N],dp[1<<N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin >> a[i][j];
    for(int i=0;i<1<<n;i++){
        vector<int> v;
        for(auto j=0;j<n;j++)if(i&(1<<j))v.emplace_back(j);
        for(auto x:v)for(auto y:v)if(x<y)dp[i]+=a[x][y];
        for(int j=i;j>0;j=(j-1)&i)dp[i]=max(dp[i],dp[j]+dp[i^j]);
    }
    cout << dp[(1<<n)-1];
}
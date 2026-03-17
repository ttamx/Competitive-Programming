#include <bits/stdc++.h>

using namespace std;

const int nx=1e3+5;

int n, c, v[nx], w[nx], dp[nx][nx];

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    cin>>c;
    int x;
    vector<int> a;
    while(cin >> x){
        a.emplace_back(x);
    }
    int n=a.size()/2, cnt=0;
    for (int i=1; i<=n; i++) v[i]=a[cnt++];
    for (int i=1; i<=n; i++) w[i]=a[cnt++];
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=c; j++)
        {
            dp[i][j]=dp[i-1][j];
            if (j>=w[i]) dp[i][j]=max(dp[i][j], dp[i-1][j-w[i]]+v[i]);
        }
    }
    cout<<dp[n][c];
}
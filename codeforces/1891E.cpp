#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,int> p2;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<bool> bad(n+2);
    for(int i=2;i<=n;i++)bad[i]=(gcd(a[i],a[i-1])==1);
    vector<vector<int>> dp0(n+2,vector<int>(k+2)),dp1(n+2,vector<int>(k+2));
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++)dp0[i][j]=min(dp0[i-1][j]+bad[i],dp1[i-1][j]+(a[i]==1));
        for(int j=1;j<=k;j++)dp1[i][j]=min(dp0[i-1][j-1]+(a[i-1]==1),dp1[i-1][j]);
    }
    cout << min(dp0[n][k],dp1[n][k]) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
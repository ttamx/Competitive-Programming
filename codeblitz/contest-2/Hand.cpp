#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll sum=0;

void runcase(){
    int n,d,l,r;
    cin >> n >> l >> r >> d;
    d=min(d,n);
    vector<vector<vector<ll>>> dp(2*n+2,vector<vector<ll>>(l+2,vector<ll>(r+2,-1e18)));
    dp[n][l][r]=0;
    for(int t=1;t<=n;t++){
        int x,y,v;
        cin >> x >> y >> v;
        auto ndp=dp;
        for(int i=0;i<=2*n;i++){
            for(int j=1;j<=l;j++){
                for(int k=1;k<=r;k++){
                    if(i>0&&j+x<=l)ndp[i][j][k]=max(ndp[i][j][k],dp[i-1][j+x][k]+v);
                    if(i<2*n&&k+y<=r)ndp[i][j][k]=max(ndp[i][j][k],dp[i+1][j][k+y]+v);
                }
            }
        }
        swap(ndp,dp);
    }
    ll ans=0;
    for(int i=n-d;i<=n+d;i++){
        for(int j=1;j<=l;j++){
            for(int k=1;k<=r;k++){
                ans=max(ans,dp[i][j][k]);
            }
        }
    }
    cout << ans << "\n";
    sum+=ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
    cout << sum;
}
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=505;

int n,m,ans;
pair<ll,ll> p[N];
ll dp[N][N];

ll calc(int i,int j){
    return abs(p[i].first-p[j].first)+abs(p[i].second-p[j].second);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)dp[i][j]=1e18;
    for(int i=1;i<=n;i++)cin >> p[i].first >> p[i].second;
    dp[0][1]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=dp[i-1][j];
            for(int k=1;k<=n;k++){
                dp[i][j]=min(dp[i][j],max(dp[i-1][k],calc(j,k)));
            }
        }
    }
    for(int i=0;i<m;i++){
        ll x;
        cin >> x;
        int l=1,r=n;
        while(l<r){
            int mid=(l+r)/2;
            if(x>=dp[mid][n])r=mid;
            else l=mid+1;
        }
        ans+=l;
    }
    cout << ans;
}
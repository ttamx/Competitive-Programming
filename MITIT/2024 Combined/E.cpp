#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=505;
const int M=1005;
const ll INF=1e18;

int n,q,c;
pair<int,int> a[M];
ll dp[M][M],dp2[M][M];
ll dp3[M],dp4[M];

ll cost(int i,int j){
    return abs(a[i].second-a[j].second);
}

int good(int i,int j){
    int d=a[j].first-a[i].first;
    return d*2<=c;
}

void solve(){
    cin >> n >> q >> c;
    for(int i=1;i<=n;i++){
        cin >> a[i].first >> a[i].second;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        a[i+n]=a[i];
        a[i+n].first+=c;
    }
    for(int i=1;i<=2*n;i++){
        for(int j=1;j<=2*n;j++){
            dp[i][j]=dp2[i][j]=INF;
        }
    }
    for(int i=1;i<=2*n;i++){
        dp[i][i]=dp2[i][i]=0LL;
    }
    for(int sz=2;sz<=2*n;sz++){
        for(int l=1,r=sz;r<=2*n;l++,r++){
            for(int m=l;m<r;m++){
                dp[l][r]=min(dp[l][r],min(dp[l][m]+dp2[m+1][r],dp2[l][m]+dp[m+1][r])+cost(l,r));
            }
            if(good(l,r)){
                dp2[l][r]=dp[l][r];
            }
            for(int m=l;m<=r;m++){
                dp2[l][r]=min(dp2[l][r],dp2[l][m]+dp2[m][r]);
            }
        }
    }
    while(q--){
        cin >> a[2*n+1].second;
        ll ans=INF;
        for(int st=1;st<=(n<=80?n:1);st++){
            dp3[st]=0LL;
            dp4[st]=cost(st,2*n+1);
            for(int i=st+1;i<=st+n-1;i++){
                dp3[i]=dp4[i]=INF;
                for(int j=st;j<i;j++){
                    dp3[i]=min(dp3[i],dp3[j]+dp2[j][i]);
                    dp3[i]=min(dp3[i],dp4[j]+dp2[j+1][i]);
                    dp4[i]=min(dp4[i],dp4[j]+dp2[j][i]);
                }
                dp4[i]=min(dp4[i],dp3[i]+cost(i,2*n+1));
            }
            ans=min(ans,dp4[st+n-1]);
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}
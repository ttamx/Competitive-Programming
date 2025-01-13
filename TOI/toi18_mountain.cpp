#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=505;
const ll INF=LLONG_MAX/2;

int n,q;
ll a[N],b[N];
ll dp[N][N];
ll ans;

ll dist(int i,int j){
    return abs(a[i]-a[j])+abs(b[i]-b[j]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i] >> b[i];
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            dp[i][j]=INF;
        }
    }
    dp[1][0]=0;
    for(int i=1;i<=n;i++){
        for(int u=1;u<=n;u++){
            for(int v=1;v<=n;v++){
                dp[u][i]=min(dp[u][i],max(dp[v][i-1],dist(u,v)));
            }
        }
    }
    while(q--){
        ll s;
        cin >> s;
        int l=1,r=n;
        while(l<r){
            int m=(l+r)/2;
            if(dp[n][m]<=s)r=m;
            else l=m+1;
        }
        ans+=l;
    }
    cout << ans;
}
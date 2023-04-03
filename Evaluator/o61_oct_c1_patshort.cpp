#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

const int N=205;

int m,q;
p2 a[N];
ll dp[N][N];

ll calc(p2 x,p2 y){
    if(x.second>y.second)swap(x,y);
    ll d=y.second-x.second;
    if(y.first<x.first){
        ll mn=x.first-d;
        if(y.first<=mn)return d+mn-y.first;
        return d+(d%2!=(x.first-y.first)%2);
    }
    ll mx=x.first+d;
    if(y.first>=mx)return d+y.first-mx;
    return d+(d%2!=(y.first-x.first)%2);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> q;
    for(int i=1;i<=m;i++){
        cin >> a[i*2-1].first >> a[i*2-1].second >> a[i*2].first >> a[i*2].second;
    }
    for(int i=1;i<=2*m;i++)for(int j=1;j<=2*m;j++)dp[i][j]=calc(a[i],a[j]);
    for(int i=1;i<=m;i++)dp[i*2-1][i*2]=dp[i*2][i*2-1]=1;
    for(int k=1;k<=2*m;k++)for(int i=1;i<=2*m;i++)for(int j=1;j<=2*m;j++)dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
    while(q--){
        p2 x,y;
        cin >> x.first >> x.second >> y.first >> y.second;
        ll ans=calc(x,y);
        for(int i=1;i<=2*m;i++)for(int j=1;j<=2*m;j++)ans=min(ans,dp[i][j]+calc(x,a[i])+calc(a[j],y));
        cout << ans << '\n';
    }
}
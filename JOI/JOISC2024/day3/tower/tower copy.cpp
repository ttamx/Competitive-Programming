#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int X=1e6+5;
const ll INF=1e18;

int n,q;
ll d,a,b;
bool bad[X];
ll dp[X];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    cin >> d >> a >> b;
    for(int i=1;i<=n;i++){
        int l,r;
        cin >> l >> r;
        for(int j=l;j<=r;j++)bad[j]=true;
    }
    for(int i=1;i<X;i++){
        dp[i]=INF;
        if(bad[i])continue;
        dp[i]=min(dp[i],dp[i-1]+a);
        if(i>=d)dp[i]=min(dp[i],dp[i-d]+b);
    }
    while(q--){
        ll x;
        cin >> x;
        cout << (dp[x]==INF?-1LL:dp[x]) << "\n";
    }
}
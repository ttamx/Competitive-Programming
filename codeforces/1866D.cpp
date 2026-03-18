#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<ll>> a(m,vector<ll>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> a[j][i];
        }
    }
    vector<ll> dp(k,-INF);
    dp[0]=0;
    for(auto &v:a){
        vector<ll> ndp(k,-INF);
        sort(v.rbegin(),v.rend());
        v.insert(v.begin(),0LL);
        for(int i=1;i<=n;i++){
            v[i]+=v[i-1];
        }
        for(int i=0;i<k;i++){
            for(int j=0;i+1-j>=0&&j<=n;j++){
                int x=min(i+1-j,k-1);
                ndp[x]=max(ndp[x],dp[i]+v[j]);
            }
        }
        dp=move(ndp);
    }
    cout << dp[k-1] << "\n";
}
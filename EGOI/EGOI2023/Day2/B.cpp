#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,f;
    ll t;
    cin >> n >> f >> t;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int m=n*(n-1)/2;
    vector<vector<ll>> dp(f+1,vector<ll>(m+1));
    for(int x=0;x<n;x++){
        for(int i=min(x+1,f);i>=1;i--){
            int s=x-i+1;
            for(int j=s;j<=m;j++){
                dp[i][j]=max(dp[i][j],dp[i-1][j-s]+a[x]);
            }
        }
    }
    for(int i=0;i<=m;i++){
        if(dp[f][i]>=t){
            cout << i;
            exit(0);
        }
    }
    cout << "NO";
}
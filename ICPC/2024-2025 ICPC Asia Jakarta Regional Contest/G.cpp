#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,p;
    cin >> n >> m >> p;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<ll> cost(10);
    for(int i=1;i<10;i++){
        cost[i]=1;
        for(int j=0;j<p;j++){
            cost[i]*=i;
        }
    }
    auto calc=[&](int x)->ll{
        return x<0?-cost[-x]:cost[x];
    };
    bool bad=false;
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            ll path=calc(a[i-1][j-1]-a[i-1][j])+calc(a[i-1][j]-a[i][j])+calc(a[i][j]-a[i][j-1])+calc(a[i][j-1]-a[i-1][j-1]);
            if(path!=0){
                bad=true;
            }
        }
    }
    vector<vector<ll>> dp(n,vector<ll>(m));
    for(int i=1;i<m;i++){
        dp[0][i]=dp[0][i-1]+calc(a[0][i-1]-a[0][i]);
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<m;j++){
            dp[i][j]=dp[i-1][j]+calc(a[i-1][j]-a[i][j]);
        }
    }
    int q;
    cin >> q;
    while(q--){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--,y1--,x2--,y2--;
        if(bad){
            cout << "INVALID\n";
        }else{
            cout << dp[x2][y2]-dp[x1][y1] << "\n";
        }
    }
}
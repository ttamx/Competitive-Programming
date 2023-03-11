#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<vector<ll>> dp(n,vector<ll>(n));
    vector<vector<bool>> use(n,vector<bool>(n,true));
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            cin >> dp[i][j];
            dp[j][i]=dp[i][j];
        }
    }
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            if(i==k)continue;
            for(int j=0;j<n;j++){
                if(j==i||j==k)continue;
                if(dp[i][k]+dp[k][j]<dp[i][j]){
                    cout << "Need better measurements.\n";
                    return;
                }
                if(dp[i][k]+dp[k][j]==dp[i][j])use[i][j]=false;
            }
        }
    }
    vector<tuple<int,int,ll>> ans;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(use[i][j]){
                ans.emplace_back(j,i,dp[i][j]);
            }
        }
    }
    sort(ans.begin(),ans.end());
    cout << ans.size() << '\n';
    for(auto [x,y,z]:ans)cout << x+1 << ' ' << y+1 << ' ' << z << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ":\n";
        runcase();
        cout << '\n';
    }
}
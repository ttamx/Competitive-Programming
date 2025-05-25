#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int tot=accumulate(a.begin(),a.end(),0LL);
    int m=tot+10;
    int offset=m/2;
    vector<int> dp(m,INF);
    dp[offset]=0;
    for(auto x:a){
        vector<int> new_dp(m,INF);
        for(int i=0;i<m;i++){
            new_dp[i]=dp[i]+x;
            if(i>=x){
                new_dp[i]=min(new_dp[i],dp[i-x]);
            }
            if(i+x<m){
                new_dp[i]=min(new_dp[i],dp[i+x]);
            }
        }
        dp=move(new_dp);
    }
    cout << (tot+dp[offset])/2;
}
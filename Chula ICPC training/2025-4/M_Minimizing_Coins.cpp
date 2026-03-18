#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> dp(m+1,INF);
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    dp[0]=0;
    for(int i=1;i<=m;i++){
        for(auto x:a){
            if(x<=i){
                dp[i]=min(dp[i],dp[i-x]+1);
            }
        }
    }
    cout << (dp[m]<INF?dp[m]:-1) << "\n";
}
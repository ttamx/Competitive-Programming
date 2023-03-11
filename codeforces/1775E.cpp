#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<pair<ll,ll>> dp(n+1);
    for(int i=1;i<=n;i++){
        ll x;
        cin >> x;
        if(x>0){
            if(x>dp[i-1].first){
                dp[i].first=0;
                dp[i].second=dp[i-1].second+x;
            }else{
                dp[i].first=dp[i-1].first-x;
                dp[i].second=dp[i-1].second+x;
            }
        }else{
            x=-x;
            if(x>dp[i-1].second){
                dp[i].second=0;
                dp[i].first=dp[i-1].first+x;
            }else{
                dp[i].second=dp[i-1].second-x;
                dp[i].first=dp[i-1].first+x;
            }
        }
    }
    cout << dp[n].first+dp[n].second << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
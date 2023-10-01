#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> dp(n+1),mn(n+1,n);
    dp[0]=0;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        dp[i]=min(dp[i-1]+1,mn[x]);
        mn[x]=min(mn[x],dp[i-1]);
    }
    cout << n-dp[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int w,n;
    cin >> w >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> dp(20001,2e9);
    dp[0]=0;
    for(auto x:a)for(int i=20000;i>=x;i--)dp[i]=min(dp[i],dp[i-x]+1);
    for(int i=w;i<=20000;i++)if(dp[i]<2e9)return void(cout << i << ' ' << dp[i] << '\n');
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
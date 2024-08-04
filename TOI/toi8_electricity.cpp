#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n),dp(n);
    for(auto &x:a)cin >> x;
    dp[0]=a[0];
    deque<int> dq{0};
    for(int i=1;i<n;i++){
        while(i-dq.front()>k)dq.pop_front();
        dp[i]=a[i]+dp[dq.front()];
        while(!dq.empty()&&dp[dq.back()]>=dp[i])dq.pop_back();
        dq.emplace_back(i);
    }
    cout << dp.back();
}
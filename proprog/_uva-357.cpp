#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<long long> dp(30001,1);
    for(int i=5;i<=30000;i++)dp[i]+=dp[i-5];
    for(int i=10;i<=30000;i++)dp[i]+=dp[i-10];
    for(int i=25;i<=30000;i++)dp[i]+=dp[i-25];
    for(int i=50;i<=30000;i++)dp[i]+=dp[i-50];
    int n;
    while(cin >> n){
        if(dp[n]==1)cout << "There is only 1 way to produce " << n << " cents change.\n";
        else cout << "There are " << dp[n] << " ways to produce " << n << " cents change.\n";
    }
}
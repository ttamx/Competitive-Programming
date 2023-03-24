#include<bits/stdc++.h>

using namespace std;

const int N=15005;

int n,m;
int a[N];
int b[N];
pair<int,vector<int>> dp[N];
int sum=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i],sum+=a[i];
        assert(a[i]==1);
    }
    cin >> m;
    for(int i=1;i<=m;i++)cin >> b[i];
    for(int i=1;i<=sum;i++)dp[i].first=2e9;
    for(int i=1;i<=m;i++){
        for(int j=b[i];j<=sum;j++){
            int val=dp[j-b[i]].first;
            if(val<dp[j].first){
                dp[j]=dp[j-b[i]];
                dp[j].first++;
                dp[j].second.emplace_back(b[i]);
            }
        }
    }
    if(dp[sum].first==2e9)cout << -1,exit(0);
    cout << dp[sum].first << '\n';
    int num=1;
    for(auto x:dp[sum].second){
        cout << x << ' ';
        for(int i=0;i<x;i++)cout << num++ << ' ';
        cout << '\n';
    }
}
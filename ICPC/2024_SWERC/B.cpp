#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    k=min(k,n);
    vector<pair<ll,int>> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i].first;
        a[i].second=i;
    }
    sort(a.begin(),a.end());
    vector<vector<ll>> dp(k+1,vector<ll>(n+1,1e18));
    vector<vector<int>> pre(k+1,vector<int>(n+1,-1));
    dp[0][0]=0LL;
    for(int s=1;s<=k;s++){
        for(int i=0;i<n;i++){
            ll cur=0;
            for(int j=i;j>=0;j--){
                cur+=(a[i].first-a[j].first)*(a[i].first-a[j].first);
                if(dp[s-1][j]+cur<dp[s][i+1]){
                    dp[s][i+1]=dp[s-1][j]+cur;
                    pre[s][i+1]=j;
                }
            }
        }
    }
    vector<int> ans(n);
    for(int s=k,i=n;s>0;s--){
        int x=a[i-1].first;
        int j=pre[s][i];
        while(i>j){
            i--;
            ans[a[i].second]=x;
        }
        i=j;
    }
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}
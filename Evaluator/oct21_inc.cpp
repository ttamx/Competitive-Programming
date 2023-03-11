#include<bits/stdc++.h>

using namespace std;

const int N=1005;

int n;
int a[N];
int dp[N];
int ans[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;++i)cin >> a[i];
    a[n+1]=2e9;
    for(int i=1;i<=n+1;++i){
        for(int j=i+1;j<=n+1;++j){
            if(a[i]<a[j])dp[j]=max(dp[j],dp[i]+1);
        }
    }
    cout << dp[n+1] << '\n';
    int idx=n+1;
    for(int i=dp[n+1];i>0;--i){
        for(int j=idx-1;j>0;--j){
            if(a[j]<a[idx]&&dp[j]==dp[idx]-1){
                ans[i]=a[j];
                idx=j;
                break;
            }
        }
    }
    for(int i=1;i<=dp[n+1];++i)cout << ans[i] << ' ';
}
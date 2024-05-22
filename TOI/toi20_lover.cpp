#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,v,w;
    cin >> n >> v >> w;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<array<int,2>> qs(n+1);
    for(int i=1;i<=n;i++){
        qs[i]=qs[i-1];
        qs[i][a[i-1]&1]+=a[i-1];
    }
    vector<int> dp(n+1,n);
    dp[0]=0;
    for(int i=2;i<=n;i+=2){
        for(int j=0;j<i;j+=2){
            int m=(i+j)/2;
            if(qs[m][1]-qs[j][1]>v||qs[i][0]-qs[m][0]>w)continue;
            dp[i]=min(dp[i],dp[j]+1);
        }
    }
    cout << (dp[n]<n?dp[n]:-1);
}
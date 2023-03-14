#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(n),o(k+1);
    for(auto &x:a)cin >> x;
    for(int i=0;i<m;i++){
        int x,y;
        cin >> x >> y;
        if(x>k)continue;
        o[x]=max(o[x],y);
    }
    a.emplace_back(0);
    sort(a.begin(),a.end());
    vector<int> dp(k+1,2e9),qs(k+1);
    for(int i=1;i<=k;i++)qs[i]=qs[i-1]+a[i];
    dp[0]=0;
    for(int i=1;i<=k;i++){
        dp[i]=dp[i-1]+a[i];
        for(int j=1;j<=i;j++){
            dp[i]=min(dp[i],dp[i-j]+qs[i]-qs[i-j+o[j]]);
        }
    }
    cout << dp[k];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
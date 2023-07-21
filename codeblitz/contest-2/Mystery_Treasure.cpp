#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q,k;
    cin >> n >> m >> q >> k;
    vector<int> stone(n+2);
    for(int i=1;i<=q;i++){
        int x,y;
        cin >> x >> y;
        if(stone[x])cout << -1,exit(0);
        stone[x]=y;
    }
    vector<ll> dp(m+2);
    for(int i=1;i<=n;i++){
        deque<int> dq;
        vector<ll> ndp(m+2);
        for(int j=1;j<=min(m,k+1);j++){
            while(!dq.empty()&&dp[dq.back()]>dp[j])dq.pop_back();
            dq.emplace_back(j);
        }
        for(int j=1;j<=m;j++){
            int x;
            cin >> x;
            while(!dq.empty()&&dq.front()<j-k)dq.pop_front();
            ndp[j]=dp[dq.front()]+x;
            if(j+k+1>m)continue;
            while(!dq.empty()&&dp[dq.back()]>dp[j+k+1])dq.pop_back();
            dq.emplace_back(j+k+1);
        }
        if(stone[i])for(int j=1;j<=m;j++)if(j!=stone[i])ndp[j]=1e12;
        swap(dp,ndp);
    }
    ll ans=1e12;
    for(int i=1;i<=m;i++)ans=min(ans,dp[i]);
    cout << (ans<1e12?ans:-1);
}
#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    s=" "+s;
    vector<vector<int>> dp(n+2,vector<int>(n+2,0));
    auto calc=[&](int l,int r,int a,int b){
        if(dp[l][r]==1){
            if(s[a]<s[b])return 2;
            if(s[a]>s[b])return 0;
        }
        return dp[l][r];
    };
    for(int i=1;i<=n+1;i++)dp[i][i-1]=1;
    for(int sz=2;sz<=n;sz+=2){
        for(int l=1,r=sz;r<=n;l++,r++){
            int res1=min(calc(l+2,r,l,l+1),calc(l+1,r-1,l,r));
            int res2=min(calc(l,r-2,r,r-1),calc(l+1,r-1,r,l));
            dp[l][r]=max(res1,res2);
        }
    }
    if(dp[1][n]==0)cout << "Bob\n";
    else if(dp[1][n]==1)cout << "Draw\n";
    else cout << "Alice\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
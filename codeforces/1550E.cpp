#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    string s;
    cin >> n >> k >> s;
    auto check=[&](int mid){
        vector<vector<int>> a(k,vector<int>(n));
        int b=1<<k;
        vector<vector<int>> dp(b,vector<int>(k,INF));
        for(int i=0;i<k;i++){
            char c='a'+i;
            int best=INF;
            int l=INF,r=INF;
            for(int j=n-1;j>=0;j--){
                if(s[j]==c||s[j]=='?'){
                    l=j;
                    if(r>=n)r=j;
                }else{
                    l=r=INF;
                }
                if(r<n)while(r-l+1>mid)r--;
                if(r-l+1==mid)best=min(best,r);
                a[i][j]=best;
            }
            dp[1<<i][i]=best+1;
        }
        for(int mask=1;mask<b;mask++){
            for(int i=0;i<k;i++){
                int last=dp[mask][i];
                if(!(mask>>i&1)||last>=n)continue;
                for(int j=0;j<k;j++){
                    if(mask>>j&1)continue;
                    int mask2=mask^(1<<j);
                    dp[mask2][j]=min(dp[mask2][j],a[j][last]+1);
                }
            }
        }
        int best=INF;
        for(int i=0;i<k;i++){
            best=min(best,dp[b-1][i]);
        }
        return best<=n;
    };
    int l=0,r=n;
    while(l<r){
        int m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    cout << l << "\n";
}